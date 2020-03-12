# PAINTSTRUCT struct
  
PAINTSTRUCT 구조체는 application의 윈도우의 작업 영역을 그리기 위한 정보를 가지고 있는 구조체입니다.  
  
## Syntax
  
	typedef struct tagPAINTSTRUCT {
			HDC         hdc;
			BOOL        fErase;
			RECT        rcPaint;
			BOOL        fRestore;
			BOOL        fIncUpdate;
			BYTE        rgbReserved[32];
	} PAINTSTRUCT;
  
이 구조체는 BeginPaint 함수에 의해 채워진다. fRestore, fIncUpdate, rgbReserved 멤버는 운영체제가 내부적으로 사용하는 런타임 데이터이므로 신경쓰지 않아도 된다.  
  
## hdc
  
그리기에 사용될 DC의 핸들값이며 BeginPaint가 리턴하는 DC의 핸들값과 동일하다.  
  
	hdc = BeginPaint(hWnd, &ps);
	Rectangle(hdc, 10, 10, 200, 200);
  
그래서 위 코드는 다음 코드와 완전히 동일하다.  
  
	BeginPaint(hWnd, &ps);
	Rectangle(ps.hdc, 10, 10, 200, 200);
  
지역변수 hdc를 선언해 사용하는 경우 코드가 더 간단해 보이는 특징이 있다. ps.hdc를 사용하는 경우는 지역 변수를 선언하지 않음으로써 메모리를 절약할 수 있고 관리가 편리하다는 특징이 있다.  
  
## fErase
  
배경을 지울 것인가 아닌가를 결정하는 멤버이다. 대부분의 프로그램은 이 멤버값이 통상 FALSE(= 0)이다. 하지만, 다음과 같은 경우에는 TRUE(0이 아닌 값)가 된다.  
  
1. 윈도우 클래스에 배경 브러시가 정의되어 있지 않다.  
  
	WndClass.hbrBackground = NULL;
  
2. WM_ERASEBKGND 메시지에서 배경을 지우지 않아 0(= FALSE)을 리턴한다.  
  
이 경우, 다음과 같이 값이 0이 아니게 된다.  
![캡처](https://user-images.githubusercontent.com/51042546/76500494-f741cf00-6483-11ea-9140-6e0181f87715.JPG)  
// 위 사진은 fErase.cpp 예제를 실행시킨 결과입니다.  
  
## rcPaint
  
그리기를 해야 할 사각 영역을 가진다. 이때 이 영역은 클리핑 영역을 포함하는 최소한의 사각 영역이다. 보통은 이 영역을 무시하고 전체 윈도우를 다 그리지만 이 영역을 잘 활용할 경우 그리는 속도를 향상시킬 수 있다.  
  
다음 예제는 어디까지나 rcPaint의 효율적인 활용을 위해 만든 극단적인 예제입니다.  
  
	// 전체 소스는 rcPaint1.cpp 예제를 확인하세요.
	LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
	{
		HDC hdc;
		PAINTSTRUCT ps;
		RECT rt;
		int x, y;

		switch (iMessage)
		{
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			GetClientRect(hWnd, &rt);
			for (y = 0; y < rt.bottom; y++)
			{
				for (x = 0; x < rt.right; x++)
				{
					Ellipse(hdc, x, y, x + 20, y + 20);
				}
			}
			EndPaint(hWnd, &ps);
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}

		return (DefWindowProc(hWnd, iMessage, wParam, lParam));
	}
  
위 예제를 보면 WM_PAINT 메시지에서 작업 영역 전체를 왼쪽에서 오른쪽으로, 위에서 아래로 원을 계속해서 그려나간다. 이는 그리기 연산이 복잡한 상황을 연출한 것이다. 최대한 많은 연산을 수행하게 만들수록 rcPaint의 효과를 분명히 볼 수 있다.  
  
실행 결과는 다음과 같다.  
![캡처](https://user-images.githubusercontent.com/51042546/76501516-bba80480-6485-11ea-8b50-aa38922d0843.JPG)  
  
작업 영역의 좌표 한 번 변경될 때마다 원을 그리니 웬만한 컴퓨터에서도 꽤나 시간이 걸리는 모습을 볼 수 있다. 이 상황에서 윈도우의 일부분만이 무효화되었다고 가정해 보자.  
  
무효화된 부분이 생겼기 때문에 WM_PAINT 메시지가 전달되고 그로 인해 윈도우를 다시 그리기 시작한다. 물론 운영체제에 의해 무효화되지 않은 부분은 다시 그려지지 않지만 쓸데없이 전체 루프를 반복함으로써 시간이 낭비된다.  
  
이럴 때 PAINTSTRUCT 구조체의 rcPaint 멤버를 사용하여 클리핑 영역에 대해서만 루프를 돌게 하면 실행 시간을 훨씬 아낄 수 있다.  
  
	// 전체 소스는 rcPaint2.cpp 예제를 확인해주세요.
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rt);
		for (y = ps.rcPaint.top; y < ps.rcPaint.bottom; y++)
		{
			for (x = ps.rcPaint.left; x < ps.rcPaint.right; x++)
				Ellipse(hdc, x, y, x + 20, y + 20);
		}
		EndPaint(hWnd, &ps);
		return 0;
  
작업 영역 전체에 대해 루프를 돌지 않고 무효화된 영역에 대해서만 루프를 돌게 된다. 실행 결과는 동일하지만 화면 일부가 무효화되었을 때 다시 그리는 속도는 훨신 우세하다. 두 예제를 번갈아 실행해 보면서 확인해보길 바란다.  
  
여기서 주의할 점은 rcPaint를 사용하지 않더라도 불필요한 출력은 발생하지 않는다는 것이다. 운영체제에 의해 무효화된 영역 이외의 부분은 출력하지 않는다. rcPaint를 사용한 이유는 무효화되지 않은 곳에서는 필요하지 않은 연산을 아예 하지 않음으로써 불필요한 실행 시간을 줄이기 위함이다.
