# 사용자에게 입력 받고 데이터 전송하기
  
    <input type = "text">
  
다음과 같이 input 태그와 type을 지정하면 해당 type에 맞는 데이터를 사용자에게서 받아올 수 있는 입력창이 만들어진다.  
![input](https://user-images.githubusercontent.com/51042546/79300782-b164a480-7f22-11ea-9e2b-5ea7bcc54b22.JPG)  
  
만약 여러 줄을 입력하고 싶다면 다음과 같은 태그를 활용하면 된다.  

    <textarea></textarea>
  
![textarea](https://user-images.githubusercontent.com/51042546/79300901-09031000-7f23-11ea-8095-ec593a6c6975.JPG)  
  
참고로 오른쪽 끝을 드래그하면 크기를 늘릴 수 있다.  
  
사용자에게서 입력을 받으면 입력을 종료한다는 의미의 버튼이 있어야 하는데 그것은 `submit` type을 이용하면 된다.  
  
    <input type = "submit">
  
이렇게 하면 제출이라는 텍스트가 적힌 전송 버튼이 생성된다.  
![submit](https://user-images.githubusercontent.com/51042546/79301054-79aa2c80-7f23-11ea-9670-e1367c1b2a00.JPG)  
  
하지만, 전송 버튼을 누른다고 해서 데이터가 서버로 전송되는 것은 아니다. 데이터가 서버로 전송되기 위해서는 어디로 보낼지 알려주는 주소가 필요하다.  
  
그러기 위해서는 우선 전송하고자 하는 데이터를 가지고 있는 폼들을 `<form>` 태그로 묶어야 한다. 그 다음 action이라는 인자를 보내고자 하는 서버의 주소를 입력하면 된다.
  
    <form action = "http://localhost:3000/process_create">
        <p>
            <input type = "text" name = "title">
        </p>
        <p>
            <textarea name = "description"></textarea>
        </p>
        <p>
            <input type = "submit">
        </p>
    </form>
  
이렇게 하면 action에 있는 주소로 form 태그 안에 있는 데이터들을 전송하고 싶다는 뜻이 된다. 입력을 받는 태그들에 name을 통해 이름을 부여한 이유는 서버 측에서 이름이 없는 데이터는 활용할 수 없기 때문이다.  
  
실제로 저 코드를 작성한 뒤, 실행 시키면 사이트를 연결할 수 없다. 당연히 해당 주소의 서버가 활성화되어 있지 않기 때문이다.  
  
하지만 URL을 보면 다음과 같이 작성되어 있다.  
`http://localhost:3000/process_create?title=hi&description=node.js`  
일단 주소는 우리가 action에 입력한 값과 동일하며, 우리가 제출한 값들은 쿼리 스트링으로 만들어져 있는 것을 확인할 수 있다.  
  
즉, form 태그는 form 태그가 감싸고 있는 폼들의 데이터들을 submit 버튼을 눌렀을 때 action이 가리키고 있는 주소의 서버로 쿼리 스트링의 형태로 데이터를 전송하는 태그이다.  
  
그러나 이렇게 주소에 데이터를 같이 보내게 되는 경우, 해당 주소를 다른 사람에게 공유했을 때 그 사람이 접근하여 서버의 데이터를 수정할 수 있는 문제가 발생할 수 있다.  
  
그래서 주소는 보통 다른 사람이 접근할 수 있는 페이지에 대한 내용만을 가지고 있어야 하며, 다른 사람이 접근해도 문제가 없는 페이지에 대해서만 주소를 공유하는 것이 좋다.  
  
서버에 데이터를 보낼 때는 다음과 같이 눈에 보이지 않게 보내는 것이 바람직하다.  
  
    <form action = "http://localhost:3000/process_create" method = "POST">
  
다음과 같이 method(방법)를 POST로 하면 된다. 이렇게 하고 제출하면 URL은 다음과 같이 변경된다.  
  
    http://localhost:3000/process_create
  
URL은 action에 적혀 있는 주소만이 나오게 된다. 데이터는 은밀하게 서버로 전송된 것을 확인할 수 있다.  
  
이렇게 전달된 데이터를 가져올 때는 method를 GET으로 변경하거나 생략하면 GET 방식이 된다.