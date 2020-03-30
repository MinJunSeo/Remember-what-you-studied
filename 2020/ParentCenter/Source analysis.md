# Source analysis
  
## global variable
  
	HINSTANCE g_hInst;
  
WinMain에 전달되는 hInst 인수를 다른 프로세서 등에서 사용하기 위해 저장할 공간이 필요합니다. 그를 위해 선언된 전역 변수입니다.  
  
	HWND hWndMain;
  
윈도우 프로시저에서 생성하는 윈도우의 핸들을 저장하기 위한 전역 변수입니다. 보통 래퍼 함수나 다른 프로세서에서 해당 윈도우에 대한 작업을 수행할 때 핸들이 필요하기 때문에 그를 위한 용도로 사용합니다.  
  
	LPCTSTR lpszClass = TEXT("ParentCenter");
  
윈도우 클래스의 멤버 중 lpszClassName의 멤버에 대입하기 위해 선언 및 초기화하였습니다. 여기서 초기화한 값은 lpszClassName에 저장되어 윈도우 타이틀에 표기됩니다.  
  
## WndProc
  
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
  
전체 코드입니다. 전반적으로 어려운 작업을 하고 있지는 않습니다. 단순히 생성되면서 hWndMain 변수에 해당 윈도우의 핸들을 저장하고, 왼쪽 마우스 버튼을 눌렀을 때 대화상자를 하나 생성합니다.  
  
## DlgProc
  
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
  
전체 코드입니다.  
  
	case WM_INITDIALOG:
		MoveToParentCenter(hDlg);
		return TRUE;
  
대화상자를 생성 및 초기화하면서 MoveToParent 함수를 호출합니다. 이 함수가 바로, 대화상자를 부모 윈도우의 중앙으로 옮겨주는 함수입니다.  
  
나머지 부분은 보편적인 대화상자 프로시저랑 동일합니다. 대화상자의 확인 버튼 혹은 취소 버튼을 눌렀을 경우 부모 윈도우로 각자의 ID를 보내면서 대화상자를 종료합니다.  
  
## MoveToParent function
  
	void MoveToParentCenter(HWND hDlg)
	{
		int x, y;
		RECT rtMain, rtDlg;

		if (!IsWindowVisible(hWndMain))
			ShowWindow(hWndMain, SW_SHOW);

		GetWindowRect(hWndMain, &rtMain);
		GetWindowRect(hDlg, &rtDlg);

		x = (rtMain.left + rtMain.right) / 2;
		y = (rtMain.top + rtMain.bottom) / 2;

		x -= (rtDlg.right - rtDlg.left) / 2;
		y -= (rtDlg.bottom - rtDlg.top) / 2;

		SetWindowPos(hDlg, hWndMain, x, y, 0, 0, SWP_NOSIZE);
	}
  
이번 프로그램의 핵심 기능을 담당하는 함수의 전체 코드입니다.  
  
	if (!IsWindowVisible(hWndMain))
		ShowWindow(hWndMain, SW_SHOW);
  
부모 윈도우가 보이지 않는 상황인지 검사합니다. 보통 최소화나 다른 윈도우에 언커버되었을 경우를 예로 들 수 있습니다. 보이지 않을 경우에 한해 해당 윈도우를 보이는 상태로 변경합니다.  
  
	GetWindowRect(hWndMain, &rtMain);
	GetWindowRect(hDlg, &rtDlg);
  
부모 윈도우와 대화상자의 윈도우의 좌표를 구하기 위해 호출하였습니다. 부모 윈도우의 크기와 대화상자의 크기를 알아야 정확한 절반을 구할 수 있고 그렇게 해야 중앙으로 옮길 수 있기 때문입니다.  
  
	x = (rtMain.left + rtMain.right) / 2;
	y = (rtMain.top + rtMain.bottom) / 2;
  
우선 x에는 부모 윈도우의 가로 넓이의 절반의 좌표 값을, y에는 부모 윈도우의 세로 넓이의 절반의 좌표 값을 할당합니다. 이 좌표가 부모 윈도우의 정중앙 좌표입니다.  
  
	x -= (rtDlg.right - rtDlg.left) / 2;
	y -= (rtDlg.bottom - rtDlg.top) / 2;
  
이제 x에서는 대화상자의 가로 넓이의 절반 값을 빼줌으로써 대화상자가 이동했을 때 대화상자의 가로축 중앙점이 부모 윈도우의 중앙점에 위치하게 합니다. y에서는 대화상자의 세로 넓이의 절반 값을 빼줌으로써 대호상자가 이동했을 때 대화상자의 세로축 중앙점이 부모 윈도우의 중앙점에 위치하게 합니다.  
  
	SetWindowPos(hDlg, hWndMain, x, y, 0, 0, SWP_NOSIZE);
  
이제 구한 값을 가지고 해당 좌표로 대화상자를 이동시켜주면 됩니다. 크기는 변경하지 않고 위치만 변경하기 위해 SWP_NOSIZE 스타일을 지정하였습니다.  
  
## Program execution
  
![캡처](https://user-images.githubusercontent.com/51042546/77870074-689ec180-727b-11ea-9fe5-958f7c6c1342.JPG)
  
첫 실행 화면의 모습이다. 왼쪽 마우스 버튼을 누르면 보는 것처럼 부모 윈도우의 정중앙에 대화상자가 생성되는 것을 볼 수 있다.  
  
![캡처](https://user-images.githubusercontent.com/51042546/77870112-7ce2be80-727b-11ea-930e-900a7400423e.JPG)  
  
부모 윈도우의 크기가 줄어들어도 그에 맞게 대화상자는 부모 윈도우의 중앙에 생성된다.
