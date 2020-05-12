# Internet & Database
  
Database server의 server의 의미를 자세히 알아보도록 하자.  
  
## Internet
  
인터넷을 사용하기 위해서, 동작하기 위해서는 최소 컴퓨터가 두 대가 필요하다. A라는 컴퓨터가 B라는 컴퓨터에게 요청을 한다. 그러면 B라는 컴퓨터는 A라는 컴퓨터의 요청에 대해 응답한다.  
  
A 컴퓨터와 같이 요청을 하는 쪽을 client라고 하고, B 컴퓨터와 같이 응답을 하는 쪽을 server라고 한다. 즉, 인터넷이란 것은 client와 server라는 컴퓨터가 서로 요청하고 응답하면서 돌아가는 시스템이라 할 수 있다.  
  
## Database server
  
MySQL을 설치하면 database client와 database server를 모두 설치한다. 실제로 데이터는 database server에 저장되고 사용자는 database client를 통해 database server에 접속할 수 있다.  
  
database server는 절대 직접 접속할 수 없고, 어떠한 형태로든간에 database client를 통해서만 접속할 수 있다.  
  
MySQL을 사용하면 database client는 바로 `mysql`이라고 할 때 실행되는 명령 기반의 프로그램이다. 실제로 이 프로그램을 실행시키면 다음과 같은 문구가 콘솔에 출력된다.  
  
	Welcome to the MySQL monitor.
  
이 MySQL monitor가 바로 database client의 한 종류였던 것이다. 이외의 MySQL database client 중 하나로 MySQL Workbench를 들 수 있는데, 이 database client는 마치 엑셀처럼 database를 다룰 수 있게 된다.  
