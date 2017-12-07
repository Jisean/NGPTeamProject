// TankFighters_Server.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//


#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include "Players.h"
#include "ServerMgr.h"
#include "stdafx.h"

#define SERVERPORT 9000
#define BUFSIZE    512

#define KEYBUF 4
//
bool sendEvent;
KEYDATA keyData;
static SOCKET client_sock[2];
Player player[2];
HANDLE hThread;	//키값을 전달 받는 스레드의 이벤트
ServerMgr m_Manager;

HANDLE hUpdateHandle; //업데이트 스레드에서 객체들 정보를 받는다
PACKET tPacket;

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

DWORD WINAPI SendThread(LPVOID parameter)
{
	int retval;
	sendEvent = true;
	ServerMgr manager = m_Manager;

	// 게임 상태를 전송한다
	// 0:대기 1: 시작 2: 종료
	int GameState = manager.GetGameState();
	
	retval = send(client_sock[0], (char *)&GameState, sizeof(int), 0);
	retval = send(client_sock[1], (char *)&GameState, sizeof(int), 0);

	//// 플레이어의 데이터를 전송한다.
	vector<Player> vPlayer = manager.GetPlayers();
	int playerNum = 1;
	////플레이어 넘버 전송
	retval = send(client_sock[0], (char *)&playerNum, sizeof(int), 0);

	playerNum++;
	retval = send(client_sock[1], (char *)&playerNum, sizeof(int), 0);

	int playerSize = vPlayer.size();
	for (int i = 0; i < vPlayer.size(); ++i)
	{
		tPacket = vPlayer[i].GetData();
		retval = send(client_sock[0], (char*)&tPacket, sizeof(PACKET), 0);
		retval = send(client_sock[1], (char*)&tPacket, sizeof(PACKET), 0);
	}

	

	sendEvent = false;
	return 0;
}

DWORD WINAPI RecvThread(LPVOID clientNum)
{
	int n = (int)clientNum;
	int addrlen;
	int retval;
	bool buf[KEYBUF];
	SOCKADDR_IN clientaddr;


	addrlen = sizeof(clientaddr);
	getpeername(client_sock[n], (SOCKADDR *)&clientaddr, &addrlen);
	while (1)
	{
		retval = recv(client_sock[n], (char*)buf, sizeof(buf), 0);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
			break;
		}
		else if (retval == 0)
			break;

		if (buf[0])
			printf("상  ");
		if (buf[1])
			printf("하  ");
		if (buf[2])
			printf("좌  ");
		if (buf[3])
			printf("우  ");



		WaitForSingleObject(hUpdateHandle, INFINITE);

		keyData.clientNum = n;
		
		for (int i = 0; i < KEYBUF; ++i)
		{
			//상하좌우(0~3), 공격-상하좌우(4~7)
			keyData.key[i] = buf[i];
		}

	}


	return 0;


}

DWORD WINAPI UpdateThread(LPVOID clientNum)
{
	int n = (int)clientNum;
	int addrlen;
	int retval;
	char buf;
	int mapY = 0;
	SOCKADDR clientaddr;

	addrlen = sizeof(clientaddr);
	ZeroMemory(keyData.key, sizeof(KEYDATA));

	DWORD stime = GetTickCount();
	DWORD updateSTime = GetTickCount();

	m_Manager.GameStart();
	while (1)
	{
		//플레이어 업데이트
		if (keyData.clientNum != -1)
		{
			m_Manager.SetKeyData(keyData);
			//m_Manager.UpdatePlayer(keyData);
			for (int i = 0; i < KEYBUF; ++i)
				keyData.key[i] = false;
			keyData.clientNum = -1;
			SetEvent(hUpdateHandle);
		}

		//오브젝트 업데이트
		if (GetTickCount() - updateSTime > 10)
		{
			updateSTime = GetTickCount();
		}

		//sendThread 호출
		if (GetTickCount() - stime > 30 && sendEvent == false)
		{
			CreateThread(NULL, 0, SendThread, (LPVOID)&mapY, 0, NULL);
		
			stime = GetTickCount();
		}
	}

	return 0;
}


DWORD WINAPI AcceptThread(LPVOID parameter)
{
	int retval;
	int addrlen;
	int clientSize = 0;
	SOCKADDR_IN clientaddr;
	SOCKET sock = (SOCKET)parameter;

	bool start = true;


	while (1) {
		// accept()
		addrlen = sizeof(clientaddr);

		client_sock[clientSize] = accept(sock, (SOCKADDR *)&clientaddr, &addrlen);

		int anp = 1;
		setsockopt(client_sock[clientSize], IPPROTO_TCP, TCP_NODELAY, (char*)&anp, sizeof(int));

		printf("%s 접속\n", inet_ntoa(clientaddr.sin_addr));

		hThread = CreateThread(NULL, 0, RecvThread, (LPVOID)clientSize, 0, NULL);
		if (hThread == NULL)
			printf("리시브 스레드 생성 실패");

		clientSize++;

		if (clientSize > 1 && start)
		{
			printf("Update Thread Start\n");
			hThread = CreateThread(NULL, 0, UpdateThread, (LPVOID)clientSize, 0, NULL);
			if (hThread == NULL)
				printf("업데이트 스레드 생성 실패");
			start = false;
		}

	}


	return 0;
}

int main(int argc, char *argv[])
{
	int retval;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;


	keyData.clientNum = -1;
	for (int i = 0; i < 8; ++i)
	{
		keyData.key[i] = false;
	}

	// socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");


	SOCKADDR_IN clientaddr;
	int addrlen;

	//이벤트 생성
	hUpdateHandle = CreateEvent(NULL, FALSE, TRUE, NULL);
	if (hUpdateHandle == NULL)
		return 1;


	HANDLE HuThread = CreateThread(NULL, 0, AcceptThread, (LPVOID)listen_sock, 0, NULL);
	WaitForSingleObject(HuThread, INFINITE);

	// closesocket()
	closesocket(listen_sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}

