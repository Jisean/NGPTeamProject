// Client58.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Client58.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE g_hInst;								// 현재 인스턴스입니다.
TCHAR szTitle[MAX_LOADSTRING];					// 제목 표시줄 텍스트입니다.
TCHAR szWindowClass[MAX_LOADSTRING];			// 기본 창 클래스 이름입니다.
HWND	g_hWnd;
bool	g_bLoadingEnd = false;
bool	g_bGameStarted = false;
bool	g_bGameReady = false;
int		g_iPlayerNum = 0;


// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	

 	// TODO: 여기에 코드를 입력합니다.
	MSG msg;
	msg.message = WM_NULL;

	// 전역 문자열을 초기화합니다.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CLIENT58, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	CMainGame		MainGame;

	if(FAILED(MainGame.Initialize()))
	{
		ERR_MSG(L"MainGame Init Failed");
		return E_FAIL; 
	}

	// 기본 메시지 루프입니다.
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			MainGame.Progress();
			MainGame.Render();
		}
	}

	return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
//  설명:
//
//    Windows 95에서 추가된 'RegisterClassEx' 함수보다 먼저
//    해당 코드가 Win32 시스템과 호환되도록
//    하려는 경우에만 이 함수를 사용합니다. 이 함수를 호출해야
//    해당 응용 프로그램에 연결된
//    '올바른 형식의' 작은 아이콘을 가져올 수 있습니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT58));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
   RECT	rc = {0, 0, WINCX, WINCY };

   g_hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance, NULL);
   /*hWnd = CreateWindow(szWindowClass, szTitle, WS_EX_TOPMOST | WS_POPUP,
      CW_USEDEFAULT, 0, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance, NULL);*/

 
   if (!hWnd)
   {
      return FALSE;
   }

    g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND	- 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT	- 주 창을 그립니다.
//  WM_DESTROY	- 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	static ORIGINPACKET *packet;
	static HANDLE hEvent;
	static SOCKET sock;
	static bool key[8];

	switch (message)
	{
	case WM_CREATE:
		sock = InitSocket(0);
		ConnectToServer(sock);

		hEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
		packet = new ORIGINPACKET(sock);
		packet->hEvent = hEvent;
		
		CreateThread(NULL, 0, RecvThread, (LPVOID)packet, 0, NULL);
		SetTimer(hWnd, 1, 50, NULL);//패킷 송신용 타이머 세팅
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
		{
			SENDPACKET *SPacket = new SENDPACKET(sock,key);
			CreateThread(NULL, 0, SendThread, (LPVOID)SPacket, 0, NULL);
		}
		}
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 메뉴의 선택 영역을 구문 분석합니다.
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case 'W':
			key[0] = true;
			break;
		case 'S':
			key[1] = true;
			break;
		case 'A':
			key[2] = true;
			break;
		case 'D':
			key[3] = true;
			break;
		case VK_UP:
			key[3] = true;
			break;
		case VK_DOWN:
			key[3] = true;
			break;
		case VK_LEFT:
			key[3] = true;
			break;
		case VK_RIGHT:
			key[3] = true;
			break;

		case VK_ESCAPE://종료용
			CloseSocket(sock);
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_KEYUP:
	{
		switch (wParam)
		{
		case 'W':
			key[0] = false;
			break;
		case 'S':
			key[1] = false;
			break;
		case 'A':
			key[2] = false;
			break;
		case 'D':
			key[3] = false;
			break;
		case VK_UP:
			key[3] = true;
			break;
		case VK_DOWN:
			key[3] = true;
			break;
		case VK_LEFT:
			key[3] = true;
			break;
		case VK_RIGHT:
			key[3] = true;
			break;
		}
	}
	break;
	
	case WM_DESTROY:
		CloseSocket(sock);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


