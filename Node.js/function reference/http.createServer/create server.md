# http.createServer
  
	var http = require('http');
	
	http.createServer([options][, requestListener])
  
## Parameters
  
[]의 경우 인자를 주지 않아도 동작한다는 뜻으로, 생략해도 된다는 의미를 지닌다.  
  
`options` type : &lt;Object&gt;  
  
`requestListener` type : &lt;Function&gt;  
  
## Return value
  
&lt;http.Server&gt;  
  
http.Server의 새로운 객체를 반환한다. 보통 이 반환값을 통해 `server.listen();`의 형태를 사용하는 것을 볼 수 있다.  
  
`server.listen();`은 요청에 응답할 수 있도록 HTTP 서버를 구동하는 역할을 한다. 이건 다양한 형태로 서버를 구동시킬 수 있다.  
  
## Remark
  
이 함수를 이용하여 우리는 웹 서버를 만들 수 있다.  
  
그리고 이 웹 서버에서 외부에서 요청이 들어올 때마다 웹 서버는 requestListener 인수로 전달된 함수를 호출한다. 그 함수의 형태는 다음과 같다.  
  
	function(request, response) {}
  
함수의 첫 번째 인자인 `request`는 웹 서버에 들어온 요청에 대한 여러 가지 정보를 가지고 있는 객체이다. 두 번째 인자인 `response`는 해당 함수 안의 구현을 통해 사용자에게 전송하고 싶은 정보(파일을 찾는데 성공했는지에 대한 성공값, 웹 페이지에 보여주고자 하는 내용 등)를 담을 수 있는 객체이다.  
