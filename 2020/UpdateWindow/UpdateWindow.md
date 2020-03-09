# UpdateWindow
  
	#include <Winuser.h>
	
	BOOL UpdateWindow(HWND hWnd);
  
해당 윈도우에 무효 영역이 존재할 경우, WM_PAINT 메시지의 우선순위를 무시하고 WndProc에 WM_PAINT 메시지를 전송하여 무효화된 영역을 다시 그릴 수 있도록 해주는 함수이다.  
  
WM_PAINT를 메시지 큐에 보내지 않고 WndProc에 직접 보내기 때문에 다른 메시지들보다도 우선적으로 WM_PAINT 메시지를 처리할 수 있다.  
  
SendMessage(hWnd, WM_PAINT, 0, 0); 와 비슷한 것 같지만 무효 영역이 존재하지 않으면 WndProc로 WM_PAINT 메시지를 보내지 않는다는 차이점이 있다.  
  
주의할 점은 WM_PAINT에서 담당하는 처리가 복잡한 윈도우에서 이 함수를 남용하게 되면 다른 프로그램이 제때 CPU를 활용하지 못해 반응 속도가 떨어질 수도 있다.  
  
## Parameters
  
	HWND hWnd
  
다시 그리기를 하고 싶은 윈도우의 핸들이다.  
  
## Return value
  
이 함수가 성공한다면 0이 아닌 값을, 실패한다면 0을 반환한다.  
  
### 관련 함수
  
	BOOL RedrawWindow(HWND hWnd, CONST RECT* lprcUpdate, HRGN hrgnUpdate, UINT flags);
  
그리기를 할 사각형이나 영역을 지정할 수 있고 플래그로 그리기 방법을 지정할 수 있다. 다만, 실전에서의 사용빈도는 그리 높지 않으므로 이런 함수만 있다는 정도로만 알아두자.
