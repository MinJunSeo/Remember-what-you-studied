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
  
## version 2.0
  
![캡처](https://user-images.githubusercontent.com/51042546/76929586-e8499980-6927-11ea-8964-4183c5d948cc.JPG)  
You can pick the color and thick at the option dialog.  
  
	case WM_KEYDOWN:
		switch (LOWORD(wParam))
		{
		case VK_SPACE:
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		return 0;
  
If you enter space key, all images will be erased.  
  
	// 마우스 오른쪽 버튼을 누르면 옵션 대화상자를 연다.
	case WM_RBUTTONDOWN:
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, OptionDlgProc);
		return 0;
  
If you click the mouse right button, you can open the option dialog.  
  
## version 3.0
  
![캡처](https://user-images.githubusercontent.com/51042546/77033324-3aeb8a00-69ea-11ea-86d0-dae84fda5c74.JPG)  
From now on, this dialog box is modeless dialog box. So, you can draw during you open this dialog box.  
This dialog box has 다시 그리기 button, so you push this button, will be erased all images.  
If you pick the color or thick, that will be applied real time.  
  
## version 3.1
  
![image](https://user-images.githubusercontent.com/51042546/77131279-7d6e9e80-6a9e-11ea-9ed4-d6c9f94d497d.png)  
From now on, you can pick the color to scroll RGB scrollbar.  
But, you can pick the color by scrollbar when you check the 직접 조정 button.  
If you don't check 직접 조정 button and scroll RGB scrollbar,  
  
![image](https://user-images.githubusercontent.com/51042546/77131381-d3434680-6a9e-11ea-9a44-e5e070a971fd.png)  
will appear a messagebox to inform you that please check the 직접 조정 button.  
  
But it has some bug. The messagebox appear twice. I don't know why the message box appear twice. I'm sorry.
  
# API Reference
  
「Windows API 정복 1권」 - 과제의 힌트 제공
  
# How to use?
  
Download SimplePaint.exe file in this folder.  
Download SimplePaint.sln and open it. Then, build and run that project.  
  
# Screenshots
  
![캡처](https://user-images.githubusercontent.com/51042546/76831199-38fabd00-686a-11ea-9829-0ecd987fa19c.JPG)  
SamplePaint program's execution result with version 1.0  
  
![캡처](https://user-images.githubusercontent.com/51042546/76929349-4164fd80-6927-11ea-8ca1-cfdd357509d1.JPG)  
SamplePaint program's execution result with version 2.0  
  
![캡처](https://user-images.githubusercontent.com/51042546/77033602-0a582000-69eb-11ea-9500-d5a01581228e.JPG)  
SamplePaint program's execution result with version 3.0  
  
![캡처](https://user-images.githubusercontent.com/51042546/77131503-32a15680-6a9f-11ea-837e-3b2db0fdf176.JPG)  
SamplePaint program's execution result with version 3.1  
  
## 작성 이력
  
2020-03-17 : SimplePaint의 1.0 버전인 SimplePaint.cpp 파일과 SimplePaint.exe 파일을 추가함  
2020-03-18 : SimplePaint의 버전을 2.0으로 업그레이드 하였다. .sln 파일과 resource 파일들을 추가함  
2020-03-19 : SimplePaint의 버전을 3.0으로 업그레이드 하였다.  
2020-03-20 : SimplePaint의 버전을 3.1로 업그레이드 하였다.
