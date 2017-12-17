#pragma once
#include "stdafx.h"
#include "Protocol.h"

// 소켓 함수 오류 출력 후 종료
void err_quit(char *msg);

// 소켓 함수 오류 출력
void err_display(char *msg);

SOCKET InitSocket(SOCKET& sock);
void ConnectToServer(SOCKET& sock, SOCKADDR_IN& serveraddr);
void CloseSocket(SOCKET sock);


DWORD WINAPI KeyProcess(LPVOID K);

int recvn(SOCKET s, char *buf, int len, int flags);
DWORD WINAPI SendThread(LPVOID parameter);



BOOL CALLBACK DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
