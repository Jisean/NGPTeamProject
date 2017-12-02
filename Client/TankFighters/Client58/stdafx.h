// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C의 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
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

#include "resource.h"
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

#include "Protocol.h"

#pragma comment(lib,"msimg32.lib")
#pragma comment(lib, "ws2_32.lib")