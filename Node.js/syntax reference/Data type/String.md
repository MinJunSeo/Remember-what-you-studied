# String
  
JavaScript에서 문자열은 ''(작은 따옴표)나 ""(큰 따옴표) 중 어느것을 사용해도 문자열로 표현할 수 있다. 단, 작은 따옴표로 시작했으면 작은 따옴표로, 큰 따옴표로 시작했다면 큰 따옴표로 끝내야 한다.  
  
	console.log('1' + '1');
  
다음과 같이 문자열을 + 연산자로 연산하게 되면 두 문자열을 이어준다. 그래서 출력 결과로 `11`이 출력된다.  
  
	console.log("Node.js".length);
  
문자열의 메서드 중 lenght 메서드를 사용하면 해당 문자열의 길이를 반환해준다. 그래서 출력 결과로 `7`이 출력된다.
  
## Template Literal
  
문자열을 조금 더 쉽게 작성할 수 있도록 도움을 주는 문자들에 대하여 알아보자.  
  
먼저 코드 상에서 문자열을 줄바꿈하고 싶을 때가 있다. 문자열이 매우 길다면 IDE 편집기 화면을 넘어가기 때문에 작업이 불편하기 때문이다. 하지만 그냥 Enter로 줄바꿈을 하면 에러가 발생한다.  
  
	// Example
	var letter = "String 
	is String."; // 에러
  
코드 상에서 문자열을 줄바꿈하고 싶다면 `\`를 사용하면 된다. `\`를 내가 줄바꿈하고 싶은 곳에다가 표현하면 에러가 나지 않고 줄바꿈을 할 수 있다.  
  
	// Example
	var letter = "String \
	is String.";  // 컴파일 OK
  
그러나 `\`는 코드 상에서의 줄바꿈을 의미하고, 실제 출력에서의 줄바꿈을 의미하지는 않는다. 위의 변수를 `console.log(letter);` 구문으로 출력해보면 `String is String`으로 출력된다.  
  
출력에서 개행을 하고 싶다면 개행하고자 하는 부분에 `\n`문자를 넣어줘야 한다.  
  
	// Example
	var letter = "My name is Node.js!\n\
	What is your name?";
  
letter 변수를 출력해보면 \n을 넣어준 부분에서 개행이 이루어짐을 확인할 수 있다.  
  
그런데 이러한 것들을 일일이 넣어주려면 귀찮고 힘들다. 그래서 이를 보완한 것이 바로 Template Litral이다.  

	var letter = "Dear " + name + "\n\nLorem ipsum dolor sit amet, \
	consectetur adipisicing elit, sed do eiusmod tempor incididunt ut \
	labore et dolore magna aliqua. " + name + "Ut enim ad minim veniam, \
	quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commod \
	consequat. Duis ute irure dolor in reprehenderit in voluptat velit esse \
	cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidat \
	non proident, sunt in culpa egoing qui officia deserunt mollit anim id \
	est laborum. " + name;
  
그러면 이제 다음 문자열을 Template Litral으로 바꾸어 보자.  
  
위 변수를 복사한 뒤, 시작과 끝을 \` 문자로 묶어준다. 그리고 세미콜론은 \` 뒤로 뺀다.   
  
	var letter = `Dear " + name + "\n\nLorem ipsum dolor sit amet, \
	consectetur adipisicing elit, sed do eiusmod tempor incididunt ut \
	labore et dolore magna aliqua. " + name + "Ut enim ad minim veniam, \
	quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commod \
	consequat. Duis ute irure dolor in reprehenderit in voluptat velit esse \
	cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidat \
	non proident, sunt in culpa egoing qui officia deserunt mollit anim id \
	est laborum. " + name`;
  
그 뒤, + 결합 연산자로 변수와 연결하는 부분은 `${변수}`의 형식으로 변경한다. 물론 앞이나 뒤에 있는 따옴표는 제거한다.  
  
	var letter = `Dear ${name}\n\nLorem ipsum dolor sit amet, \
	consectetur adipisicing elit, sed do eiusmod tempor incididunt ut \
	labore et dolore magna aliqua. ${name} Ut enim ad minim veniam, \
	quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commod \
	consequat. Duis ute irure dolor in reprehenderit in voluptat velit esse \
	cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidat \
	non proident, sunt in culpa egoing qui officia deserunt mollit anim id \
	est laborum. ${name}`;
  
개행하는 곳은 그냥 Enter 키를 입력하면 된다.  
  
	var letter = `Dear ${name}

	Lorem ipsum dolor sit amet, \
	consectetur adipisicing elit, sed do eiusmod tempor incididunt ut \
	labore et dolore magna aliqua. ${name} Ut enim ad minim veniam, \
	quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commod \
	consequat. Duis ute irure dolor in reprehenderit in voluptat velit esse \
	cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidat \
	non proident, sunt in culpa egoing qui officia deserunt mollit anim id \
	est laborum. ${name}`;
  
실행 결과는 다음과 같다.  
  
	Dear Node.js

	Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Node.js Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commod consequat. Duis ute irure dolor in reprehenderit in voluptat velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidat non proident, sunt in culpa egoing qui officia deserunt mollit anim id est laborum. Node.js
  
`${ }`의 식에서 {} 안에 숫자들의 연산을 넣어도 괜찮은데 예를 들어 `1 + 1`을 넣게 되면 해당 연산 결과인 2가 출력된다.
