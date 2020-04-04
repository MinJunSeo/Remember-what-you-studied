# Scrollbar
  
"scrollbar" 윈도우 클래스로 생성할 수 있다. 수평 스크롤 바일 경우 SBS_HORZ, 수직 스크롤 바일 경우 SBS_VERT 스타일을 지정한다.  
  
	BOOL SetScrollRange(HWND hWnd, int nBar, int nMinPos, int nMaxPos, BOOL bRedraw);
  
`hWnd` : 스크롤 바의 윈도우 핸들  
`nBar` : 이미 부착된 스크롤 바나 별도의 스크롤 바 컨트롤을 지정한다. SB_CTL이면 별도의 컨트롤을 지정한다.  
`nMinPos` : 해당 스크롤 바의 최솟값(범위)  
`nMaxPos` : 해당 스크롤 바의 최댓값(범위)  
`bRedraw` : 변경을 위해 스크롤 바를 다시 그려야하는지 묻는 진위형 인수  
  
이 함수를 통해 초기 스크롤 바를 만들어 범위를 지정하여 생성할 수 있다.  
  
	int SetScrollPos(HWND hWnd, int nBar, int nPos, BOOL bRedraw);
  
`hWnd` : 스크롤 바의 윈도우 핸들  
`nBar` : 스크롤 바의 컨트롤을 지정한다. SB_CTL이면 별도의 컨트롤을 지정한다.  
`nPos` : 스크롤 바가 처음 위치해있을 위치를 지정한다.  
`bRedraw` : 스크롤 바를 다시 그릴 것인지 묻는 진위형 인수  
  
스크롤 바를 생성한 뒤, 스크롤 바의 위치를 초기화하거나 변경할 때 사용한다.  
  
스크롤 바는 수평 스크롤 바와 수직 스크롤 바에 따라 전달되는 메시지가 다르다. 수평인 경우 WM_HSCROLL, 수직일 경우 WM_VSCROLL 메시지가 전달된다.  
  
메시지와 함께 인수로 전달되는 wParam과 lParam이 지니는 의미는 다음과 같다.  
  
인수 | 설명
-----|------
LOWORD(wParam) | 스크롤 바 내의 어디를 눌렀는가?
HIWORD(wParam) | 현재 위치
lParam | 스크롤 바의 윈도우 핸들
  
LOWORD(wParam)으로 전달되는 위치 값은 다음과 같다.  
  
값 | 설명
---|------
SB_LINELEFT 또는 SB_LINEUP | 사용자가 왼쪽 화살표 버튼을 눌렀다는 뜻이다. 왼쪽으로 한 단위 스크롤시킨다.
SB_LINERIGHT 또는 SB_LINEDOWN | 사용자가 오른쪽 화살표 버튼을 눌렀다는 뜻이다. 오른쪽으로 한 단위 스크롤시킨다.
SB_PAGELEFT 또는 SB_PAGEUP | 사용자가 왼쪽 몸통 부분을 눌렀다는 뜻이다. 한 페이지 왼쪽으로 스크롤 시킨다.
SB_PAGERIGHT 또는 SB_PAGEDOWN | 사용자가 오른쪽 몸통 부분을 눌렀다는 뜻이다. 한 페이지 오른쪽으로 스크롤 시킨다.
SB_THUMBPOSITION | 스크롤 박스를 드래그한 후 마우스 버튼을 놓았다.
SB_THUMBTRACK | 스크롤 박스를 드래그하고 있는 중이다. 마우스 버튼을 놓을 때까지 계속 전달된다.
