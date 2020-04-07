# BitBlt function
  
	#include <Wingdi.h>
	
	BOOL BitBlt(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop);
  
DC간의 영역끼리 고속 복사만을 수행하는 함수이다.  
  
두 DC는 호환되어야 하나 만약 색상 포맷이 호환되지 않을 경우 원본의 색상 포맷을 복사본의 포맷에 맞게 변경한다.  
  
비트맵은 원본 그대로 복사가 되지만 rop 스타일에 따라 배경과 함께 논리 연산되어 비트맵의 일부가 변형될 수 있다. 원본의 비트맵은 복사본의 맵핑모드에 따라 크기가 커지거나 작아지기도 한다.  
  
모든 장치가 BitBlt 함수를 지원하는 것은 아니므로 GetDeviceCaps를 사용하여 BitBlt 함수를 사용할 수 있는 장치인지 확인해봐야 한다.  
  
## Parameters
  
`hdc`  
비트맵이 복사될 DC의 핸들이다.  
  
`x`  
비트맵이 복사될 x 좌표를 지정하는 인수이다.  
  
`y`  
비트맵이 복사될 y 좌표를 지정하는 인수이다.  
  
`cx`  
비트맵이 복사될 영역의 넓이를 지정하는 인수이다.  
  
`cy`  
비트맵이 복사될 영역의 높이를 지정하는 인수이다.  
  
`hdcSrc`  
복사될 비트맵의 원본이 저장되어 있는 DC의 핸들이다.  
  
`x1`, `x2`  
원본의 비트맵을 복사하고자 하는 x, y좌표 값이다. 이 값이 0이면 비트맵 전체를 복사한다. 복사 영역의 넓이와 높이는 `cx`와 `cy`의 값으로 결정된다.  
  
`rop`  
raster-operation 코드이다. 브러시, 원본, 복사본의 비트맵 색상이 논리 연산될 방법을 지정한다.  
그 중 일부는 다음과 같다.  
  
값 | 설명
---|------
BLACKNESS | 대상 영역을 검정색으로 가득 채운다.  
CAPTUREBLT | 반투명 창들을 포함한다.
DSTINVERT | 화면을 반전시킨다.
MERGECOPY | 원본 비트맵과 대상 화면을 AND 연산한다.
MERGEPAINT | 원본 비트맵과 대상 화면을 OR 연산한다.
NOMIRRORBITMAP | 비트맵이 미러링되지 않는다.
NOTSRCCOPY | 원본을 반전시켜 복사한다.
NOTSRCERASE | 원본의 색상과 복사본의 영역을 Boolean OR 연산자로 연산한 뒤, 결과를 반전해 나온 색상을 지정한다.
PATCOPY | `hdc`에 지정된 브러쉬로 대상 비트맵을 그린다.
PATINVERT | Boolean XOR 연산자로 `hdc`에 저장된 브러시와 대상 영역을 결합한다.
PATPAINT | Boolean OR 연산자로 `hdc`에 저장된 브러시와 대상 영역을 결합한다.
SRCAND | 원본과 대상의 색상을 Boolean AND 연산자로 결합한다.
SRCCOPY | 원본 영역을 대상 영역에 복사한다.
SRCERASE | 원본과 대상의 반전된 색상을 Boolean AND 연산자로 결합한다.
SRCINVERT | 원본의 색상과 대상의 색상을 Boolean XOR 연산자로 결합한다.
SRCPAINT | 원본과 대상의 색상을 Boolean OR 연산자로 결합한다.
WHITENESS | 대상 영역을 흰색으로 채운다.
  
## Return value
  
수행 중 예외가 발생하지 않으면 0이 아닌 값을, 발생하면 0을 반환한다.  
GetLastError 함수를 사용해 예외에 대한 정보를 얻을 수 있다.
