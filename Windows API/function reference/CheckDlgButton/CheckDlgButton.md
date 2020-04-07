# CheckDlgButton
  
	#include <Winuser.h>
	
	BOOL CheckDlgButton(HWND hDlg, int nIDButton, UINT uCheck);
  
체크 상태를 가지는 버튼의 체크 상태를 변경하는 함수이다. 이때 해당 차일드로 BM_SETCHECK 메시지를 보낸다.  
  
## Parameters
  
`hDlg`  
체크 상태를 변경하고자 하는 버튼을 포함하는 대화상자의 핸들이다.  
  
`nIDButton`  
체크 상태를 변경하고자 하는 버튼의 ID이다.  
  
`uCheck`  
버튼의 체크상태를 지정한다. 다음과 같은 값들을 지정할 수 있다.  
  
값 | 설명
---|------
BST_CHECKED | 버튼을 체크한다.
BST_INDETERMINATE | 버튼을 grayed로 체크한다. 이 값은 BS_3STATE나 BS_AUTO3STATE 스타일을 가지고 있는 버튼에게만 지정할 수 있다.
BST_UNCHECKED | 버튼을 체크 상태를 해제한다.
  
## Return value
  
이 함수가 성공하면 0이 아닌 값을, 실패하면 0을 반환한다.
