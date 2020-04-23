# 수정할 정보 전송하기
  
파일을 수정하고 서버로 데이터를 보내기 위해서는 2가지가 필요하다.  
첫 번째는 바로 `<form>`이라는 태그이다. 사용자가 수정을 하기 위해서는 입력이 필요하므로 `<form>` 태그가 필요하다.  
두 번째는 파일을 읽어오는 기능이다. 우리는 파일을 새로 만드는 것이 아니라 기존에 있던 파일의 내용을 수정하는 것이니 기존의 내용을 미리 `<form>` 태그 안에 넣어둘 필요가 있다. 그러기 위해서는 파일의 내용을 읽어올 필요가 있다.  
  
## 파일 읽어오기
  
파일을 읽어오는 구문은 이미 이전에도 사용한 적이 있기 때문에 복사 + 붙여넣기 기법을 활용하면 금방 구현할 수 있다.  
우선 전에 사용했던 코드를 그대로 복사 + 붙여넣기 한다.  
  
    fs.readdir("./data", function(err, filelist)
    {
        fs.readFile(`data/${queryData.id}`, "utf8", function(err, description)
        {
            var title = queryData.id;
            var list = templateList(filelist);
            var template = templateHTML(title, list,
                `<h2>${title}</h2>${description}`,
                `<a href = "/create">create</a> <a href = "/update?id=${title}">update</a>`);
            response.writeHead(200);
            response.end(template);
        });
    });
  
이걸로 내가 사용하는 파일을 읽어오는 기능은 바로 구현이 완료되었다.  
  
## form 태그로 수정창 구현하기
  
위 코드에서 title과 description을 보여주는 body 부분을 `<form>` 태그로 변경해주면 된다.  
  
    var template = templateHTML(title, list,
        `
        <form action = "/update_process" method = "POST">
        <p>
            <input type = "text" name = "title" placeholder = "title">
        </p>
        <p>
            <textarea name = "description" placeholder = "description"></textarea>
        </p>
        <p>
            <input type = "submit">
        </p>
        </form>
        `,
        `<a href = "/create">create</a> <a href = "/update?id=${title}">update</a>`);
  
이렇게 하면 저번에 파일을 생성하는 창과 동일한 입력 창이 만들어졌을 것이다.  
  
## 파일에서 읽어온 정보 넣어놓기
  
이제 파일에서 읽어온 데이터를 입력 창에 미리 넣어두어야 한다.  
먼저 `<input>` 태그는 value라는 인수를 이용하여 표현되는 값을 정할 수 있다.  
  
    // 파일에서 읽어온 파일의 이름을 title이라는 변수에 담아두었음
    <input type = "text" name = "title" placeholder = "title" value = "${title}">
  
다음과 같이 value에 미리 파일의 제목을 넣어두면 파일의 제목이 미리 그 창에 들어가있게 된다.  
  
`<textarea>` 태그는 태그 사이에 내가 보여주고자 하는 값을 넣어주면 된다.  
  
    // 파일에서 읽어온 파일의 내용을 description이라는 변수에 담아두었음
    <textarea name = "description" placeholder = "description">${description}</textarea>
  
이렇게 하면 파일에서 읽어온 정보들이 입력 창에 표시되는 것을 볼 수 있다.  
  
## 수정된 정보 전송하기
  
수정된 정보를 서버로 보내야 하는데, 보낼 때 파일의 이름을 저장하고 있는 title 이름을 가지고 있는 input 태그의 값을 보내면 큰일이 날 수 있다. 왜냐하면 파일의 제목은 사용자가 원한다면 변경할 수 있기 때문이다. 만약 사용자가 제목을 변경했는데 그 값을 보내버리면 해당 파일을 찾지 못 할 것이다.  
  
그래서 파일의 이름을 읽어온 뒤로 변경되지 않는 title 변수에 저장되어 있는 값을 서버로 보내야 한다. 그러기 위해서 다음과 같은 코드를 `<form>` 태그 아래 추가한다.  
  
    <input type = "hidden" name = "id" value = "${title}">
  
id라는 이름으로 서버에 보내지게 되는데 값은 파일의 제목을 가지고 있다. 변경 전의 파일 제목이므로 제목을 사용자가 변경해도 아무런 걱정이 없다.  
input type이 hidden이라고 되어 있는데, 이 값이 변경되면 안 되기 때문에 사용자에게 보여질 필요가 없다. 그래서 hidden으로 input type을 주게 되면 사용자에게 보여지지 않게 된다.