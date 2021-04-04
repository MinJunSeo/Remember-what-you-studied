// Visual Studio 2019에서 작성된 코드입니다.

#include "stackInfo.h"
#include <stdlib.h>
#include <stdio.h>

void StackInit(Stack* pstack)
{
	pstack->topIndex = -1;
}

int SIsEmpty(Stack* pstack)
{
	if (pstack->topIndex == -1)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void SPush(Stack* pstack, Data data)
{
	(pstack->topIndex)++;
	pstack->stackArr[pstack->topIndex] = data;
}

Data SPop(Stack* pstack)
{
	int rpos = pstack->topIndex;

	if (SIsEmpty(pstack) == TRUE)
	{
		puts("Stack is Empty !!");
		exit(-1);
	}

	pstack->topIndex--;

	return pstack->stackArr[rpos];
}

Data SPeek(Stack* pstack)
{
	if (SIsEmpty(pstack) == TRUE)
	{
		puts("Stack is Empty");
		exit(-1);
	}

	return pstack->stackArr[pstack->topIndex];
}