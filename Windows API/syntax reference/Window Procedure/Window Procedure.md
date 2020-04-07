# Window Procedure
  
윈도우 프로시저(Window Procedure)는 윈도우 클래스당 하나씩 배정되며 운영체제로부터 전달되는 메시지를 어떻게 처리할지 정의해놓음으로써 해당 윈도우가 어떻게 행동할지 결정해준다.  
  
일반적으로 다음고 같은 원형을 가지는 함수이다.  
  
	LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
  
함수이므로 이름은 물론 사용자가 마음대로 바꿀 수 있지만 일반적으로 WndProc라는 이름을 사용한다. 운영체제에 의해 호출되는 CALLBACK 함수이기 때문에 사용자가 직접 호출할 수는 없고 SendMessage 등의 함수를 이용해 간접적으로 호출할 수 있다.  
  
## Parameters
  
	HWND hWnd
  
운영체제로 전달된 메시지를 받을 윈도우 핸들이다.  
  
	UINT uMsg
  
전달된 메시지의 값을 가진다.  
  
	WPARAM wParam
	LPARAM lParam
  
둘 다 32비트 정수값이며 메시지의 추가 정보를 가진다. 메시지별로 이들의 의미는 각각 다르기 때문에 메시지별로 알고 있을 필요가 있다.  
  
## Framework
  
윈도우 프로시저로 무수히 많은 메시지가 전달되는데 메시지별로 처리하는 과정이 전부 다르다 보니 switch 문을 사용한다. 보편적으로 다음과 같은 형태로 정의된다.  
  
	LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		HDC hdc;
		PAINTSTRUCT ps;
		
		switch (uMsg)
		{
		case WM_CREATE:
			return 0;
		
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			return 0;
		
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		
		return (DefWindowProc(hWnd, uMsg, wParam, lParam));
	}
  
여기서 다른 메시지를 처리하고 싶다면 case 문을 추가하여 처리할 수 있다. WM_CREATE 밑에는 초기화를 위한 코드를 작성하면 되고, 그리기와 관련된 코드는 대부분 BeginPaint와 EndPaint 함수 사이에 작성하면 된다. 보편적으로 WM_DESTROY 메시지 처리 루틴이 switch의 맨 마지막에 작성된다.  
  
## Reentrant
  
윈도우 프로시저는 실행 중에 또다른 윈도우 프로시저가 실행될 수 있는 재진입(Reentrant)이 가능한 함수이다. 대표적인 예로는 SendMessage를 들 수 있다.  
  
SendMessage처럼 직접적으로 재진입을 명시하는 코드가 있고, 함수 내부에서 특정한 메시지를 보내는 경우(BeginPaint 등)와 같은 간접적인 재진입이 있을 수도 있다.  
  
재진입이 가능하기 때문에 가급적이면 지역변수를 적게 사용하는 것이 좋다. 특히 변수를 초기화하는 문장은 가금적 자제해야 한다.  
  
변수나 배열을 선언하는 것은 보통 메시지에서 처리를 보조하기 위해 선언하는 경우가 많은데 한 지역변수가 여러 곳에 사용될 수도 있지만 한 메시지의 처리만을 위해 선언되는 경우도 있다. 만약 한 메시지만의 처리를 위해 배열이나 변수를 선언해 초기화하는 경우 불필요하게 메모리를 낭비하게 된다.  
  
	// 극단적인 예로 다음과 같은 경우를 들 수 있다.
	LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		TCHAR buffer[9999];
		int number[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		...
	}
  
저걸 만약 WM_KEYDOWN이나 WM_PAINT와 같이 한 메시지에서만 사용하는 지역변수라면 메모리 낭비가 정말 장난이 아닐 것이다. 위와 같이 특정 메시지의 처리만을 위한 지역변수는 가금적 case문 아래에 두는 것이 좋다.  
  
	case WM_PAINT:
	{
		int number[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		...
		return 0;
	}
	
	case WM_KEYDOWN:
	{
		TCHAR buffer[9999];
		return 0;
	}
  
변수의 선언은 스코프가 열린 직후에 해야 하므로 case문 아래 둘 수 없으니 스코프를 열어서 그 안에 지역변수를 넣어야 한다. 초기화하지 않더라도 지역변수는 블록 안에 넣는 것이 더 유리하다. 만약 처리를 위한 변수가 너무 많다면 외부에 함수를 직접 만들어 사용하는 것도 하나의 방법이 될 수 있다.
