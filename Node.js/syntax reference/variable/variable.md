# variable
  
JavaScript에서는 자료형을 굳이 쓰지 않고 값만 대입하면 변수를 만들 수 있다.  
  
	// Example
	a = 1;
  
다음과 같은 경우 a라는 변수가 만들어지고 1이라는 값이 할당된다. `console.log(a);`로 출력해보면 1이 출력된다.  
참고로 JavaScript에서 주석을 달고 싶다면 `//` 기호를 사용하면 된다.  
  
변수를 만들 때 물론 위와 같이 만들어도 아무런 문제가 없지만 다음과 같이 **var** 키워드를 붙여주는 것이 좋다. JavaScript에서는 var를 붙인 변수와 붙이지 않은 변수에 대한 차이가 있는 것 같다.  
  
	// Example
	var a = 1;
  
참고로 변수를 처음으로 만들 때만 var를 붙이면 된다. 후에 다른 값을 할당하는 등 해당 변수를 사용하는 과정에서 var 키워드를 붙일 필요는 없다.  
  
	// Example
	var a = 1;
	a = 2;    // var를 붙이지 않아도 된다.
  
변수는 여러 가지 역할이나 의미를 가지고 있지만 그 중 가장 대표적인 것은 바로 **자료에 이름을 붙이는 것**이다. 또한 그 이름을 통해 해당 자료를 이용할 수 있다는 점이다.  
  
	// Example
	var letter = "Computer Security Division Common Tasks";    // 문자열에 letter라는 이름을 붙임
	console.log(letter);    // 화면에 letter라는 이름의 자료를 출력함
  
만약 문자열을 이룬 단어가 1억 개가 되는 문자열을 출력한다고 했을 때 그냥 출력하는 것보다는 당연히 변수를 사용하는 편이 코드가 더 간결해보인다.  
  
변수에 이름을 잘 부여하면 해당 변수가 어떤 자료를 가지고 있을지 추측할 수 있게 도와준다. 그래서 변수의 이름은 보관할 자료와 연관된 이름으로 짓는 것이 좋다.  
  
변수를 잘 활용하면 코드에서 중복되는 부분을 줄일 수 있어 좋은 프로그램을 만드는 데 기여할 수 있다.  
예를 들어, 다음과 같은 문자열이 있다고 하자.  
  
	letter = "bread and butter. 5 and 5 makes 10. She came in and took her coat off. Go and get me a pen please. We talked for hours.’ ‘And what did you decide? Miss another class and you’ll fail. He tried and tried but without success. I like city life but there are cities and cities."
  
다음 문자열을 보면 "and"라는 문자열이 많이 반복되고 있다. 이렇게 반복되는 자료가 많아지면 많아질수록 여러 문제가 나타나는데 대표적으로 다음과 같다.  
  
1. 데이터의 양이 많아진다. 그로 인해 코드의 양도 많아지게 된다.  
2. 반복되는 자료를 사용한 곳이 같은 의미에서 사용한 것인지 파악하는 것이 어려워진다.  
3. 반복되는 자료를 수정할 때 전체에서 한 두개 정도만 빼고 수정해야 하면 기계적으로는 불가능하다.  
  
이런 경우, 변수를 통해 해결할 수 있다.  

	var key = "and"    // 반복되는 문자열을 변수에 저장한다.
	var letter = "bread " + key + " butter. 5 " + key + 
	"5 makes 10. She came in " + key + " took her coat off. Go " + key +
	" get me a pen please. We talked for hours." + key +
	" what did you decide? Miss another class " + key +
	" you’ll fail. He tried " + key +
	" tried but without success. I like city life but there are cities " + 
	key + " cities." // + 연산자로 문자열과 변수를 이어준다.
  
다음과 같이 변수를 활용하면 줄바꿈도 활용할 수 있어 가독성도 높아지며, and라는 키워드를 바꿀 때 한 번에 바꿀 수 있다.
