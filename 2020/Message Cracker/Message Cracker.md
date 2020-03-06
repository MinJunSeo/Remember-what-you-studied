# 메시지 크래커
  
## 메시지 크래커의 배경
  
메시지들은 각각 wParam, lParam에 고유의 정보를 담아 보내며 메시지 처리 함수는 wParam, lParam을 전달받아야 자신에게 주어진 일을 제대로 수행할 수 있습니다.  
  
여기서 조금 더 생각해보면 wParam, lParam에 전달되는 추가 정보를 조금 더 쓰기 좋은 형태로 넘겨준다면 메시지 처리 함수 내에서 처리하기 더 편리해질 것이다. 하나 예를 들어보자.  
  
WM_SIZE 메시지는 wParam에 크기 변경 상태를, lParam의 상하위 워드에 변경된 후의 높이와 폭을 전달하는데 이 인수를 다음과 같이 넘겨주는 것이다.  
  
	LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
	{
		switch (iMessage)
		{
		case WM_SIZE:
			return OnSize(hWnd, wParam, LOWORD(lParam), HIWORD(lParam));
		......
	}

	LRESULT OnSize(HWNd hWnd, UINT state, int cx, int cy)
	{
		......
	}
  
이제 OnSize라는 메시지 처리 함수에서는 state, cx, cy 인수로 추가 정보를 받게 되고 이 인수를 사용하는 것이 wParam, lParam을 사용하는 것보다는 훨씬 더 편리하다. 그 이유는 wParam, lParam에서 필요한 정보를 직접 추출하는 과정이 생략되어서 그렇다.  
  
이런 서비스를 하는 것이 바로 메시지 크래커(Message Cracker)이다. 메시지 크래커는 WndProc에 들어갈 함수 호출문과 메시지 처리 함수의 원형을 매크로로 잘 정의해 놓은 것이다.
  
## 메시지 크래커의 사용 방법
  
메시지 크래커를 사용하기 위해서는 기본적으로 포함되는 <Windows.h> 헤더 파일 이외에 <windowsx.h>라는 헤더파일도 선언해야 한다.  
  
	// 메시지 크랙커를 사용하는 경우
	#include <windowsx.h>
  
그 다음에는 메시지 처리 함수의 원형을 정의한다. 이번에는 단순히 WM_SIZE 메시지만 처리해보도록 하겠다.  
  
	// 메시지 처리 함수의 원형 정의
	void MsgCrk_OnSize(HWND hWnd, UINT state, int cx, int cy);
  
그 다음 WndProc에는 다음과 같은 매크로문을 작성한다.  
  
	LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
	{
		switch (iMessage)
		{
			HANDLE_MSG(hWnd, WM_SIZE, MsgCrk_OnSize);
		}
		
		return (DefWindowProc(hWnd, iMessage, wParam, lParam));
	}
  
그 다음, 메시지 처리 함수를 정의한다.  
  
	void MsgCrk_OnSize(HWND hWnd, UINT state, int cx, int cy)
	{
		......
	}
  
이렇게 되면, 해당 윈도우 프로그램에서 WM_SIZE 메시지가 전달될 때마다 HANDLE_MSG 매크로에 의해 MsgCrk_OnSize 함수가 대신 호출되어 해당 함수 내에 있는 내용을 처리한다.  
  
## HANDLE_MSG
  
메시지 크래커를 쓰는 방법은 알겠는데, 갑자기 등장한 HANDLE_MSG 매크로에 대해 의문이 생기지 않을 수 없다. switch 내인데도 불구하고 case를 사용하지 않았고, 심지어 return도 하지 않는다. 대체 어떻게 정의되어 있는걸까?  
  
우선 HANDLE_MSG는 다음과 같은 형태로 사용한다.  
  
	HANDLE_MSG(윈도우 핸들, 메시지, 처리 함수);
  
그리고 HANDLE_MSG는 <windowsx.h> 헤더 파일에 다음과 같이 정의되어 있다.  
  
	#define HANDLE_MSG(hWnd, message, fn)	\
		case (message):
			return HANDLE_##message((hWnd), (wParam), (lParam), (fn))
  
switch문 내에서 사용되므로 case문으로 정의되어 있다. 또한 스스로 return도 해주고 있으므로 우리가 직접 return 할 필요도 없다.  
  
## 메시지 크래커의 장점
  
1. 소스를 읽기 쉽다.  
2. 유지, 보수가 편리하다.  
3. 실수를 방지한다.  
  
위 세 가지 이유는 매크로문에 의해 WndProc에 작성되는 코드의 줄이 줄어들게 되어 가독성이 높아지고, 무엇보다 해당 메시지에서 문제가 생기면 해당 메시지 처리 함수만 찾아가서 오류를 고쳐주면 된다. 이러한 점에서 개발자의 실수 또한 자연스럽게 줄어들 수 있다.  
  
4. 인수의 의미를 쉽게 알 수 있도록 해 준다.  
  
메시지 크래커를 사용하기 위해서 메시지 처리 함수의 원형은 wParam, lParam에 전달되는 의미를 그대로 인수로 전달받기 때문에 인수의 의미를 쉽게 알 수 있어 메시지 처리에 도움이 될 수 있다.  
  
5. 이식에 유리하다.  
  
운영체제가 업그레이드되면 메시지의 추가 정보가 바뀔 수도 있는데 메시지 크래커는 운영체제의 변경사항을 반영하여 다시 배포될 것이므로 소스는 손대지 않아도 다시 컴파일하기만 하면 된다.  
  
## 메시지 크래커의 단점
  
1. 사용하기 위해서는 <windowsx.h> 헤더 파일을 참고해야 한다.  
  
가뜩이나 API 함수들의 양은 엄청나게 많은데 메시지 크래커의 함수 원형까지 외워야 한다면 정말 머리가 터질 것이다. 다행히도 <windowsx.h> 헤더 파일에는 주석으로 메시지 처리 함수의 원형이 적혀 있기 때문에 컷 & 페이스트 하면 금방 할 수 있지만 결국은 사용하기 위해 <windowsx.h>를 항상 참고해야 하는 불편함을 동반한다.  
  
2. 일부 메시지는 기존의 지식과 조금 다르게 설정되어 있는 경우가 있다.  
  
WM_CREATE 메시지는 초기화를 무사히 했을 경우 0, 에러가 발생했을 경우 -1을 리턴하는 것이 일반적으로 알고 있는 지식이다. 하지만 메시지 크래커의 OnCreate 함수는 BOOL 형으로 되어 있으며 return 0이 return FALSE로 해석되어 생성을 중지하는 경우가 발생할 수 있다.  
  
3. 짧은 소스에서 사용하면 오히려 가독성이 떨어진다.  
  
당연한 말이지만 남용하면 안 된다. 메시지 크래커는 어디까지나 WndProc 안에 20개 이상의 메시지를 처리하는 등 꽤나 길어지는 경우에 가독성 및 유지, 보수를 위해 사용하는 것이다. 짧게 작성되는 코드에서 사용하면 오히려 코드가 길어지게 된다.  
  
## 추가로 더 알아봅시다!
  
아까 HANDLE_MSG 매크로의 정의를 자세히 봤다면 생소한 부분이 있었을지도 모른다. 바로 ## 부분이다. 코드가 작성되어 있는 부분에 전처리문인 것을 알려주는 #이 두 개나 들어가 있다니, 뭔가 이상하다고 생각하지 않나?  
  
##은 매크로나 typedef 문과 함께 사용되는 경우가 많은데, 매크로 치환이 끝난 후 자신은 주변의 공백과 함께 스스로 제거되는 기능을 한다. 예를 들어,  
  
	#define CONNECT(a, b) a##b
  
라고 정의되었을 경우,  
  
	CONNECT(Windows, API)  
  
는 Windows##API로 치환된 후 ##이 제거됨으로써 WindowsAPI가 된다.
