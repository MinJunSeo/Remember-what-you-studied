# synchronous & asynchronous
  
## synchronous
  
동기적이라는 것은 주어진 일 하나를 전부 수행할 때까지 다른 일을 수행하지 않는 것을 말한다. 주어진 일이 얼마나 오랜 시간을 필요로 하더라도 동기적으로 일을 수행한다면 주어진 일 하나가 끝날 때까지 계속 그 일을 수행한다.  
  
## asynchronous
  
비동기적이라는 것은 일을 부여하고 끝날 때 관리자에게 말을 하게 하고 다음 일을 수행하는 방식으로 일을 하는 사람과 관리자가 병렬적으로 일을 수행하는 방식을 말한다.  
  
비동기적으로 일을 하면 효율적으로 일을 수행할 수 있지만 그만큼 복잡해진다.  
  
## Node.js
  
Node.js는 비동기적으로 프로그램을 개발하는 것에 특화되어 있다. 그래서 초심자가 Node.js로 코드를 짜다 보면 어렵게 느껴지는 경우가 많다.  
  
Node.js의 file system을 다루는 함수들을 보면 함수명에 `Sync`가 붙지 않은 것과 붙은 것이 존재한다. `Sync`가 붙어 있으면 동기적인 방식으로 동작하는 함수이다. 예로 readFile을 들어보도록 한다.  
  
    fs.readFile(path[, options], callback);
    fs.readFileSync(path[, options]);
  
우선 `readFileSync` 함수부터 알아보자.  
먼저 `sample.txt` 파일에 B라는 문자 하나만을 작성한다.  
그 다음, 다음과 같은 코드를 작성한다.  
  
    var fs = require("fs");

    console.log('A');
    var result = fs.readFileSync("syntax/sample.txt", "utf8");
    console.log(result);
    console.log('C');
  
다음과 같은 코드는 실행 결과로 다음과 같이 출력된다.  
  
    A
    B
    C
  
솔직히 예상한 결과와 다르지 않다. 순차적으로 실행된다면 당연히 저렇게 실행된다고 예상할 수 있기 때문이다.  
  
다음은 `readFile` 함수에 대하여 알아보자.  
  
    var fs = require("fs");

    console.log('A');
    fs.readFile("syntax/sample.txt", "utf8", function(err, result)
    {
        console.log(result);
    });
    console.log('C');
  
비동기적으로 동작하는 `readFile` 함수는 `readFileSync` 함수처럼 반환값을 가지지 않고, 세 번째 인수로 `callback` 이라는 함수를 지정해야 한다.  
  
그렇게 되면 `readFile` 함수가 파일을 읽어들임과 동시에 세 번째 인수로 지정한 함수를 실행시킨다. 그리고 첫 번째 매개변수인 `err`에는 읽는 과정에서 에러가 있었다면 에러를 전달하고, 두 번째 매개변수인 `result`에는 파일의 내용을 전달해준다.  
  
위 코드를 실행시키면 예상과는 조금 다른 실행 결과를 보여준다.  
  
    A
    C
    B
  
실행 결과를 통해 알 수 있는 사실은 A를 출력하고 `readFile`이 실행될텐데 실행되는 도중에 바로 `console.log('C');`가 실행되는 것을 볼 수 있다.  
  
`readFile`은 `readFile` 나름대로 동작해서 끝나는대로 세 번째 인수인 함수를 호출시키면서 안에 있던 명령이 실행되는 것이다.  
  
Node.js는 비동기적인 작업을 선호하기 때문에 Node.js의 작업 효율을 끌어올리기 위해서는 비동기적인 작업 방식으로 만들어야 한다. 하지만 내가 만드는 것이 복잡하지 않거나 큰 효율을 다루고 있는 일이 아니라면 이해하기 쉬운 동기적인 작업 방식으로 만드는 것도 잘못된 방식은 아니다.  
  
## callback
  
비동기적인 작업을 수행하는 함수들은 기본적으로 **callback**이라는 인수를 취하도록 되어 있다.  
  
**callback**은 나중에 수행되는 작업들을 말한다. 기본적으로 해당 함수의 일을 모두 수행한 다음에 실행되는 것이 바로 **callback**이다.  
  
    function a()
    {
        console.log('A');
    }
  
다음과 같은 함수가 있다고 하자. 위 함수는 단순히 'A' 문자만 출력하는 기능을 가지고 있는 함수이다.  
  
그런데 다음과 같은 함수도 동일한 기능을 가지고 않을까?  
  
    function()
    {
        console.log('A');
    }
  
위 함수는 이름을 가지고 있지 않지만 기능적으로는 동일하다. 이렇게 이름이 없어서 호출할 수 없는 함수를 **익명 함수**라고 한다.  
  
하지만 함수는 호출하지 않으면 의미가 없으니 다음과 같이 처리할 수 있다.  
  
    var a = function()
    {
        console.log('A');
    }
  
변수의 값으로 함수를 주는 코드인데, JavaScript에서는 함수도 일종의 값으로 처리할 수 있다는 것을 알 수 있다.  
  
위 변수 a를 `a();`로 실행해도 동일한 실행 결과를 얻을 수 있다.  
  
함수가 끝났으니 다음 일을 하라고 할 수 있는데, 방법은 함수를 만들 때 인수로 `callback`을 전달하고 정의문에서 실행시키면 된다.  
  
    // Example
    function slowfunc(callback) // 작업시간이 오래 걸리는 함수라 하자.
    {
        callback(); // callback 함수를 실행시켰다.
    }
  
실제 호출하는 장면은 다음과 같이 할 수 있다.  
  
    slowfunc(a); // 인수로 함수의 값을 가지고 있는 변수를 전달
  
물론 실행 결과로는 대문자 A가 출력된다. 이것이 callback이다.  
(이해하는 건 어렵기 때문에 조금씩 반복해서 보도록 하자.)