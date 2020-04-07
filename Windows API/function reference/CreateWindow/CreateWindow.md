# CreateWindow
  
	#include <Winuser.h>
	
	void CreateWindow(lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight,
		hWndParent, hMenu, hInstance, lpParam);
  
overlapped, pop-up, child 윈도우를 만든다. 만약 확장 스타일을 주고 싶다면 CreateWindowEx 함수를 사용해야 한다.  
  
## Parameters
  
	// Type : LPCTSTR
	lpClassName
  
RegisterClass 혹은 RegisterClassEx 함수를 통해 등록한 윈도우 클래스의 이름을 지정하는 문자열이다. 여기서 지정한 윈도우 클래스에 정의된 속성대로 윈도우를 생성한다.  
  
	// Type : LPCTSTR
	lpWindowName
  
윈도우의 타이틀 바에 표시될 문자열이다. 프로그래머가 마음대로 지정할 수 있지만 컨트롤의 이름("button", "listbox" 등) 등 지정할 수 없는 문자열이 존재한다.  
  
	// Type : DWORD
	dwStyle
  
만들고자 하난 윈도우의 스타일을 지정한다. 스크롤 바를 가지거나 경계선을 가지는 등 여러 가지 설정을 여기서 할 수 있다. 가장 무난하게 WS_OVERLAPPEDWINDOW를 주면 우리가 평소에 사용하는 보편적인 윈도우가 만들어진다.  
  
	// Type : int
	x
  
윈도우의 좌상단이 나타날 좌표의 x 좌표를 의미한다.  
  
	// Type : int
	y
  
윈도우의 좌상단이 나타날 좌표의 y 좌표를 의미한다. 만약 x, y 인수로 100, 500을 줬으면 윈도우의 가장 좌상단이 (100, 500) 좌표에 나타난다.  
  
	// Type : int
	nWidth
  
픽셀 단위이며, 윈도우의 폭을 지정한다.  
  
	// Type : int
	nHeight
  
픽셀 단위이며, 윈도우의 높이를 지정한다.  
  
	// Type : HWND
	hWndParent
  
부모 윈도우의 핸들을 지정한다. 보통 차일드 윈도우를 만들 때 사용한다.  
  
	// Type : HMENU
	hMenu
  
윈도우에서 사용할 메뉴의 핸들을 지정한다. 이 인수로 지정된 메뉴는 현재 CreateWindow 함수로 만들어지는 윈도우에서만 사용한다. NULL을 주면 윈도우 클래스에서 지정한 메뉴를 그대로 사용할 수 있다.  
  
	// Type : HINSTANCE
	hInstace
  
프로그램의 핸들을 지정한다. 보통 WinMain의 인수로 전달된 hInstance를 대입하면 된다.  
  
	// Type : LPVOID
	lpParam
  
CREATESTRUCT라는 구조체를 가리키는 포인터이며 여러 개의 윈도우를 만들 때 각 윈도우에 고유의 파라미터를 전달하는 특수 목적으로 사용한다. 보편적으로는 NULL을 준다.  
  
## System class
  
CreateWindow의 인수 중 lpWindowName으로 지정할 수 없는 것 중 하나가 바로 시스템 클래스이다. 시스템 클래스는 운영체제가 프로그램이 시작됨과 동시에 자동으로 등록되는 윈도우 클래스이다. 보편적으로 차일드 윈도우로 잘 알려진 버튼이나 체크박스같은 것들이다.  
  
시스템 클래스를 사용하기 위해서는 lpClassName에 시스템 클래스의 이름을 주면 된다. 대소문자는 상관없다.  
  
	// Example - Create Edit
	CreateWindow(TEXT("Edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOSCROLL,
		50, 50, 100, 30, hWnd, (HMENU)0, g_hInst, NULL);
  
System class | meaning
-------------|---------
BUTTON | 버튼(누를 수 있는 버튼이다. 스타일을 바꾸면 체크 박스도 만들 수 있다.) 
COMBOBOX | 콤보 박스(목록에 있는 항목 중 하나를 선택할 수도 있고 직접 내용을 입력할 수도 있다.)
EDIT | 에디트(자신이 직접 글을 써 넣을 수 있는 공간이다.)
LISTBOX | 리스트 박스(목록에 있는 항목 중 하나를 선택할 수 있다.)
MDICLIENT | MDI client 윈도우
RichEdit | microsoft rich edit 1.0 컨트롤이다.
RICHEDIT_CLASS | microsoft rich edit 2.0 컨트롤이다.
SCROLLBAR | 스크롤 바
STATIC | 스태틱(화면상에 출력되어 있는 글자들)
