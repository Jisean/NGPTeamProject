#include "stdafx.h"
#include "Server.h"
#include "Include.h"
#include "Protocol.h"
#include "resource.h"

CServer::CServer()
{
	sock = NULL;
}

CServer::~CServer()
{
}

void CServer::err_quit(char * msg)
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

void CServer::err_display(char * msg)
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

void CServer::InitSocket(int retval)
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");


	ConnectToServer(sock);
}

void CServer::ConnectToServer(SOCKET sock)
{
	DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), g_hWnd, DlgProc);
	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(SERVERIP);
	serveraddr.sin_port = htons(9000);
	int retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");

	int anp = 1;
	setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&anp, sizeof(int));

	g_bConnected = true;
}

void CServer::CloseSocket()
{
	closesocket(sock);
	WSACleanup();
}

DWORD CServer::RecvThread(LPVOID parameter)
{
	return 0;
}

DWORD CServer::SendThread(LPVOID parameter)
{
	return 0;
}


