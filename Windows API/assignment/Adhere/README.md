# Project Title
  
Windows API - Adhere  
  
# Project Contents
  
## Motivation
  
Windows API를 공부하면서 주어지는 과제를 해결하고자 노력하였습니다.  
과제의 구현 과정에서 꽤나 높은 벽을 마주했기에 자신에게 필요한 정보를 찾을 수 있는 능력도 기르고자 하였습니다.  
  
## Goal
  
여러 종류의 윈도우 관리 및 여러 가지 조건을 설정할 수 있도록 한다.  
  
## Function
  
1. 팝업 윈도우의 폭을 200픽셀로 고정하여 높이만 조정할 수 있도록 합니다. 또한 높이는 부모 윈도우의 높이를 초과하지 못하며 최소 부모 높이의 1/4 이상의 크기를 유지합니다.  
2. 팝업 윈도우가 부모의 좌측 혹은 우측 벽에 30픽셀 미만으로 접근하면 부모의 벽에 밀착시킵니다.
  
## Source Example
  
1. 팝업 윈도우의 닫기 버튼 사용 금지  
  
      	WndClass.style = CS_VREDRAW | CS_NOCLOSE; // 닫기 버튼(X) 사용 불가
  
위와 같이 윈도우 클래스의 style 멤버에 CS_NOCLOSE 스타일을 부여하면 닫기 버튼을 사용할 수 없는 상태의 윈도우를 생성할 수 있습니다.  
  
2. 팝업 윈도우의 폭을 200픽셀로 고정하기  
  
      	LPMINMAXINFO pmmi;
      	......
      	case WM_GETMINMAXINFO:
		pmmi = (LPMINMAXINFO)lParam;
		// 팝업 윈도우의 폭은 200 픽셀로 고정한다.
		pmmi->ptMaxPosition.x = 200;
		pmmi->ptMaxSize.x = 200;
		pmmi->ptMaxTrackSize.x = 200;
		return 0;
  
운영체제는 윈도우의 크기 혹은 위치를 변경하기 전에 이 메시지를 보냅니다. 그리고 lParam에 전달되는 구조체를 통해 윈도우의 위치 혹은 크기를 제한할 수 있습니다.  
  
ptMaxPosition은 최대화되었을 때의 위치를 지정합니다.  
ptMaxSize는 최대화되었을 때의 크기를 지정합니다.  
ptMaxTrackSize는 경계선을 드래그하여 지정할 수 있는 윈도우의 최대 크기를 제한합니다.  
  
3. 부모 윈도우의 좌,우측벽에 30픽셀 미만으로 접근하면 부모의 벽에 밀착시키기  
  
      	RECT mainWndRect;
      	LPWINDOWPOS wp;
      	int t, height;
      	......
      	case WM_WINDOWPOSCHANGING:
		GetWindowRect(hWndMain, &mainWndRect);
		height = mainWndRect.bottom - mainWndRect.top;
		wp = (LPWINDOWPOS)lParam;
  
해당 메시지에서 lParam으로 전달되는 WINDOWPOS 구조체는 현재 이동중인 윈도우의 영역을 알려줍니다. 이 값을 편집하면 윈도우의 새 위치에 반영이 됩니다.  
  
     // 팝업 윈도우의 높이는 (부모 윈도우 높이 / 4) < cy < 부모 윈도우 높이
	wp->cy = min(max(wp->cy, height / 4), height);
  
팝업 윈도우의 높이는 부모 윈도우의 높이를 넘어설 수 없고, 최소한 부모 윈도우의 1/4 크기를 유지해야 하는 조건이 있기 때문에 해당 소스를 작성합니다.  
  
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
  
메인 윈도우의 작업 영역 x 좌표와 팝업 윈도우의 x 좌표의 절댓값이 30픽셀 미만이라면 팝업 윈도우의 x 좌표를 메인 윈도우의 왼쪽 좌표로 하여 좌측에 달라붙게 만듭니다.  
  
메인 윈도우의 오른쪽 작업 영역 x 좌표 - (팝업 윈도우의 x 좌표 + 팝업 윈도우의 폭)의 절댓값이 30픽셀 미만이라면 우측 벽에 붙어야 할 조건을 충족했기 때문에 우측 벽에 붙여야 합니다. 이때, 우측 벽에 붙이기 위해서 t = mainWndRect.right; 를 사용하면 안됩니다. t는 현재 팝업 윈도우의 x 좌표를 가지고 있는데요. 해당 x 좌표는 윈도우의 좌상단을 의미합니다. 그러므로 오른쪽 벽에 붙이기 위해서는 윈도우의 폭만큼 빼줄 필요가 있다는 뜻입니다. 그래서 현재 팝업 윈도우의 폭을 메인 윈도우의 오른쪽 좌표에서 빼준 값으로 x 좌표를 변경합니다.  
  
# Screenshot
  
![캡처](https://user-images.githubusercontent.com/51042546/75956218-c1886d80-5efa-11ea-849b-8cf0f1f8c466.JPG)
  
# Reference
  
「Windows API 정복 1권」 - 김상형 저  
MSDN(MicroSoft Developer Network)  
  
## 작성 이력
  
2020-03-05 : Adhere.cpp 파일을 추가함
