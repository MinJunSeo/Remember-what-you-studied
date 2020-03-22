# TextOut function
  
	BOOL TextOut(HDC hdc, int x, int y, LPCWSTR lpString, int c);
  
인수로 전달된 DC의 핸들 hdc에 저장되어 있는 폰트, 배경색, 글자 색 등의 정보를 참조하여 화면에 문자열을 출력한다.  
  
작업 영역 기준으로 (x, y)에 lpString이 가리키는 곳에 있는 문자열을 출력한다.  
  
**TextOut 함수는 문자열의 종료 문자인 NULL 문자를 인식하지 않는다. 따라서, 반드시 마지막 인수인 c에 문자열의 길이를 전달하여 문자열의 종료를 알려야 한다.**  
  
그런데 직접 숫자로 문자열의 길이를 전달하는 것은 좋지 않다. 특히 영어랑 숫자를 제외한 한글 등의 문자가 문자열에 담겨있는 경우가 문제가 된다. "윈도우"라는 문자열이 멀티바이트에서는 8바이트지만 유니코드에서는 4바이트로 측정되기 때문이다. 그래서 보통은 문자열을 LPCWSTR 포인터나 배열에 담은 뒤, lstrlen 함수를 사용해 문자열의 길이를 전달하는 방법을 사용한다.  
  
하지만 TextOut 함수는 문자열만 취급하기 때문에 정수를 출력하고 싶다면 wsprintf 함수를 사용하여 배열에 해당 정수를 포함한 문자열을 저장한 뒤, TextOut 함수로 화면에 출력해야 한다.  
  
	// example
	LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
	{
	    HDC hdc;
	    PAINTSTRUCT ps;
	    int num = 10;
			TCHAR str[20];
			
			switch (iMessage)
			{
			case WM_PAINT:
			    hdc = BeginPaint(hWnd, &ps);
					wsprintf(str, TEXT("num = %d"), num);
					TextOut(hdc, 10, 10, str, lstrlen(str));
					EndPaint(hWnd, &ps);
					return 0;
			......
			}
	}
  
참고로 SetTextAlign 함수를 활용하면 화면에 출력되는 좌표나 문자열의 정렬 상태 등을 조정할 수 있다.  
  
## Parameters
  
	hdc
  
화면에 출력을 위해 전달받는 DC의 핸들이다. 보통 GetDC나 BeginPaint 함수로 구해진 DC의 핸들이 전달된다.  
  
	x, y
  
작업 영역을 기준으로 문자열이 출력되고자 하는 x, y 좌표의 값을 전달한다.  
  
	lpString
  
문자열을 가리키고 있는 포인터이다. TEXT 매크로를 직접 사용해도 상관없다.  
  
	c
  
lpString이 가리키고 있는 문자열의 길이이다. 유니코드와의 호환을 위해 lstrlen 함수로 문자열의 길이를 구하는 것을 추천한다.  
  
## Return value
  
이 함수가 성공하였다면 0이 아닌 값을, 실패하였다면 0을 반환한다.
