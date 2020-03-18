// Visual Studio 2019 version 16.4.6

#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// 옵션 대화상자 프로시저 원형
BOOL CALLBACK OptionDlgProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("SimplePaint version 2.0");

// 옵션 대화상자에서도 사용해야 하기에 전역 변수로 변경
int nWidth = 1;
COLORREF dwColor = RGB(0, 0, 0); // 펜의 색을 결정할 변수. 초기색은 검정

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

	// 화면에 차일드가 없어져 WS_OVERLAPPEDWINDOW 속성으로만 생성
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
	static int x, y;
	static BOOL bNowDraw = FALSE;

	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (LOWORD(wParam))
		{
		case VK_SPACE: // 공백 키를 누를 경우
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

	// 오른쪽 마우스 버튼을 누를 경우 옵션 대화상자를 연다.
	case WM_RBUTTONDOWN:
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, OptionDlgProc);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

BOOL CALLBACK OptionDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	// 대화상자를 열 때 어떤 버튼이 체크되어야 하는지 검사 후 체크한다.
	case WM_INITDIALOG:
		if (nWidth == 1)
			CheckDlgButton(hDlg, IDC_THICK, BST_UNCHECKED);
		else
			CheckDlgButton(hDlg, IDC_THICK, BST_CHECKED);

		if (dwColor == RGB(0, 0, 0))
			CheckDlgButton(hDlg, IDC_BLACK, BST_CHECKED);
		else if (dwColor == RGB(255, 0, 0))
			CheckDlgButton(hDlg, IDC_RED, BST_CHECKED);
		else if (dwColor == RGB(255, 255, 0))
			CheckDlgButton(hDlg, IDC_YELLOW, BST_CHECKED);
		else
			CheckDlgButton(hDlg, IDC_BLUE, BST_CHECKED);
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			if (IsDlgButtonChecked(hDlg, IDC_THICK)) // 버튼이 체크되어 있는가?
				nWidth = 5;
			else
				nWidth = 1;

			// 라디오 버튼이기에 각 버튼을 모두 if로 검사할 필요가 없다.
			if (IsDlgButtonChecked(hDlg, IDC_BLACK))
				dwColor = RGB(0, 0, 0);
			else if (IsDlgButtonChecked(hDlg, IDC_RED))
				dwColor = RGB(255, 0, 0);
			else if (IsDlgButtonChecked(hDlg, IDC_YELLOW))
				dwColor = RGB(255, 255, 0);
			else
				dwColor = RGB(0, 0, 255);
			
			EndDialog(hDlg, IDOK);
			return TRUE;

		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		}
		break;
	}
	
	return FALSE;
}