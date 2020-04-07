# Messaeg Deadlock
  
한 메시지 처리 루틴 중에서 다른 메시지의 처리를 해야 하는 상황이면 흔히 우리는 메시지를 처리하는 도중 SendMessage 함수를 사용하여 처리하고자 하는 메시지를 먼저 처리한 후에 이어서 처리를 하는 방식을 사용한다.  
  
	// 예를 들어 이렇게 말이다.
	case WM_CREATE:
		SetTimer(hWnd, 1, 5000, NULL);
		SendMessage(hWnd, WM_TIMER, 1, 0); // WM_CREATE 메시지 처리 중에 WM_TIMER 메시지를 보낸다.
		return 0;
  
그런데 SendMessage 함수는 메시지를 받은 윈도우 프로시저가 리턴하기 전에는 리턴하지 않는다. 즉, SendMessage 함수로 보낸 메시지를 해당 윈도우 프로시저가 처리하기 전까지는 해당 함수는 리턴하지 않는다는 뜻이다. 의외로 이 특성을 몰라 버그를 일으키기도 한다.  
  
	// 다음과 같은 상황에 처해있다고 하자.
	case WM_...:
		처리 1;
		SendMessage(hWnd, WM_......, 0, 0);
		처리 2;
  
hWnd 윈도우에게 어떤 작업을 하기 위해 WM_......라는 메시지를 보냈다. 그런데 이 작업을 처리하는데 30초가 걸린닫고 가정해 보자. 그렇다면 SendMessage 함수 다음에 있는 처리 2는 30초 이후에나 수행될 수 있다.  
  
이렇게 되면 특정 메시지를 보냈을 경우, 작업 시간이 평소보다 오래 걸릴 수 있다는 점이다. 특히 SendMessage는 윈도우 간의 통신에 자주 사용되는 메시지인만큼, 통신에서 저런 상황이 발생한다면 보낸 쪽 윈도우는 일시적으로 데드락 상태가 된다.  
  
확실히 코드를 작성할 때는 저런 상황이 발생하지 않도록 충분히 주의를 기울이겠지만 어쩔 수 없이 저런 상황이 발생할 수도 있다. 그리고 프로그래머도 인간이니 실수를 할 수도 있지 않은가?  
  
이런 상황을 해결할 수 있는 방법 중 하나는 메시지가 다른 스레드로부터 전달되었을 때는 즉시 리턴하여 메시지를 보낸 윈도우도 다음 처리를 바로 처리할 수 있도록 만드는 것이다. 다음과 같이 말이다.  
  
	case WM_...:
		if (InSendMessage())
		{
			ReplyMessage(TRUE);
			처리;
		}
		return 0;
  
다른 윈도우로부터 통신으로 받는 메시지의 경우 다음과 같이 작성하면 데드락 상황을 예방할 수 있다.  
  
InSendMessage 함수는 해당 메시지가 자신과 다른 스레드로부터 전달된 것이라면 0이 아닌 값을 반환한다. 그렇다는 것은 SendMessage 같은 함수로 메시지가 전달되었다는 뜻이므로 바로 반환하여 해당 윈도우도 다음 처리를 할 수 있도로 한다.  
  
ReplyMessage는 인수로 전달된 값을 SendMessage로 리턴합니다. 이렇게 되면 SendMessage도 바로 리턴을 하기 때문에 해당 윈도우도 바로 처리할 수 있습니다.  
  
또 다른 방법으로는 메시지를 SendMessage 함수를 이용하지 말고 다음과 같은 함수들을 이용하는 것이다.  
  
	BOOL SendNotifyMessage(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	LRESULT SendMessageTimeout(HWND hWnd, UINT Msg, WPARAM wParam LPARAM lParam,
		UINT fuFlags, UINT uTimeout, PDWORD_PTR lpdwResult);
  
SendNotifyMessage는 hWnd 인수로 전달된 윈도우 핸들이 만약 다른 스레드의 윈도우의 핸들일 경우 대기를 하지 않고 즉시 리턴한다.  
  
SendMessageTimeout 함수는 인수로 지정한 일정 시간 이상이 지나면 메시지의 처리 여부에 상관없이 즉시 리턴한다.
