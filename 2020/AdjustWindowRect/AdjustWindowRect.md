# AdjustWindowRect
  
## Syntax
  
	#include <Winuser.h>
	
	BOOL AdjustWindowRect(LPRECT lpRect, DWORD dwStyle, BOOL bMenu);
  
이 함수는 원하는 작업 영역의 크기를 주면 작업 영역 크기에 맞는 윈도우 크기를 계산한다. 그런 다음 윈도우 크기를 CreateWindow 함수로 넘겨주면 원하는 크기의 클라이언트 영역의 윈도우를 만들 수 있다.  
  
이 함수는 전달받은 스타일 값과 메뉴 존재 여부를 참고하여 원하는 작업 영역에 맞는 윈도우 크기를 계산하여 첫 번째 인수 lpRect에 다시 대입한다.
  
확장 스타일을 주고 싶다면 확장 함수인 AdjustWindowRectEx 함수를 이용할 수 있다. 원형은 다음과 같다.  
  
	BOOL AdjustWindowRectEx(LPRECT lpRect, DWORD dwStyle, BOOL bMenu, DWORD dwExStyle);
  
확장 스타일을 지정하는 인수인 dwExStyle이 늘어난 것 빼고는 AdjustWindowRect 함수와 하는 일은 동일하다.  
  
## Parameters
  
	LPRECT lpRect
  
RECT 구조체의 포인터로 가리키고 있는 RECT 구조체는 원하는 클라이언트 영역의 왼쪽 상단 및 오른쪽 하단 모서리의 좌표를 포함하고 있어야 한다.  
  
	DWORD dwStyle
  
창의 스타일을 지정하는 인수로 | 연산자를 사용하여 복수 개의 스타일을 전달할 수 있다. 단, **WS_OVERLAPPED 스타일은 지정할 수 없다.**  
  
	BOOL bMenu
  
해당 창에 메뉴가 존재하는 지를 전달합니다.  
  
## Return value
  
성공하면 0이 아닌 값을, 실패하면 0을 반환합니다.  
  
## Remarks
  
작업 영역을 원하는 크기대로 변경하기 위해서는 타이틀 바, 경계선의 폭, 높이를 고려해야 한다. 하지만 이러한 값들은 사용자가 제어판에서 마음대로 변경할 수 있기 때문에 고정되어 있지 않고 시스템마다 다르다. 그러한 계산을 해 주는 것이 바로 이 함수이다.  
  
단, **WS_HSCROLL, WS_VSCROLL 스타일을 가진 윈도우의 경우 스크롤 바의 크기는 계산에 포함되지 않는다.** 이러한 부분은 안타깝지만 직접 계산해야 한다.
