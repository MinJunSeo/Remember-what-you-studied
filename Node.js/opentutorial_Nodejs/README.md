# Project title
  
opentutorial_Nodejs : 생활코딩 Node.js 강좌를 보면서 만드는 예제 프로그램입니다.  
  
# Motivation
  
강좌에서 실습을 통해 Node.js를 가르쳐주기 때문에 따라하면서 새로 추가되는 내용들에 대해 정리하는 공간입니다.  
  
# Source Example & Features
  
## version 1.0
  
data 디렉토리에 있는 파일들의 내용을 웹 사이트 상에 보여줍니다.  
  
	var template = require('./lib/template.js');
  
파일을 불러와 보여주는 형식을 하나의 템플릿으로 만들어 해당 모듈을 사용하고 있습니다.  
  
클라이언트가 직접 파일을 생성할 수 있습니다.  
  
클라이언트가 현재 보고 있는 파일을 수정할 수 있습니다. 단, main 페이지는 수정할 수 없습니다.  
  
클라이언트가 현재 보고 있는 파일을 삭제할 수 있습니다. 단, main 페이지는 삭제할 수 없습니다.  
  
자신의 컴퓨터 정보를 꼭 필요한 것만 보여주고, 사용자의 입력에서 html 태그 중 필요 없는 태그는 문자 그대로 써지도록 하였습니다.  
  
## version 1.1
  
![select * from table](https://user-images.githubusercontent.com/51042546/81892159-55ef0a80-95e5-11ea-8ec7-6a05be6ccb7b.png)  
MySQL과 연동하여 데이터베이스 내 테이블 목록을 웹 페이지 상에서 보여줍니다.  
  
## version 1.2
  
![show description](https://user-images.githubusercontent.com/51042546/81895534-62776100-95ed-11ea-8109-0f621fd29ffe.png)  
테이블에 저장되어 있는 제목과 본문을 불러와 웹 페이지 상에서 볼 수 있습니다.  
  
## version 1.3
  
웹 사이트 상에서 데이터 정보(제목, 본문)를 입력하여 데이터베이스에 해당 정보를 추가하고, 추가한 정보를 웹 사이트에서 볼 수 있다.  
단, 아직 글쓴이 id를 받지 못하기 때문에 글쓴이 id값이 고정되어 있다.  
  
# API Reference
  
<a href = "https://opentutorials.org/course/3347/21186" target = "_blank">MySQL로 홈페이지 구현 - 생활코딩</a>  
<a href = "https://opentutorials.org/course/3347/21187" target = "_blank">MySQL로 상세보기 구현 - 생활코딩</a>  
<a href = "https://opentutorials.org/course/3347/21188" target = "_blank">MySQL로 글생성 기능 구현 - 생활코딩</a>  
  
# 수정 이력
  
2020-05-14 : version 1.0 소스 코드를 추가하였습니다.
2020-05-14 : main.js와 lib/template.js를 1.1 버전으로 업데이트하였습니다.  
2020-05-14 : main.js를 1.2 버전으로 업데이트하였습니다.
2020-05-14 : main.js를 1.3 버전으로 업데이트하였습니다.  
