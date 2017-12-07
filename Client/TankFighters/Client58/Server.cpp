#include "stdafx.h"
#include "Server.h"
#include "Include.h"
#include "Protocol.h"
#include "resource.h"

DWORD SERVERIP;

void err_quit(char * msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, (LPCWSTR)msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

void err_display(char * msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, (LPCWSTR)msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
}

SOCKET InitSocket(int retval)
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	return sock;
}

void ConnectToServer(SOCKET sock)
{
	DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), g_hWnd, DlgProc);
	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	int retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");

	int anp = 1;
	setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&anp, sizeof(int));

}

void CloseSocket(SOCKET sock)
{
	closesocket(sock);
	WSACleanup();
}

DWORD WINAPI RecvThread(LPVOID parameter)
{
	ORIGINPACKET sp = *(ORIGINPACKET*)parameter;
	int retval;
	int GameState;//게임 진행상태
	HANDLE hEvent = sp.hEvent;

	PACKET sPacket;

	while (1)
	{
		WaitForSingleObject(hEvent, INFINITE);

		//게임 상태 수신 0: 대기, 1: 게임 진행
		retval = recv(sp.sock, (char*)&GameState, sizeof(int), 0);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
			exit(1);
		}

		if (GameState == 1 && g_bGameStarted == false && g_bLoadingEnd == true)
		{
			g_bGameReady = true;
		}
		////////////////


		//1,2플레이어 구분
		retval = recv(sp.sock, (char*)&g_iPlayerNum, sizeof(int), 0);
		if(retval == SOCKET_ERROR) {
			err_display("recv()");
			exit(1);
		}

		int playerSize = 0;
		retval = recv(sp.sock, (char*)&playerSize, sizeof(int), 0);

		//PACKET
		for (int i = 0; i < playerSize; ++i)
		{
			retval = recv(sp.sock, (char*)&sPacket, sizeof(PACKET), 0);
			if (retval == SOCKET_ERROR) {
				err_display("recv()");
				exit(1);
			}
			else if (retval == 0)
				break;
		}


		cout << "패킷 수신됨" << endl;

		SetEvent(hEvent);
	}
	return 0;
}

DWORD WINAPI SendThread(LPVOID parameter)
{
	if (g_bGameStarted == true)
	{
		SENDPACKET sp = *(SENDPACKET*)parameter;

		char buf[BUFSIZE + 1] = "TestPacket";

		int retval = send(sp.sock, (char*)&sp.key, sizeof(sp.key), 0);//키입력 현황 송신
		if (retval == SOCKET_ERROR)
		{
			err_display("send()");
			exit(1);
		}
		cout << "패킷송신됨" << endl;

		//::Safe_Delete(parameter);

		delete parameter;
	}

	return 0;
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
			SendMessage(GetDlgItem(hDlg, IDC_IPADDRESS1), IPM_GETADDRESS, 0, (LPARAM)&SERVERIP);
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	case WM_CLOSE:
		exit(1);
		break;
	}
	return FALSE;
}
