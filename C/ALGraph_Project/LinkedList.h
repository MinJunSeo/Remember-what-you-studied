#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

typedef int Ldata;

typedef struct _node {
	Ldata	data;
	struct _node* next;
} Node;


typedef struct _list {
	Node* head;
	Node* cur;
	Node* before;
	int numOfData;
	int (*comp)(Ldata d1, Ldata d2);
}List;

void SetsortRule(List* plist, int (*comp)(Ldata d1, Ldata d2));
void ListInit(List* plist);
void FInsert(List* plist, Ldata data);
void SInsert(List* plist, Ldata data);
void LInsert(List* plist, Ldata data);
int LFirst(List* plist, Ldata* pdata);
int LNext(List* plist, Ldata* pdata);

Ldata LRemove(List* plist);
void LPrint(List* plist);
int LConut(List* plist);

#endif