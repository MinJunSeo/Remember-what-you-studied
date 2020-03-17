# Project title
  
SimplePaint : Make a paint program with Windows API.  
  
# Motivation
  
「Windows API 정복 1권」을 읽으면서 지속적으로 주어지는 과제인 SimplePaint를 계속해서 해결하여 Windows API 프로젝트에 익숙해지고자 하여 시작하였습니다.  
  
# Source examples & Features
  
## version 1.0
  
	case WM_MOUSEMOVE:
		......
		// 선을 긋는다.
		MoveToEx(hdc, x, y, NULL);
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		LineTo(hdc, x, y);
		......
		return 0;
  
Draw lines use a mouse.  
  
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
		......
		return 0;
  
You can pick the color of line at the radio button.  
  
	case WM_CREATE:
		......
		hThick = CreateWindow(TEXT("button"), TEXT("굵게"),
			WS_CHILD | WS_VISIBLE | BS_CHECKBOX | WS_BORDER,
			10, 170, 55, 30, hWnd, (HMENU)ID_THICK, g_hInst, NULL);
		......
		return 0;
  
You can check the thickness of pen at the check box.  
  
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		......
		case ID_REDRAW:
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		return 0;
  
If you click the repaint button, all lines will be erased.  
  
	int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
	{
		......
		hWnd = CreateWindow(lpszClass, lpszClass,
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
		......
	}
  
You can't draw at children window. (ex : button place)  
If you uncover or adjust this window, all image will be erased.  
  
# API Reference
  
「Windows API 정복 1권」 - 과제의 힌트 제공
  
# How to use?
  
Download SimplePaint.exe file in this folder.  
  
# Screenshots
  
![캡처](https://user-images.githubusercontent.com/51042546/76831199-38fabd00-686a-11ea-9829-0ecd987fa19c.JPG)
