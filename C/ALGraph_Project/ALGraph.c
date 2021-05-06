// Visual Studio 2019에서 작성된 코드입니다.

#include <stdio.h>
#include <stdlib.h> // stdlib 함수의 사용을 위해 선언
#include <string.h> // memset 함수의 사용을 위해 선언
#include "ALGraph.h"

int WhoIsPred(Ldata d1, Ldata d2)
{
	if (d1 < d2)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void GraphInit(Graph* pg, int nv)
{
	int i;

	pg->adjList = (List*)malloc(sizeof(List) * nv);
	pg->numV = nv;
	pg->numE = 0;
	pg->infovisit = (Ldata*)malloc(sizeof(Ldata) * nv);

	for (i = 0; i < nv; i++) // 동적할당한 인접 리스트의 초기화
	{
		ListInit(&(pg->adjList[i]));
		SetSortRule(&(pg->adjList[i]), WhoIsPred);
	}

	memset(pg->infovisit, 0, sizeof(int) * nv);
	// infovisit에 들어갈 정보는 어차피 0과 1만 들어가기 때문에 int 타입으로 해도 상관없다.
}

void GraphDestroy(Graph* pg)
{

}