// Visual Studio 2019에서 작성된 코드입니다.

#ifndef __ARRAY_LIST_H__

#define __ARRAY_LIST_H__

#define LIST_LEN 100
typedef int Ldata; // 구조체에 담을 데이터의 타입에 대한 typedef 정의

typedef struct _ArrayList // 배열기반 리스트를 정의한 구조체
{
	Ldata array[LIST_LEN]; // 저장된 데이터의 수
	int numOfData; // 저장된 데이터의 수
	int curPosition; // 데이터 참조위치를 기록
} ArrayList;

typedef ArrayList List; // ArrayList라는 말이 길어서 따로 다시 한 번 이름을 간략화하였다.

void ListInit(List* plist); // 리스트 초기화 함수

int LFirst(List* plist, Ldata* pdata); // 리스트의 처음인지 판별하는 함수
int LNext(List* plist, Ldata* pdata); // 다음에 데이터가 있는지 확인하는 함수

void LInsert(List* plist, Ldata data); // 데이터를 추가하는 함수
Ldata LRemove(List* plist); // 데이터를 삭제하는 함수

int LCount(List* plist); // 저장된 데이터의 수를 반환하는 함수
void LMInsert(List* plist, Ldata data, int index);

#endif