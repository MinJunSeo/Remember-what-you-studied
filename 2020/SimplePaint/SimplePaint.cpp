// Visual Studio 2019 version 16.4.6

#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("SimplePaint");

enum { ID_RED = 101, ID_BLUE, ID_YELLOW, ID_BLACK }; // 색상 ID
#define ID_THICK 200 // 펜 굵게하는 ID
#define ID_REDRAW 201 // 화면 다시 그리는 ID

// 각 기능들의 윈도우의 핸들
HWND hRed, hBlue, hYellow, hBlack, hThick, hReDraw;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass,
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int x, y;
	static int nWidth = 1;
	static BOOL bNowDraw = FALSE;
	static COLORREF dwColor = RGB(0, 0, 0); // 펜의 색을 결정할 변수. 초기색은 검정

	switch (iMessage)
	{
	case WM_CREATE:
		// 라디오버튼을 묶을 그룹박스 생성
		CreateWindow(TEXT("button"), TEXT("색상"),
			WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			10, 10, 70, 150, hWnd, (HMENU)0, g_hInst, NULL);
		hRed = CreateWindow(TEXT("button"), TEXT("빨강"),
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
			17, 27, 55, 30, hWnd, (HMENU)ID_RED, g_hInst, NULL);
		hBlue = CreateWindow(TEXT("button"), TEXT("파랑"),
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			17, 57, 55, 30, hWnd, (HMENU)ID_BLUE, g_hInst, NULL);
		hYellow = CreateWindow(TEXT("button"), TEXT("노랑"),
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			17, 87, 55, 30, hWnd, (HMENU)ID_YELLOW, g_hInst, NULL);
		hBlack = CreateWindow(TEXT("button"), TEXT("검정"),
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			17, 117, 55, 30, hWnd, (HMENU)ID_BLACK, g_hInst, NULL);
		CheckRadioButton(hWnd, ID_RED, ID_BLACK, ID_BLACK);
		hThick = CreateWindow(TEXT("button"), TEXT("굵게"),
			WS_CHILD | WS_VISIBLE | BS_CHECKBOX | WS_BORDER,
			10, 170, 55, 30, hWnd, (HMENU)ID_THICK, g_hInst, NULL);
		hReDraw = CreateWindow(TEXT("button"), TEXT("다시 그리기"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			10, 210, 100, 30, hWnd, (HMENU)ID_REDRAW, g_hInst, NULL);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_THICK:
			if (SendMessage(hThick, BM_GETCHECK, 0, 0) == BST_UNCHECKED) // 체크되어 있지 않다면
			{
				SendMessage(hThick, BM_SETCHECK, BST_CHECKED, 0); // 체크된 상태로 변경한다.
				nWidth = 5; // 굵기를 굵게 한다.
			}
			else
			{
				SendMessage(hThick, BM_SETCHECK, BST_UNCHECKED, 0);
				nWidth = 1;
			}
			break;

		case ID_RED:
			dwColor = RGB(255, 0, 0);
			break;

		case ID_BLUE:
			dwColor = RGB(0, 0, 255);
			break;

		case ID_YELLOW:
			dwColor = RGB(255, 255, 0);
			break;

		case ID_BLACK:
			dwColor = RGB(0, 0, 0);
			break;

		case ID_REDRAW:
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		return 0;

	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		bNowDraw = TRUE;
		return 0;

	case WM_MOUSEMOVE:
	{
		HPEN hPen, OldPen;

		if(bNowDraw)
		{
			hdc = GetDC(hWnd);
			// 펜을 내가 설정한 굵기와 색깔로 만든다.
			hPen = CreatePen(PS_SOLID, nWidth, dwColor);
			OldPen = (HPEN)SelectObject(hdc, hPen);

			// 선을 긋는다.
			MoveToEx(hdc, x, y, NULL);
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			LineTo(hdc, x, y);

			SelectObject(hdc, OldPen);
			DeleteObject(hPen);
			ReleaseDC(hWnd, hdc);
		}
		return 0;
	}

	case WM_LBUTTONUP:
		bNowDraw = FALSE;
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}