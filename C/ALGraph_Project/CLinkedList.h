// Visual Studio 2019에서 작성된 코드입니다.

#ifndef __C_LINKED_LIST_H__
#define __C_LINKED_LIST_H__

typedef int LData;

typedef struct _node
{
	LData data;
	struct _node* next;
} Node;

typedef struct _CLL
{
	Node* tail;
	Node* before;
	Node* cur;
	int (*comp) (LData, LData);
	int numOfData;
} CList;

typedef CList List;

void ListInit(List* plist);
void LInsert(List* plsit, LData data);

void FInsert(List* plist, LData data);
void SInsert(List* plist, LData data);


int LFirst(List* plist, LData* pdata);
int LNext(List* plist, LData* pdata);

LData LRemove(List* plist);
int LCount(List* plist);

void SetSortRule(List* plist, int (*comp)(LData, LData));
void LPrint(List* plist);

#endif