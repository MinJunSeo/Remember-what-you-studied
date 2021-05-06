// Visual Studio 2019에서 작성된 코드입니다.

#include <stdio.h>
#include "ArrayList.h"

void ListInit(List* plist)
{
	plist->numOfData = 0;
	plist->curPosition = -1;
}

int LFirst(List* plist, Ldata* pdata)
{
	if (plist->numOfData == 0)
	{
		return 0;
	}

	plist->curPosition = 0;
	*pdata = plist->array[0];

	return 1;
}

int LNext(List* plist, Ldata* pdata)
{
	if (plist->curPosition >= plist->numOfData - 1)
	{
		return 0;
	}

	plist->curPosition++;
	*pdata = plist->array[plist->curPosition];

	return 1;
}

void LInsert(List* plist, Ldata data)
{
	if (plist->numOfData >= LIST_LEN)
	{
		puts("List is Full !!");
		return;
	}

	plist->array[plist->numOfData] = data;
	(plist->curPosition)++;
	(plist->numOfData)++;
}

Ldata LRemove(List* plist)
{
	int rpos = plist->curPosition;
	int num = plist->numOfData;
	int i;
	Ldata rdata = plist->array[rpos];

	for (i = rpos; i < num - 1; i++)
	{
		plist->array[i] = plist->array[i + 1];
	}

	(plist->curPosition)--;
	(plist->numOfData)--;

	return rdata;
}

int LCount(List* plist)
{
	return plist->numOfData;
}

void LMInsert(List* plist, Ldata data, int index)
{
	int i;
	int num = plist->numOfData;

	if (plist->numOfData >= LIST_LEN)
	{
		puts("List is Full !!");
		return;
	}
	else if (index > plist->numOfData)
	{
		puts("Discrete List");
		return;
	}

	for (i = num; i > index; i--)
	{
		plist->array[i] = plist->array[i - 1];
	}

	plist->array[index] = data;
	(plist->numOfData)++;
}