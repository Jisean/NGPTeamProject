// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C�� ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <vector>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <functional>
#include <fstream>
#include <process.h>
#include <time.h>

#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

#include "Device.h"
#include "TextureMgr.h"
#include "TimeMgr.h"

#ifdef _DEBUG
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__) 
#endif

#include <crtdbg.h>

#include<WinSock2.h>
#include <CommCtrl.h>
#include <iostream>

using namespace std;

#pragma comment (lib, "fmodex_vc.lib")

#include "Server.h"
extern CServer g_Socket;

#include "resource.h"
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

#pragma comment(lib,"msimg32.lib")
#pragma comment(lib, "ws2_32.lib")