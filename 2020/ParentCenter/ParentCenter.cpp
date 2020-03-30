// Visual Studio 2019 version 16.4.6

#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("ParentCenter");

void MoveToParentCenter(HWND);

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

	switch (iMessage)
	{
	case WM_CREATE:
		hWndMain = hWnd;
		return 0;

	case WM_LBUTTONDOWN:
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProc);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
		MoveToParentCenter(hDlg);
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hDlg, IDOK);
			return TRUE;

		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return FALSE;
		}
		break;
	}

	return FALSE;
}

void MoveToParentCenter(HWND hDlg)
{
	int x, y;
	RECT rtMain, rtDlg; // main window와 대화상자 좌표를 구한다.

	if (!IsWindowVisible(hWndMain)) // window가 최소화되어 있는 경우
		ShowWindow(hWndMain, SW_SHOW);

	// 각 window의 화면상의 좌표를 구한다.
	GetWindowRect(hWndMain, &rtMain);
	GetWindowRect(hDlg, &rtDlg);

	// main window의 중앙 좌표를 구한다.
	x = (rtMain.left + rtMain.right) / 2;
	y = (rtMain.top + rtMain.bottom) / 2;

	// 대화상자의 절반 폭만큼 x, y를 감소해야 한다.
	x -= (rtDlg.right - rtDlg.left) / 2;
	y -= (rtDlg.bottom - rtDlg.top) / 2;

	// 크기는 변경하지 않고 위치만 옮기기 위해 SWP_NOSIZE 사용
	SetWindowPos(hDlg, hWndMain, x, y, 0, 0, SWP_NOSIZE);
}