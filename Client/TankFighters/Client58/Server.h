#pragma once
#include "stdafx.h"

class CServer
{
public:
	CServer();
	~CServer();

public:
	void err_quit(char *msg);
	void err_display(char* msg);

	void InitSocket(int retval);
	void ConnectToServer(SOCKET sock);
	void CloseSocket();
	
	DWORD WINAPI RecvThread(LPVOID parameter);
	DWORD WINAPI SendThread(LPVOID parameter);


public:
	SOCKET sock;
	DWORD SERVERIP;


};