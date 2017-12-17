#pragma once
#include "stdafx.h"
#include "Protocol.h"

// ���� �Լ� ���� ��� �� ����
void err_quit(char *msg);

// ���� �Լ� ���� ���
void err_display(char *msg);

SOCKET InitSocket(SOCKET& sock);
void ConnectToServer(SOCKET& sock, SOCKADDR_IN& serveraddr);
void CloseSocket(SOCKET sock);


DWORD WINAPI KeyProcess(LPVOID K);

int recvn(SOCKET s, char *buf, int len, int flags);
DWORD WINAPI SendThread(LPVOID parameter);



BOOL CALLBACK DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
