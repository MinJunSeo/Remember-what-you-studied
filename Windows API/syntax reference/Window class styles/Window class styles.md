# Window class styles
  
WNDCLASS 구조체의 멤버 중 style에 지정할 수 있는 플래그를 말한다. 복수 개를 동시에 지정하는 것도 가능하다.  
  
## List
  
style | meaning
------|---------
CS_BYTEALIGNCLIENT | 작업 영역을 X축으로 바이트 정렬하여 이동이나 크기 조정 속도를 빠르게 한다. 16색이나 흑백 화면에서만 의미가 있다.
CS_BYTEALIGNWINDOW | 윈도우를 X축으로 바이트 정렬하여 이동이나 크기 조정 속도를 빠르게 한다. 16색이나 흑백 화면에서만 의미가 있다.
CS_CLASSDC | 이 클래스로부터 만들어진 모든 윈도우가 하나의 DC를 공유한다.
CS_DBLCLKS | 마우스 더블클릭 메시지를 보낸다.
CS_DROPSHADOW | drop shadow 효과를 활성화한다.
CS_GLOBALCLASS | 해당 프로그램을 전역 클래스로 등록한다.
CS_HREDRAW | 작업 영역의 폭이 변경되면 윈도우를 다시 그린다.
CS_NOCLOSE | 시스템 메뉴의 닫기 명령을 사용하지 못하게 한다. 타이틀 바에 있는 X 버튼도 사용할 수 없으며 Alt + F4 키로도 종료할 수 없다.
CS_OWNDC | 각 윈도우가 하나의 DC를 독점적으로 사용한다.
CS_PARENTDC | 차일드 윈도우가 부모 윈도우의 DC를 사용한다.
CS_SAVEBITS | 윈도우가 열리기 전에 이 윈도우가 차지하는 배경 화면 영역을 비트맵으로 저장한다. 운영체제는 이 윈도우가 화면에서 제거될 때 저장한 비트맵으로 화면을 복구하며 가려졌던 윈도우에게 WM_PAINT 메시지를 보내지 않는다. 사용 시 최초 윈도우가 나타나는 시간이 조금 오래 걸린다.
CS_VREDRAW | 작업 영역의 높이가 변경되면 윈도우를 다시 그린다.
  
## CS_CLASSDC
  
	int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
	{
		WNDCLASS WndClass;
		......
		WndClass.style = CS_CLASSDC;
		......
	}
  
위와 같이 WNDCLASS 구조체의 style에 CS_CLASSDC 플래그를 주게 되면 해당 윈도우 클래스로부터 만들어지는 모든 윈도우는 클래스 DC를 사용한다. 한 윈도우 클래스에 속한 모든 윈도우가 같은 DC를 공유한다. DC 핸들을 매번 할당받을 필요가 없어 속도에 유리하다.  
  
그러나 Win32에서는 여러 가지 이유로 사용을 금지하고 있다. 과거와의 호환성 문제로 아직 남아 있을 뿐 사용하지 말아야 한다.  
  
## CS_DBLCLKS
  
	int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
	{
		WNDCLASS WndClass;
		......
		WndClass.style = CS_DBLCLKS;
		......
	}
  
위와 같이 WNDCLASS 구조체의 style에 CS_DBLCLKS 플래그를 주게 되면 더블클릭 메시지를 받을 수 있다. 만약 더블클릭 처리를 하고 싶다면 위와 같이 style에 플래그를 준 뒤, 윈도우 프로시저에서  
  
	case WM_LBUTTONDBLCLK:
		// 더블클릭 메시지 처리
  
다음과 같이 처리하면 된다.  
  
더블클릭을 검출하는데 그만큼 실행 시간의 감소가 요구되며 해당 플래그를 지정할 경우 WM_LBUTTONDOWN을 두 번 받는다든지, 트리플 클릭 등의 검출을 할 수는 없게 된다.  
  
## CS_DROPSHADOW
  
	int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
	{
		WNDCLASS WndClass;
		......
		WndClass.style = CS_DROPSHADOW;
		......
	}
  
위와 같이 WNDCLASS 구조체의 style에 CS_DROPSHADOW 플래그를 주면 drop shadow 효과를 사용할 수 있게 된다. 이 효과는 SPI_SETDROPSHADOW를 통해 효과 적용 / 비적용을 토글할 수 있다. 사용 시 대표적으로 해당 윈도우의 바로 뒤 Z 축에 투명한 윈도우가 하나 생기며 그 윈도우는 그림자를 가지고 있다.
  
![캡처](https://user-images.githubusercontent.com/51042546/76399543-1d069f80-63c2-11ea-8108-44a53a4ea541.JPG)  
  
## CS_GLOBALCLASS
  
	int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
	{
		WNDCLASS WndClass;
		......
		WndClass.style = CS_GLOBALCLASS;
		......
	}
  
위와 같이 WNDCLASS 구조체의 style에 CS_GLOBALCLASS 플래그를 지정하면 Application 전역 클래스를 만든다. Application 전역 클래스는 프로세스의 모든 모듈에서 이 클래스를 사용할 수 있다. Application이 직접 이 부류의 클래스를 만드는 경우는 무척 드물다.  
  
## CS_HREDRAW
  
	int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
	{
		WNDCLASS WndClass;
		......
		WndClass.style = CS_HREDRAW;
		......
	}
  
위와 같이 WNDCLASS 구조체의 style에 CS_HREDRAW 스타일을 지정하면 작업 영역의 폭이 변경되었을 경우 작업 영역 전체를 무효화하여 다시 그린다. WM_SIZE에서 InvalidateRect를 자동으로 호출하는 역할이라고 보면 된다.  
  
그리기는 확실하게 되지만 그만큼 WM_PAINT가 빈번하게 호출되므로 속도가 조금 늦어진다. 그래서 작업 영역 크기와 그림이 관계없거나 크기 조절이 아예 불가능한 윈도우의 경우 이 스타일을 주지 않는 것이 좋을 수 있다.  
  
## CS_NOCLOSE
  
	int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
	{
		WNDCLASS WndClass;
		......
		WndClass.style = CS_NOCLOSE;
		......
	}
  
위와 같이 WNDCLASS 구조체의 style에 CS_NOCLOSE를 지정하면 시스템 메뉴의 닫기 명령을 사용할 수 없다. 또한 타이틀 바의 닫기 버튼도 사용할 수 없고, Alt + F4의 강제 종료도 할 수 없다. 그래서 해당 프로그램의 종료 방법을 제시하지 않으면 작업 관리자의 힘을 빌릴 수밖에 없다.  
  
2020 폴더에 있는 Adhere 폴더에 있는 예제가 바로 이 CS_NOCLOSE를 활용한 예제이다.  
![캡처](https://user-images.githubusercontent.com/51042546/76400391-92bf3b00-63c3-11ea-831a-1c6afd3840b1.JPG)  
위와 같이 시스템 명령의 닫기 버튼이 보이지 않는다.  
  
## CS_OWNDC
  
	int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
	{
		WNDCLASS WndClass;
		......
		WndClass.style = CS_OWNDC;
		......
	}
  
위와 같이 WNDCLASS 구조체의 style에 CS_OWNDC 플래그를 지정하면 private DC를 사용할 수 있게 된다.  
  
private DC는 하나의 윈도우가 배타적으로 사용하는 DC를 말한다. 윈도우가 생성될 때 한 번만 만들어지며 윈도우가 실행되는 동안 계속 존재한다. 그래서 한 번 설정해 놓으면 바꾸지 않는 한 값이 계속 유지되며 윈도우가 실행되는 동안 계속 존재하므로 사용 후 ReleaseDC로 해제해서는 안 된다.
  
그래서 그리기 속도가 빨라지는 장점이 있지만 시스템 리소스와 메모리를 많이 소모하는 단점이 있고 디폴트 DC로 되돌리기 어렵다.  
  
## CS_PARENTDC
  
	int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
	{
		WNDCLASS WndClass;
		......
		WndClass.style = CS_PARENTDC;
		......
	}
  
위와 같이 WNDCLASS 구조체의 style에 CS_PARENTDC 플래그를 지정하면 parent DC를 사용할 수 있게 된다.  
  
parent DC가 발급될 때 부모 윈도우가 사용하던 DC를 캐시에서 찾아 해당 DC를 사용한다. 없다면 커먼 DC가 발급된다. 클리핑 영역을 계산하는 시시간을 최소화하기 위해 사용한다. (최상위 윈도우나 팝업 윈도우는 이 DC를 사용할 수 없다.)  
  
## CS_VREDRAW
  
	int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
	{
		WNDCLASS WndClass;
		......
		WndClass.style = CS_VREDRAW;
		......
	}
  
작업 영역의 폭이 아니라 **높이**가 변경될 때 작업 영역을 무효화하여 다시 그리는 점을 제외하면 CS_HREDRAW와 동일하다.  
  
아직 배우는 중이라 몇 개 상세히 알려드리지 못 한 스타일에 대해서는 죄송스럽게 생각합니다. 다음에 조금 더 배우게 되어 알게 되는 기회가 있다면 수정하도록 하겠습니다.
