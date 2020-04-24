# eval
  
	eval(string);
  
eval은 JavaScript의 내장 함수로, 문자열로 표현된 JavaScript의 코드를 실행시켜주는 함수이다.  
  
예를 들어, 다음의 코드는  
  
	console.log(eval("2 + 2"));
  
2 + 2로 출력이 되지 않고 4로 출력된다. 즉, 문자열 안에 있던 연산식이 수행되어 나온 결과가 출력되었다고 볼 수 있다.  
  
실제로 eval은 문자로 이루어진 JavaScript의 코드를 실행하여 얻게 된 값을 반환한다. 물론 값이 없다면 undefined를 반환한다.
