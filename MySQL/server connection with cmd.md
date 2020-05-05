# MySQL server connection with cmd
  
MySQL 데이터베이스를 사용하기 위해서는 MySQL 서버에 접속해 데이터베이스를 관리하는 방법이 있는데, 이 방법을 cmd 창을 통해 할 수 있는 방법에 대해 정리하고자 한다.  
  
우선 기본적으로 cmd 창에 주소가 MySQL server를 다운받은 디렉토리의 bin 폴더여야 한다.  
![bin dir](https://user-images.githubusercontent.com/51042546/81029587-88e81e80-8ec0-11ea-89da-77ee84dabe3e.png)  
  
하지만 매번 이렇게 하는 것은 귀찮을 때가 많다. 왜냐하면 cmd 창이 매번 보안 검사에 의해 자주 꺼지기도 하는데, `cd 주소`를 할 수는 없지 않은가? 그래서 cmd 창에서 그냥 할 수 있도록 시스템 환경 변수에서 path 인자에 해당 주소를 추가한다면 cmd 창에서도 바로 mysql 명령어를 수행할 수 있다.  
![path](https://user-images.githubusercontent.com/51042546/81029725-fa27d180-8ec0-11ea-9a3c-dc31abc2b5cc.JPG)  
  
이렇게 한 뒤, cmd 창을 실행시켜 `mysql -u유저 이름 -p`를 치고 Enter를 누르면 된다. 이때 -u는 user라는 뜻으로 이 뒤에 오는 이름을 사용자 이름으로 정하고 사용하겠다는 의미이다. 여기서 root를 치면 최상위 관리자를 의미한다. -p는 이때 사용하는 user에게 비밀번호를 지정하여 로그인할 때 비밀번호를 입력하게 만든다.  
  
Enter를 치면 아마 Enter password라는 구문과 함께 password를 입력할 수 있을 것이다.  
![mysql connection](https://user-images.githubusercontent.com/51042546/81029820-5a1e7800-8ec1-11ea-8fb4-5f7c9b25ad31.png)  
  
비밀번호를 입력하면 mysql 서버에 접속하여 mysql 서버를 제어할 수 있게 된다.  
![login success](https://user-images.githubusercontent.com/51042546/81029858-7e7a5480-8ec1-11ea-9485-7f74e74e3052.png)  
