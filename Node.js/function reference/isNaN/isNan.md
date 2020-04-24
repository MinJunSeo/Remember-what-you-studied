# isNaN
  
	isNaN(value);
  
매개변수가 NaN(Not a Number)인지 판별하는 내장 함수이다.  
  
## Parameters
  
`value`  
NaN인지 판별하고자 하는 값  
  
## Return value
  
주어진 값이 NaN이라면 true를, 아니라면 false를 반환한다.  
  
value 예시 | 반환값
-----------|-------
123.123 | false
"123.123" | false
"Not a Number" | true
123 * 123 | false
"123 * 123" | true
  
