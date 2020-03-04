// Visual Studio 2019에서 작성된 코드입니다.

#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("UserMes");

UINT nSoriMessage;

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

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
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
	LPCTSTR Mes = TEXT("마우스 왼쪽 버튼을 누르면 SoriMessage 메시지를 전달합니다.");
	int i;
	RECT rt;

	switch (iMessage)
	{
	case WM_CREATE:
		nSoriMessage = RegisterWindowMessage(TEXT("SoriMessage"));
		return 0;

	case WM_LBUTTONDOWN:
		SendMessage(hWnd, nSoriMessage, 0, 0);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 50, 50, Mes, lstrlen(Mes));
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	if (iMessage == nSoriMessage)
	{
		hdc = GetDC(hWnd);
		MessageBeep(0);
		SelectObject(hdc, GetStockObject(NULL_BRUSH));
		for (i = 0; i < 100; i += 5)
		{
			Ellipse(hdc, 200 - i, 200 - (i / 2), 200 + i, 200 + (i / 2));
			Sleep(10);
		}
		Sleep(100);
		SetRect(&rt, 100, 100, 300, 300);
		FillRect(hdc, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH));
		ReleaseDC(hWnd, hdc);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}