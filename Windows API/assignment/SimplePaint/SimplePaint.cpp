// Visual Studio 2019 version 16.4.6

#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// 옵션 대화상자 프로시저 원형
BOOL CALLBACK OptionDlgProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
HWND hMDlg; // 옵션 대화상자 핸들
LPCTSTR lpszClass = TEXT("SimplePaint version 3.1");

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
	static int x, y;
	static BOOL bNowDraw = FALSE;

	switch (iMessage)
	{
	case WM_CREATE:
		// 옵션 대화상자 핸들에서 사용하기 위해 해당 윈도우 핸들 저장
		hWndMain = hWnd;
		return 0;

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

		if (bNowDraw)
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
		if (!IsWindow(hMDlg)) // 대화상자가 열려있지 않다면
		{
			hMDlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, OptionDlgProc);
			ShowWindow(hMDlg, SW_SHOW);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

BOOL CALLBACK OptionDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	// 스크롤 바의 핸들을 저장할 변수
	static HWND hRedScr, hGreScr, hBluScr;
	// 현재 스크롤 바의 위치를 저장하고 있을 변수
	static int nRedPos, nGrePos, nBluPos;

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

		hRedScr = GetDlgItem(hDlg, IDC_SCRRED);
		hGreScr = GetDlgItem(hDlg, IDC_SCRGREEN);
		hBluScr = GetDlgItem(hDlg, IDC_SCRBLUE);

		// 스크롤 바의 길이를 지정한다. SB_CTL 속성을 주면 별도의 컨트롤이 부여된다.
		SetScrollRange(hRedScr, SB_CTL, 0, 255, TRUE);
		SetScrollRange(hGreScr, SB_CTL, 0, 255, TRUE);
		SetScrollRange(hBluScr, SB_CTL, 0, 255, TRUE);

		// 초기 스크롤 바의 위치를 지정한다. 초기는 검정색이니 모두 0에 위치한다.
		SetScrollPos(hRedScr, SB_CTL, 0, TRUE);
		SetScrollPos(hGreScr, SB_CTL, 0, TRUE);
		SetScrollPos(hBluScr, SB_CTL, 0, TRUE);
		return TRUE;

	case WM_HSCROLL:
	{
		int tempPos; // 스크롤 바의 변경될 위치를 임시적으로 저장할 변수

		// 직접 조정 버튼을 선택하지 않으면 작업할 수 없다.
		if (!IsDlgButtonChecked(hDlg, IDC_USERDEF))
		{
			MessageBox(hDlg, TEXT("직접 조정 버튼을 선택하세요."), TEXT("알림"), MB_OK);
			return TRUE;
		}

		if ((HWND)lParam == hRedScr)
			tempPos = nRedPos;
		else if ((HWND)lParam == hGreScr)
			tempPos = nGrePos;
		else
			tempPos = nBluPos;

		// 스크롤 바의 어디를 눌렀는가?
		switch (LOWORD(wParam))
		{
		case SB_LINELEFT:
			tempPos = max(0, tempPos - 1);
			break;

		case SB_LINERIGHT:
			tempPos = min(255, tempPos + 1);
			break;

		case SB_PAGELEFT:
			tempPos = max(0, tempPos - 10);
			break;

		case SB_PAGERIGHT:
			tempPos = min(255, tempPos + 10);
			break;

		case SB_THUMBTRACK: // 스크롤 바를 드래그하고 있다면
			tempPos = HIWORD(wParam); // 현재 위치를 tempPos에 저장한다.
			break;
		}

		if ((HWND)lParam == hRedScr)
			nRedPos = tempPos;
		else if ((HWND)lParam == hGreScr)
			nGrePos = tempPos;
		else
			nBluPos = tempPos;

		SetScrollPos((HWND)lParam, SB_CTL, tempPos, TRUE);
		dwColor = RGB(nRedPos, nGrePos, nBluPos);
		return TRUE;
	}

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_RED:
			dwColor = RGB(255, 0, 0);
			nRedPos = 255;
			nGrePos = nBluPos = 0;
			SetScrollPos(hRedScr, SB_CTL, nRedPos, TRUE);
			SetScrollPos(hGreScr, SB_CTL, nGrePos, TRUE);
			SetScrollPos(hBluScr, SB_CTL, nBluPos, TRUE);
			return TRUE;

		case IDC_YELLOW:
			dwColor = RGB(255, 255, 0);
			nRedPos = nGrePos = 255;
			nBluPos = 0;
			SetScrollPos(hRedScr, SB_CTL, nRedPos, TRUE);
			SetScrollPos(hGreScr, SB_CTL, nGrePos, TRUE);
			SetScrollPos(hBluScr, SB_CTL, nBluPos, TRUE);
			return TRUE;

		case IDC_BLUE:
			dwColor = RGB(0, 0, 255);
			nRedPos = nGrePos = 0;
			nBluPos = 255;
			SetScrollPos(hRedScr, SB_CTL, nRedPos, TRUE);
			SetScrollPos(hGreScr, SB_CTL, nGrePos, TRUE);
			SetScrollPos(hBluScr, SB_CTL, nBluPos, TRUE);
			return TRUE;

		case IDC_BLACK:
			dwColor = RGB(0, 0, 0);
			nRedPos = nGrePos = nBluPos = 0;
			SetScrollPos(hRedScr, SB_CTL, nRedPos, TRUE);
			SetScrollPos(hGreScr, SB_CTL, nGrePos, TRUE);
			SetScrollPos(hBluScr, SB_CTL, nBluPos, TRUE);
			return TRUE;

		case IDC_USERDEF:
			dwColor = RGB(nRedPos, nGrePos, nBluPos);
			return TRUE;

		case IDC_THICK:
			if (IsDlgButtonChecked(hDlg, IDC_THICK)) // 버튼이 체크되어 있는가?
				nWidth = 5;
			else
				nWidth = 1;
			return TRUE;

		case IDC_CLEAR:
			InvalidateRect(hWndMain, NULL, TRUE);
			return TRUE;

		// 모델리스형 대화상자이기 때문에 닫는 것은 취소버튼을 누르거나 닫기버튼을 눌렀을 때 뿐이다.
		case IDCANCEL:
		case IDCLOSE:
			DestroyWindow(hMDlg);
			hMDlg = NULL;
			return TRUE;
		}
		break;
	}

	return FALSE;
}
