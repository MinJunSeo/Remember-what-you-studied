// Visual Studio 2019에서 작성된 코드입니다.

#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("Adhere");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	// 메인 윈도우 클래스 등록
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

	// 차일드 윈도우 클래스 등록
	WndClass.lpfnWndProc = ChildProc;
	WndClass.lpszClassName = TEXT("Ad");
	WndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH); // 회색 배경색을 준다.
	WndClass.style = CS_VREDRAW | CS_NOCLOSE; // 닫기 버튼(X) 사용 불가
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
	switch (iMessage)
	{
	case WM_CREATE:
		// 차일드 윈도우 생성
		CreateWindow(TEXT("Ad"), TEXT("Tool"),
			WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_VISIBLE,
			// 팝업 윈도우로 | 타이틀 바 | 시스템 메뉴 | 크기 변경 가능한 두꺼운 경계선 | 바로 보이기
			200, 250, 200, 200, hWnd, (HMENU)0, g_hInst, NULL);
		hWndMain = hWnd;
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

LRESULT CALLBACK ChildProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	LPMINMAXINFO pmmi;
	RECT mainWndRect;
	LPWINDOWPOS wp;
	int t, height;

	switch (iMessage)
	{
	case WM_GETMINMAXINFO:
		pmmi = (LPMINMAXINFO)lParam;
		// 팝업 윈도우의 폭은 200 픽셀로 고정한다.
		pmmi->ptMaxPosition.x = 200;
		pmmi->ptMaxSize.x = 200;
		pmmi->ptMaxTrackSize.x = 200;
		return 0;

	case WM_WINDOWPOSCHANGING:
		GetWindowRect(hWndMain, &mainWndRect);
		height = mainWndRect.bottom - mainWndRect.top;
		wp = (LPWINDOWPOS)lParam;

		// 팝업 윈도우의 높이는 (부모 윈도우 높이 / 4) < cy < 부모 윈도우 높이
		wp->cy = min(max(wp->cy, height / 4), height);

		t = wp->x;
		// 메인 윈도우 작업영역 x 좌표 - 팝업 윈도우의 x 좌표의 절댓값이 30 픽셀 미만
		if (abs(mainWndRect.left - t) < 30)
			t = mainWndRect.left;
		if (abs(mainWndRect.right - (t + (wp->cx))) < 30)
			// 메인 윈도우 오른쪽 작업영역 x 좌표 - 현 팝업 윈도우의 폭(200 픽셀)
			t = mainWndRect.right - (wp->cx);
		wp->x = t;

		t = wp->y;
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}