# administrator account
  
Ubuntu server를 다운 받고 VM VritualBox를 통해 실행시키면 기본적으로 명령 패널은 다음과 같다.  
  
![command line](https://user-images.githubusercontent.com/51042546/80565416-5c00bb00-8a2b-11ea-80ae-57cd54f2c038.JPG)  
  
기본적으로 $로 표시되어 있는데, 가끔 권리자의 권한이 필요할 때가 있다. 그럴 때는 관리자 계정으로 로그인을 할 필요가 있다. 그럴 때는 패널에 다음과 같이 명령하면 된다.  
  
	sudo su - root
  
su도 관리자 권한으로 변경하는 거지만 su 명령어는 아무나 사용할 수 있는 것이 아니기 때문에 sudo를 사용한다. sudo를 사용하면 자신의 아이디에 대한 비밀번호를 입력하라는 창이 나온다.  
  
![password for your id](https://user-images.githubusercontent.com/51042546/80565670-01b42a00-8a2c-11ea-8f3c-496945397dc5.JPG)  
  
여기서 나의 아이디에 대응하는 비밀번호를 입력하면 관리자 계정으로 로그인 된다.  
  
![root](https://user-images.githubusercontent.com/51042546/80565720-29a38d80-8a2c-11ea-874c-336ff6ef797a.JPG)  
  
최상위 관리자 계정의 이름은 root이며 기본적으로 입력 패널이 #가 된다.  
  
다시 내 상태(일반 유저 로그인 상태)로 돌아가고 싶다면 `exit` 명령어를 입력하고 Enter를 누르면 된다.  
