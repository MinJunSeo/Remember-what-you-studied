// Visual Studio 2019에서 작성된 코드입니다.

#ifndef __AL_GRAPH_H__
#define __AL_GRAPH_H__

#include "CLinkedList.h"
// 새로운 edge는 끝에 추가되기 때문에 원형 연결 리스트를 사용하면 작업이 편리해진다.

enum { A, B, C, D, E, F, G, H, I, J }; // 그래프의 해당 인덱스를 문자로 사용하기 위한 열거

typedef int Ldata;

typedef struct _ual
{
	int numV; // 정점의 개수
	int numE; // 간선의 개수
	List* adjList; // 인접 리스트
	int* infovisit; // 방문 기록
} ALGraph;

typedef ALGraph Graph;

void GraphInit(Graph* pg, int nv); // 그래프 초기화
void GraphDestroy(Graph* pg); // 그래프 파괴
void AddEdge(Graph* pg, Ldata fromV, Ldata toV); // 새로운 간선 추가

#endif