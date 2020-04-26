# Array
  
JavaScript의 객체 형태 중 하나인 배열이다. 배열은 순차적으로 데이터를 정리할 때 사용하면 편리한 자료 구조이다.  
  
## 선언하는 방법
  
`new Array()`의 형태로 배열을 생성한 뒤, 값을 직접 지정하는 방식을 사용할 수 있다.  
  
	var arr = new Array();
	arr[0] = "Min";
	arr[1] = "Jun";
  
하지만 이렇게 일일이 값을 직접 지정하는 것은 상당히 불편합니다. 그래서 new를 통해 배열을 생성할 때 바로 값을 지정할 수도 있습니다.  
  
	var arr = new Array( "Min", "Jun" );
  
혹은 배열의 리터럴인 []를 사용하여 new를 사용하지 않고 바로 생성할 수도 있습니다.  
  
	var arr = [ "Min", "Jun" ];
  
## Array.lenght
  
배열 객체의 lenght 속성은 배열의 길이를 반환하는 속성입니다. 부호 없는 32비트 정수형으로 반환하는데, 이때 배열의 마지막 요소의 인덱스보다 1 큰 값이 반환됩니다.  
  
lenght 속성에 값을 부여할 수 있는데, 이렇게 될 경우 배열의 길이가 늘어납니다. 배열의 길이가 늘어남과 동시에 요소도 늘어나게 되고 늘어난 요소는 undefined 값으로 할당됩니다. (Node.js에서는 <1 empty item>로 값이 출력됩니다.)  
  
	// example
	var arr = [ "Min", "Jun", "Seo" ];
	arr.length = 4;
	console.log(arr);
	
	// result
	[ 'Min', 'Jun', 'Seo', <1 empty item> ]
  
그러나 lenght 속성이 항상 배열에 정의된 원소의 수를 나타내지는 않는다.  
