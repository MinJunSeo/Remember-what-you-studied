# BeginPaint
  
	#include <Winuser.h>
	
	HDC BeginPaint(HWND hWnd, LPPAINTSTRUCT lpPaint);
  
다시 그리기 위한 윈도우를 준비하며, PAINTSTRUCT 구조체를 그리기와 관련된 정보들로 채운다.  
  
무효 영역 중 다시 그릴 필요가 없는 비가시 영역을 제외하여 자동으로 클리핑 영역을 설정한다.  
  
반드시 WM_PAINT 메시지를 처리하는 과정에서만 호출해야 하는 함수이며, WM_PAINT 메시지 이외의 부분에서 이 함수를 호출해서는 안 된다.  
  
GetDC를 호출하면 ReleaseDC를 호출하는 것과 같이 BeginPaint 함수를 호출하였다면 EndPaint를 반드시 호출해야 한다.  
  
## Parameters
  
	HWND hWnd
  
다시 그리기 위한 윈도우의 핸들이다.  
  
	LPPAINTSTRUCT lpPaint
  
그리기에 관련된 정보를 받을 PAINTSTURCT 구조체의 포인터이다.  
  
## Return value
  
성공한다면, 해당 윈도우에서 그리기에 사용할 DC의 핸들을 리턴한다.  
실패한다면, NULL이 반환된다.  
  
## Source example
  
	LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
	{
		HDC hdc;
		PAINTSTRUCT ps;
		
		switch (iMessage)
		{
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// 그리기 작업은 여기에 작성합니다. ex) 원 그리기, 텍스트 출력...
			EndPaint(hWnd, &ps);
			return 0;
		......
	}
  
웬만한 Windows API 소스들을 찾아보면 다들 이런 메시지 형태일 것이다. Windows API에서 화면 출력을 위해서는 WM_PAINT 메시지를 사용해야 하므로 반드시 이 코드들이 작성되어야 할 것이다.  
  
여담으로, Visual Studio 2019에서 자동으로 프로젝트를 생성해주는 프레임워크를 사용하면 WM_PAINT 메시지 처리 부분은 주석 메시지나 hdc를 제외하면 동일하게 작성되어 있다. 그만큼 저 형태가 기본적인 형태라는 뜻이다.  
  
### 클리핑 영역
  
클리핑 영역은 무효 영역 중에서도 화면에 보이는 가시 영역을 말한다. 실제 그리기에 사용하는 영역은 무효 영역이 아니라 클리핑 영역이다. 대체로 클리핑 영역과 무효 영역은 일치하지만 그렇지 않은 경우가 있다.  
  
![캡처](https://user-images.githubusercontent.com/51042546/76293689-dac35c80-62f4-11ea-83cf-0ccb806252a2.JPG)  
  
위의 경우 동영상은 매 초마다 무효 영역이 많이 정의된다. 동영상 그림 자체가 계속 변하기 때문에 무효화되는 영역은 작업 영역 전체가 된다. 하지만 일부분이 언커버되었는데 그렇기 때문에 언커버된 부분을 다시 그릴 필요는 없다. 왜냐하면 지금 해당 부분이 사용자에게 보이지 않기 때문이다. 이 경우, BeginPaint에서는 클리핑 영역을 설정할 때 해당 부분을 제외한 영역을 그리기 영역인 클리핑 영역으로 설정하게 된다.  
  
이 외에도 최소화되어 있는 상태나, 윈도우의 일부분이 화면 밖으로 나가있을 때 등도 클리핑 영역이 무효 영역과 일치하지 않는 경우일 수 있다.
