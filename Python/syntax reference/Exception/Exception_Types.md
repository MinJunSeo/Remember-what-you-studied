# Error Types
  
파이썬은 예외도 상속으로 구현되며, 계층 구조로 이루어져 있다. 파이썬에서 예외 처리를 위해서 각 예외가 어떤 예외를 나타내고 있는지 알아보기로 하자.  
  
## SystemExit
  
sys.exit() 함수가 일으키는 에러이다. Exception을 잡는 코드에 의해 잡히지 않는다. 처리되지 않을 경우 파이썬 인터프리터가 종료된다.  
  
## KeyboardInterrupt
  
사용자가 인터럽트 키(일반적으로 Control-c 또는 Delete)를 누를 때 발생한다. Exception을 잡는 코드에 의해 잡히지 않는다. 실행 중 인터럽트 검사가 정기적으로 수행한다.  
  
## Exception
  
모든 시스템 종료 외의 내장 예외 및 사용자 정의 예외는 이 클래스에서 파생된다. 그래서 Exception으로 예외 처리를 하면 모든 내장 예외 및 사용자 정의 예외를 받아 처리할 수 있다.  
  
### StopIteration
  
이터레이터에 의해 생성된 항목이 더 이상 없다는 것을 알려주기 위해 발생합니다. 보통 내장 함수 next()나 이터레이터의 __next__() 매서드가 일으킨다.  
  
### OverflowError
  
산술 연산에서 오버플로우가 발생한 경우 발생하는 에러이다. 다만, 정수의 연산에서는 발생하지 않는다.  
  
### ZeroDivisionError
  
나누기(/, //) 또는 % 연산자로 연산을 수행할 때 두 번째 인자가 0일 때 발생한다.  
  
### AssertionError
  
assert 함수가 실패하였을 때 발생합니다. assert는 지정된 조건식이 거짓일 때 실패합니다.  
  
### AttributeError
  
클래스에서 존재하지 않는 속성에 접근하거나 비공개 속성에 접근하는 등 속성 참조나 대입이 실패할 때 발생합니다.  
  
### BufferError
  
버퍼와 관련된 연산을 수행할 수 없을 때 발생합니다.  
  
### EOFError
  
input() 함수가 데이터를 읽지 못한 상태에서 EOF 조건을 만날 때 발생한다.  
  
### ImportError
  
import 문이 모듈을 로드하는 데 문제가 있을 때 발생한다. 또는 `from ... import`에서 import 하려는 이름을 찾을 수 없을 때도 발생한다.  
  
#### ModuleNotFoundError
  
모듈을 찾을 수 없을 때 import가 일으키는 예외입니다.  
  
### LookupError
  
매핑 또는 시퀀스에 사용된 키나 인덱스가 잘못되었을 때 발생하는 예외입니다.  
  
#### IndexError
  
시퀀스 인덱스가 범위를 벗어날 때 발생합니다.  
  
#### KeyError
  
매핑(딕셔너리) 키가 기존 키 집합에서 발견되지 않을 때 발생합니다.  
  
### NameError
  
지역 또는 전역 이름을 찾을 수 없을 때 발생합니다.  
  
#### UnboundLocalError
  
함수나 매서드에서 지역 변수를 참조하지만, 해당 변수에 값을 불러올 수 없을 때 발생합니다.  
  
이 외에도 여러 가지의 예외가 있습니다. 모든 내장 예외에 대해서는 Python 문서 참조.  
<a href = "https://docs.python.org/ko/3/library/exceptions.html">Python 3.8.2 문서</a>
