# 서버로 전송된 데이터 확인하기
  
우리가 HTML의 `<form>` 태그의 method를 활용하여 서버로 데이터를 주고 받을 수 있다.  
그런데 정말로 잘 전송되었는지 확인하기 위해서는 어떻게 해야 할까?  
  
물론 코드를 작성하여 `method = "GET"` 모드의 `<from>` 태그로 작성된 코드를 작성하면 확인할 수 있겠지만 단순히 데이터가 잘 전송되었는지 확인하는 것만으로 코드를 짜기에는 조금 번거롭다. 그래서 단순히 데이터가 잘 전송되었는지만 확인하려면 다음과 같은 방식으로 확인할 수 있다.  
  
1. 내가 데이터를 보낸 페이지에서 **검사** 버튼을 클릭한다.  
![검사](https://user-images.githubusercontent.com/51042546/79425044-163ffd80-7ffc-11ea-95f7-647f029c0402.JPG)  
  
2. 검사 창 맨 윗줄에서 **Network**를 클릭한다.  
![Network](https://user-images.githubusercontent.com/51042546/79425216-5606e500-7ffc-11ea-8596-6ac6e4cb7188.JPG)  
  
3. 그러면 현재 페이지의 이름과 상태를 확인할 수 있다. 여기서 페이지 이름을 클릭한다.  
![Name](https://user-images.githubusercontent.com/51042546/79425354-89e20a80-7ffc-11ea-8c22-dac91a0d4c92.JPG)  
  
4. 그러면 페이지 이름 옆에 창이 나오는데 메뉴바 중에서 **Headers**를 선택한다.  
![Headers](https://user-images.githubusercontent.com/51042546/79425446-abdb8d00-7ffc-11ea-8cac-2808944db9a6.JPG)  
  
5. 스크롤 바를 내려서 맨 밑으로 가면 **Form Data**라는 항목이 있는데, 그 항목의 내용을 보면 내가 전송한 데이터를 확인할 수 있다.  
![Form Data](https://user-images.githubusercontent.com/51042546/79425559-d6c5e100-7ffc-11ea-84fd-fbe9e2acf4c8.JPG)