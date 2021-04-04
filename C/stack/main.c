// Visual Studio 2019에서 작성된 코드입니다.

#include <stdio.h>
#include "stackInfo.h"

int main()
{
	// 스택 생성 및 초기화
	Stack stack;
	StackInit(&stack);

	// 데이터 넣기
	SPush(&stack, 100);
	SPush(&stack, 200);
	SPush(&stack, 300);
	SPush(&stack, 400);
	SPush(&stack, 500);

	// 데이터 꺼내기
	while (!SIsEmpty(&stack))
	{
		printf("%d ", SPop(&stack));
	}
	
	return 1;
}