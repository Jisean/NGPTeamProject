#pragma once
#include "stdafx.h"

// ���� �Լ� ���� ��� �� ����
void err_quit(char *msg);

// ���� �Լ� ���� ���
void err_display(char *msg);

SOCKET InitSocket(int retval);
void ConnectToServer(SOCKET sock);
void CloseSocket(SOCKET sock);




DWORD WINAPI RecvThread(LPVOID parameter);
DWORD WINAPI SendThread(LPVOID parameter);


BOOL CALLBACK DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
