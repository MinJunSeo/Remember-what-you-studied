// Visual Studio 2019에서 작성된 코드입니다.

#include <stdio.h>
#include "ArrayList.h"

int main()
{
	// ArrayList의 생성 및 초기화 //
	List list;
	int data;
	ListInit(&list);

	// 5개의 데이터 저장 //
	LInsert(&list, 5);
	LInsert(&list, 1);
	LInsert(&list, 1);
	LInsert(&list, 0);
	LInsert(&list, 8);

	// 저장된 데이터의 전체 출력 //
	printf("현재 데이터의 수 : %d \n", LCount(&list));

	if (LFirst(&list, &data)) // 첫 번째 데이터 조회
	{
		printf("%d ", data);

		while (LNext(&list, &data)) // 두 번째 이후의 데이터 조회
		{
			printf("%d ", data);
		}
	}
	puts("\n");

	LMInsert(&list, 4, 2); // 데이터 새로 추가

	// 숫자 1을 탐색하여 모두 삭제 //
	if (LFirst(&list, &data))
	{
		if (data == 1)
		{
			LRemove(&list);
		}

		while (LNext(&list, &data))
		{
			if (data == 1)
			{
				LRemove(&list);
			}
		}
	}

	// 삭제 후 남은 데이터의 전체 출력 //
	printf("현재 데이터의 남은 수 : %d \n", LCount(&list));

	if (LFirst(&list, &data))
	{
		printf("%d ", data);

		while (LNext(&list, &data))
		{
			printf("%d ", data);
		}
	}
	puts("\n");

	return 1;
}