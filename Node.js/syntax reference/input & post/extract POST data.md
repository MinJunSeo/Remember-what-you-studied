# 서버로 전송한 데이터 객체화하기
  
우리가 서버로 데이터를 전송하였다면, 그 데이터를 가져와서 코드 내에서 활용할 수 있어야 한다. 그러기 위해서는 서버로 전송된 데이터를 코드 내에서 객체화 시켜서 사용하는 것이 보편적인데, 그 방법을 알아보자.  
  
1. 다음과 같이 데이터를 보낸 서버 경로를 확인하는 조건문을 삽입합니다.  
  
        else if(pathname === "/서버 경로")
        {
        }
    
    서버 경로는 HTML 태그 중 하나인 `<form>` 태그의 action에 부여된 값을 보면 알 수 있습니다.  
  
2. 전송된 데이터를 담기 위한 변수를 선언합니다.  
  
        else if(pathname === "/서버 경로")
        {
            var body = '';
        }
  
    서버에 전송된 데이터가 하나라면 변수로서 하나의 값이 할당되겠지만 복수 개의 값일 경우 각 데이터의 이름(HTML 태그에서 name에 부여된 값)에 하나의 값이 할당되어 있는 배열의 형태로 할당됩니다.  
    
        // Example
        { title: 'Node.js', description: 'Node.js is...' }
  
3. 다음과 같은 코드를 삽입합니다.  
  
        else if(pathname === "/서버 경로")
        {
            var body = '';
            request.on("data", function(data)
            {
                body = body + data;
            });
        }
  
    웹 브라우저가 POST 방식으로 데이터를 전송할 때 데이터의 양이 매우 많다면 처리하는 도중에 프로그램이 종료될 수도 있다. 이 코드는 일정 수치의 데이터가 전송되었다면 서버는 콜백 함수를 호출하도록 되어 있다. 그리고 인자인 data는 수신한 정보를 담고 있다.  
    
    body가 가지고 있던 데이터에 인자로 전달된 data를 추가하여 배열의 형태로 복수 개의 데이터를 저장할 수 있도록 한다.  
    
    그래도 데이터의 양이 너무 많다면 접속을 강제로 끊어버리는 일종의 보안 코드를 삽입하는데, 예제에서는 사용하지 않기로 한다.  
  
4. 다음의 코드를 삽입한다.  
  
        else if(pathname === "/서버 경로")
        {
            var body = '';
            request.on("data", function(data)
            {
                body = body + data;
            });
            request.on("end", function()
            {

            });
        }
  
    정보가 계속해서 들어오다가 더 이상 들어올 정보가 없다면 "end" 인자 다음에 있는 콜백 함수를 호출하도록 되어 있다. 그래서 이 콜백 함수가 실행되었을 때 정보 수신이 종료되었음을 의미한다.  
  
5. 전역 변수에 다음 변수를 선언한다.  
  
        var qs = require("querystring");
  
    Node.js가 가지고 있는 `querystring`이라는 모듈을 가지고 온다.  
  
6. 그 뒤, 다음과 같이 작성한다.  
  
        else if(pathname === "/서버 경로")
        {
            var body = '';
            request.on("data", function(data)
            {
                body = body + data;
            });
            request.on("end", function()
            {
                var post = qs.parse(body);
            });
        }
  
    이렇게 하면 post라는 변수에 지금까지 수신한 데이터를 모두 가지고 있게 된다.  
    
    이때 post는 배열이기 때문에 HTML 태그에서 name에 준 값을 사용하면 해당 name에서 입력한 데이터를 얻을 수 있다. 즉, 객체화가 가능해진다.  
    
    만약 title이라는 name에 Node.js라는 값이 들어있다면 다음과 같이 객체화할 수 있다.  
    
        var title = post.title;
  
