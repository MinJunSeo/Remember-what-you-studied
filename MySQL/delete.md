# DELETE
  
테이블에 저장되어 있는 행(데이터)을 삭제하는 구문이다. 필수적으로 작성해야 하는 구문은 다음과 같다.  
  
	DELETE FROM table_name;
  
삭제하고자 하는 행이 있는 table의 이름을 `table_name`에 넣어주면 된다. 그런데 이렇게 하면 해당 테이블에 있는 모든 행이 삭제되기 때문에 주의해야 한다.  
  
## 특정 행 삭제하기
  
특정 행만을 삭제하기 위해서는 WHERE 구문을 통해 값의 조건을 걸어 해당 값을 가지고 있는 행만 삭제해야 한다. 구문은 다음과 같다.  
  
	DELETE FROM table_name WHERE where_condition;
  
저 `where_condition`에 어떤 열의 어떤 값을 가지고 있는지 적어주면 된다. 예를 들어 author가 duru이라면 author = 'duru' 이런 식으로 말이다.  
  
Ex) topic 테이블에서 id 값이 6인 행을 삭제하기  
![delete row](https://user-images.githubusercontent.com/51042546/81460850-e04cfe00-91e2-11ea-90d8-8a3b61858292.png)  
