// TankFighters_Server.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include "windows.h"
#include <stdlib.h>
#include <stdio.h>
#include "Player.h"
#include "protocol.h"
#include "Bullet.h"

#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

typedef struct tagTile //타일 정보
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vSize;
	BYTE			byOption;
	BYTE			byDrawID;

}TILE;


#define SERVERPORT 9000
#define BUFSIZE    512

#define KEYBUF 4
//

//변수 및 STL 컨테이너
CRITICAL_SECTION cs; // 임계 영역
bool sendEvent;
OBJDATA objdata;
KEYDATA keyData;

SOCKADDR_IN clientaddr;
SOCKET client_sock[2];
SOCKET	listen_sock;
HANDLE		hlistenThread = nullptr;
HANDLE		hThread[2];
KEY PlayerKey[2];
vector<CBullet*> vecBullet;
CBullet BulletArray[30];
int BulletIndex = 0;
vector<TILE*>	m_vecTile;
vector<TILE*>   vecTile;


int Player_Number = 0;
HANDLE hUpdateHandle; //업데이트 스레드에서 객체들 정보를 받는다
CPlayer Player[2] = { CPlayer(0), CPlayer(1) };


//함수 선언부
void AddPlayerNumber(void);
void LoadTile(const char& wstrPath);
void UpdateData(DWORD dwTime, DWORD dwTime2);
void TankTileColision(void);
void BulletUpdate();
ORIGINPACKET PlayerUpdate(int clientNum, int otherPlayer, PACKET& Packet);
void RecvData(int clientNum, PACKET& Packet);
void SendData(ORIGINPACKET Origin, PACKET& Packet);


// 소켓 함수 오류 출력 후 종료
void err_quit(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

// 소켓 함수 오류 출력
void err_display(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}


int WINAPI recvn(SOCKET s, char *buf, int len, int flags)
{
	int received;
	char *ptr = buf;
	int left = len;

	while (left > 0)
	{
		received = recv(s, ptr, left, flags);

		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;

		else if (received == 0)
			break;

		left -= received;

		ptr += received;

	}
	return (len - left);

}

DWORD WINAPI UpdateThread(LPVOID clientNum)
{
	PACKET Packet;
	DWORD m_dwTime = GetTickCount();


	AddPlayerNumber();

	Packet.OBJ_ID = (int)clientNum;
	int otherPlayer = 0;
	if (Packet.OBJ_ID == 0)
		otherPlayer = 1;

	else
		otherPlayer = 0;




	//최초에 플레이어에게 1,2플레이어 구분을 해주는 송신함수.
	int Retval = send(client_sock[Packet.OBJ_ID], (char*)&Packet.OBJ_ID, sizeof(PACKET), 0);
	if (Retval == SOCKET_ERROR)
		err_display("Send()");

	

	while (1)
	{

		RecvData((int)clientNum, Packet);

		ORIGINPACKET Origin = PlayerUpdate((int)clientNum, otherPlayer, Packet);
		
		SendData(Origin,Packet);

	}
	return 0;
}
void AddPlayerNumber(void)
{
	EnterCriticalSection(&cs);//동시접속시 꼬임을 방지하기위해 임게영역에 진입한다.
	++Player_Number;
	LeaveCriticalSection(&cs);
}

DWORD WINAPI AcceptThread(LPVOID nullvalue)
{

	while (1)
	{

		if (Player_Number > 1)
			break;


		// accept()
		int addrlen = sizeof(clientaddr);
		client_sock[Player_Number] = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);

		if (client_sock[Player_Number] == INVALID_SOCKET)
		{
			err_display("accept()");
			break;
		}

		// 접속한 클라이언트 정보 출력
		printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		hThread[Player_Number] = CreateThread(NULL, 0, UpdateThread, (LPVOID)Player_Number, 0, NULL);

		if (hThread[Player_Number] == NULL)
		{
			closesocket(client_sock[Player_Number]);
		}
		else
		{
			CloseHandle(hThread[Player_Number]);
		}



	}

	return 0;

}



int main(int argc, char *argv[])
{

	int retval;

	InitializeCriticalSection(&cs);

	//////////타일정보 세팅
	char* FileName = "TankFightersMap.dat";
	LoadTile(*FileName);

	for (int i = 0; i < m_vecTile.size(); ++i)
	{
		if (m_vecTile[i]->byOption == 4)
		{
			vecTile.push_back(m_vecTile[i]);
		}
	}
	/////////////////////

	// 윈속 초기화
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return E_FAIL;

	// socket()
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (listen_sock == INVALID_SOCKET)
		err_quit("socket()");

	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
		err_quit("bind()");


	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
		err_quit("listen()");

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;



	//AcceptThread()
	hlistenThread = CreateThread(nullptr, 0, AcceptThread, nullptr, 0, nullptr);

	DWORD dwTime = GetTickCount();
	DWORD dwTime2 = GetTickCount();
	//각각 플레이어 1,2가 사용할 타임값


	while (1)
	{

		EnterCriticalSection(&cs);

		UpdateData(dwTime,dwTime2);
		
		LeaveCriticalSection(&cs);


		TankTileColision();


	}

	closesocket(listen_sock);


	// 윈속 종료
	WSACleanup();

	for (int i = 0; i < vecBullet.size(); ++i)
	{
		delete vecBullet[i];
	}
	vecBullet.clear();
	return 0;
}

void LoadTile(const char& wstrPath)
{
	HANDLE	hFile = CreateFile(&wstrPath, GENERIC_READ,
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD	dwByte;

	while (true)
	{
		TILE*		pTile = new TILE;

		ReadFile(hFile, pTile, sizeof(TILE), &dwByte, NULL);

		if (dwByte == 0)
		{
			delete pTile;
			pTile = nullptr;
			break;
		}

		m_vecTile.push_back(pTile);
	}

	CloseHandle(hFile);
}

void UpdateData(DWORD dwTime, DWORD dwTime2)
{
	int Player1 = 0;
	int Player2 = 1;


	///////////키를 확인하여 총알을 생성한다.
	if (Player[Player1].m_Key.bUShoot || Player[Player1].m_Key.bDShoot || Player[Player1].m_Key.bLShoot
		|| Player[Player1].m_Key.bRShoot)
	{
		if (vecBullet.size() < 7)
		{
			if (dwTime + 500 < GetTickCount())
			{
				dwTime = GetTickCount();
				vecBullet.push_back(CBullet::Create(Player[Player1].m_tInfo.vPos.x, Player[Player1].m_tInfo.vPos.y,
					Player[Player1].m_Key, (OBJ_ID)Player1));
			}
		}
	}


	if (Player[Player2].m_Key.bUShoot || Player[Player2].m_Key.bDShoot || Player[Player2].m_Key.bLShoot
		|| Player[Player2].m_Key.bRShoot)
	{
		if (vecBullet.size() < 7)
		{
			if (dwTime2 + 500 < GetTickCount())
			{
				dwTime2 = GetTickCount();
				vecBullet.push_back(CBullet::Create(Player[Player2].m_tInfo.vPos.x, Player[Player2].m_tInfo.vPos.y,
					Player[Player2].m_Key, (OBJ_ID)Player2));
			}
		}
	}
	/////////////////////////////////////


	BulletUpdate();

	
}

void TankTileColision()
{
	for (int i = 0; i < 2; ++i)
	{
		CPlayer* pPlayer = &Player[i];

		vector<TILE*>::iterator tileiter = vecTile.begin();


		for (tileiter; tileiter != vecTile.end(); tileiter++)
		{
			TILE* pTile = *tileiter;

			if (pTile->byOption == 4)
			{
				D3DXVECTOR3 vDis = pTile->vPos - pPlayer->m_tInfo.vPos;
				float fDis = D3DXVec3Length(&vDis);

				D3DXVECTOR3 vDir = vDis;
				D3DXVec3Normalize(&vDir, &vDir);

				float fCheckValue; // 박스의 크기

				if (pTile->byOption == 1)
					fCheckValue = 100.f;

				else
					fCheckValue = 50.f;

				if (fDis < fCheckValue + 30.f)
				{
					D3DXVECTOR3 vPlayerPos = pPlayer->m_tInfo.vPos;
					D3DXVECTOR3 vTilePos = pTile->vPos;

					RECT rcPlayer;
					rcPlayer.top = vPlayerPos.y - fCheckValue / 2;
					rcPlayer.bottom = vPlayerPos.y + fCheckValue / 2;
					rcPlayer.left = vPlayerPos.x - fCheckValue / 2;
					rcPlayer.right = vPlayerPos.x + fCheckValue / 2;

					RECT rcSource;
					rcSource.top = vTilePos.y - fCheckValue / 2;
					rcSource.bottom = vTilePos.y + fCheckValue / 2;
					rcSource.left = vTilePos.x - fCheckValue / 2;
					rcSource.right = vTilePos.x + fCheckValue / 2;

					RECT rc;

					if (IntersectRect(&rc, &rcPlayer, &rcSource))
					{
						SetRect(&rc, 0, 0, rc.right - rc.left, rc.bottom - rc.top);

						if (rc.bottom > rc.right) // 좌우 충돌
						{
							if (pPlayer->m_tInfo.vPos.x < pTile->vPos.x)
							{
								pPlayer->m_tInfo.vPos.x = pPlayer->m_tInfo.vPos.x - rc.right;
							}

							else if (pPlayer->m_tInfo.vPos.x > pTile->vPos.x)
							{
								pPlayer->m_tInfo.vPos.x = pPlayer->m_tInfo.vPos.x + rc.right;
							}
						}

						if (rc.bottom < rc.right)
						{
							if (pPlayer->m_tInfo.vPos.y < pTile->vPos.y)
							{
								pPlayer->m_tInfo.vPos.y = pPlayer->m_tInfo.vPos.y - rc.bottom;
							}

							else if (pPlayer->m_tInfo.vPos.y > pTile->vPos.y)
							{
								pPlayer->m_tInfo.vPos.y = pPlayer->m_tInfo.vPos.y + rc.bottom;
							}
						}
					}
				}

			}
		}
	}

}

void BulletUpdate()
{
	int Player1 = 0;
	int Player2 = 1;

	auto iter_Tile = vecTile.begin();

	UINT Size = vecTile.size();
	vector<CBullet*>::iterator iter = vecBullet.begin();



	///////////타일과 총알간의 충돌 처리
	int count = 0;
	for (iter; iter != vecBullet.end(); ++iter)
	{

		for (iter_Tile = vecTile.begin(); iter_Tile != vecTile.end(); ++iter_Tile)
		{


			D3DXVECTOR3 vTilePos = (*iter_Tile)->vPos;
			D3DXVECTOR3 vTearPos = (*iter)->m_tInfo.vPos;
			vTilePos.z = 0.f;
			vTearPos.z = 0.f;

			D3DXVECTOR3 vDis = vTilePos - vTearPos;

			float fDistance = D3DXVec3Length(&vDis);

			if (fDistance < 25.f)
			{

				(*iter)->iHp = 0;
				break;
			}

		}

		(*iter)->Update(count);
		++count;
	}

	///////////////////////////////


	////////////총알과 플레이어간의 충돌 처리
	iter = vecBullet.begin();
	for (iter; iter != vecBullet.end(); ++iter)
	{
		D3DXVECTOR3 vTearPos = (*iter)->m_tInfo.vPos;

		if ((*iter)->ID == ID_PLAYER)
		{
			D3DXVECTOR3 vP2Pos = Player[Player2].m_tInfo.vPos;


			vTearPos.z = 0.f;
			vP2Pos.z = 0.f;

			D3DXVECTOR3 vDis = vP2Pos - vTearPos;

			float fDistance = D3DXVec3Length(&vDis);

			if (fDistance < 25.f)
			{
				Player[Player2].iHp -= 1;
				if (Player[Player2].iHp <= 0)
					Player[Player2].m_tInfo.vPos = D3DXVECTOR3(2000.f, 2000.f, 0.f);
				(*iter)->iHp = 0;
				break;
			}
		}

		if ((*iter)->ID == ID_PLAYER2)
		{
			D3DXVECTOR3 vP1Pos = Player[Player1].m_tInfo.vPos;


			vTearPos.z = 0.f;
			vP1Pos.z = 0.f;

			D3DXVECTOR3 vDis = vP1Pos - vTearPos;

			float fDistance = D3DXVec3Length(&vDis);

			if (fDistance < 25.f)
			{
				Player[Player1].iHp -= 1;
				if (Player[Player1].iHp <= 0)
					Player[Player1].m_tInfo.vPos = D3DXVECTOR3(2000.f, 2000.f, 0.f);

				cout << Player[Player1].iHp << endl;
				(*iter)->iHp = 0;
				break;
			}
		}
	}
	////////////////////////////


	BulletIndex = 0;
	iter = vecBullet.begin();

	//////////////처리가 완료된 총알을 삭제하는 구간
	for (iter; iter != vecBullet.end();)
	{
		if ((*iter)->iHp == 0)
		{
			BulletArray[BulletIndex].m_tInfo.vPos.x = (*iter)->m_tInfo.vPos.x;
			BulletArray[BulletIndex].m_tInfo.vPos.y = (*iter)->m_tInfo.vPos.y;
			BulletArray[BulletIndex].iHp = (*iter)->iHp;
			++BulletIndex;
			delete (*iter);
			(*iter) = nullptr;
			iter = vecBullet.erase(iter);
		}

		else
		{
			BulletArray[BulletIndex].m_tInfo.vPos.x = (*iter)->m_tInfo.vPos.x;
			BulletArray[BulletIndex].m_tInfo.vPos.y = (*iter)->m_tInfo.vPos.y;
			BulletArray[BulletIndex].iHp = (*iter)->iHp;
			++BulletIndex;

			++iter;
		}

	}
	/////////////////////////////////
}

void RecvData(int clientNum, PACKET& Packet)
{
	int Retval = 0;

	ZeroMemory(&Player[(int)clientNum].m_Key, sizeof(KEY));
	Retval = recvn(client_sock[Packet.OBJ_ID], (char*)&Player[Packet.OBJ_ID].m_Key, sizeof(KEY), 0);
	PlayerKey[Packet.OBJ_ID] = Player[(int)clientNum].m_Key;

}

ORIGINPACKET PlayerUpdate(int clientNum, int otherPlayer, PACKET& Packet)
{
	float Speed = 5.f;

	if (Player[Packet.OBJ_ID].m_Key.bUp)
	{
		Player[Packet.OBJ_ID].m_tInfo.vPos.y -= Speed;
	}

	if (Player[Packet.OBJ_ID].m_Key.bDown)
	{
		Player[Packet.OBJ_ID].m_tInfo.vPos.y += Speed;
	}

	if (Player[Packet.OBJ_ID].m_Key.bLeft)
	{
		Player[Packet.OBJ_ID].m_tInfo.vPos.x -= Speed;
	}

	if (Player[Packet.OBJ_ID].m_Key.bRight)
	{
		Player[Packet.OBJ_ID].m_tInfo.vPos.x += Speed;
	}

	ORIGINPACKET Origin;
	ZeroMemory(&Origin, sizeof(ORIGINPACKET));

	Origin.PlayerInfo1.fX = Player[(int)clientNum].m_tInfo.vPos.x;
	Origin.PlayerInfo1.fY = Player[(int)clientNum].m_tInfo.vPos.y;
	Origin.PlayerInfo1.Hp = Player[(int)clientNum].iHp;

	for (int i = 0; i < BulletIndex; ++i)
	{
		Origin.BulletInfo[i].fX = BulletArray[i].m_tInfo.vPos.x;
		Origin.BulletInfo[i].fY = BulletArray[i].m_tInfo.vPos.y;
		Origin.BulletInfo[i].Hp = BulletArray[i].iHp;
	}

	Origin.BulletSize = BulletIndex;

	Origin.PlayerInfo2.fX = Player[otherPlayer].m_tInfo.vPos.x;
	Origin.PlayerInfo2.fY = Player[otherPlayer].m_tInfo.vPos.y;
	Origin.PlayerInfo2.Hp = Player[otherPlayer].iHp;
	Origin.KeyValue = PlayerKey[otherPlayer];


	return Origin;
}

void SendData(ORIGINPACKET Origin, PACKET& Packet)
{
	int Retval = 0;

	Retval = send(client_sock[Packet.OBJ_ID], (char*)&Origin, sizeof(ORIGINPACKET), 0);
	/*if (Retval == SOCKET_ERROR)
		err_display("send()");*/
}