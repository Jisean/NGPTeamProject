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

SOCKET InitSocket(SOCKET& sock)
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == INVALID_SOCKET) 
		err_quit("socket()");

	return sock;
}

void ConnectToServer(SOCKET& sock, SOCKADDR_IN& serveraddr)
{
	DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), g_hWnd, DlgProc);
	// connect()
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

DWORD WINAPI KeyProcess(LPVOID K)
{
	while (1)
	{
		KeyInput tKey = *(KeyInput*)K;

		if (GetAsyncKeyState(VK_RIGHT))
			tKey.bRight = true;

		if (GetAsyncKeyState(VK_LEFT))
			tKey.bLeft = true;

		if (GetAsyncKeyState(VK_UP))
			tKey.bUp = true;

		if (GetAsyncKeyState(VK_DOWN))
			tKey.bDown = true;

	}
	return 0;

}

int recvn(SOCKET s, char *buf, int len, int flags)
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

