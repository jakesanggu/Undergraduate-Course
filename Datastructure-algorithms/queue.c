
// HW03. 히프 정렬을 이용한 프로세스 스케쥴러

// 학과 : 전자공학과
// 학번 : 201402703
// 이름 : 이상구

// 개발환경 : VS2017 

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#define Range(a,b) a>=b?((a)-(b)):((b)-(a))

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>

#define MAX_TERMS 100
#define MAX_ELEMENT 100
#define LENGHT_BAR 40
#define MINIMUM_OPERATION_PER_MINUTE 3
// 시간을 나타내는 변수

FILE * FP;// 파일입출력시


int now_time = 0;
int num = 0;
// 자료구조 선언

typedef struct Process_Element {
	char *Name;

	int priority;

	int Arrive_t;
	int Processing_t;
	int Rest_t;

	//스타베이션 시간체크를 위해 필요한 변수
	int Time_1;
	int Time_2;
	int Weight_Value;
	int status;
}Process_Element;
typedef struct Process_Queue_Type {

	Process_Element *Element_arr[MAX_ELEMENT];

	int front;
	int rear;

}Process_Queue_Type;
typedef struct Process_Heap_Type {

	Process_Element *heap[MAX_ELEMENT];

	int heap_size;

} Process_Heap_Type;
int is_empty_Queue(Process_Queue_Type *q);
void init_Queue(Process_Queue_Type *q);
void initHeap(Process_Heap_Type *h);
void insert_Process(Process_Queue_Type *q, char *name, int prior, int arr, int pro, int rest, int Time_1, int Time_2, int Weight_Value, int status);
//void insert_Process(Process_Queue_Type *q, char *name, int prior, int arr, int pro, int rest);
void delete_Process(Process_Queue_Type *q, int index);
int is_empty_Heap(Process_Heap_Type*h);
int is_full_Heap(Process_Heap_Type*h);
void PrintHeap(Process_Heap_Type*h);
void insertMinHeap(Process_Heap_Type *h, Process_Element item);
Process_Element* deleteMinHeap(Process_Heap_Type *h);
void heapSort(Process_Queue_Type *running_q);
void search(Process_Queue_Type *ready_q, Process_Queue_Type *running_q);
void running_Process(Process_Queue_Type *ready_q, Process_Queue_Type *running_q, Process_Queue_Type *ended_q);
void PrintQueue(Process_Queue_Type *q);
void Remaining_Time(Process_Queue_Type*q);
void Task_Manager(Process_Queue_Type* q);
int Change_Prioirty(Process_Queue_Type* q, char* str, int pri);
void FPrintQueue(Process_Queue_Type *q);
void Check_Starved_Process(Process_Element* Temp_Node);
void Print_Starve_Process(Process_Queue_Type*running_q);
int main(void)
{
	char name[10];
	int priority;
	int arrive_time;
	int processing_time;
	int rest_time;

	int now;

	int yes_no;

	int flag;



	Process_Queue_Type *ready_q = (Process_Queue_Type*)malloc(sizeof(Process_Queue_Type));
	Process_Queue_Type *running_q = (Process_Queue_Type*)malloc(sizeof(Process_Queue_Type));
	Process_Queue_Type *ended_q = (Process_Queue_Type*)malloc(sizeof(Process_Queue_Type));

	init_Queue(ready_q);
	init_Queue(running_q);
	init_Queue(ended_q);

	while (num != 6)
	{
		flag = 0;

		system("cls");

		printf("===============================================================================\n");
		printf("Ready Queue Information\n");
		PrintQueue(ready_q);
		printf("===============================================================================\n");
		printf("Running Queue Information\n");
		PrintQueue(running_q);
		printf("===============================================================================\n\n\n");

		printf("\n\n원하는 번호를 입력해주세요.\n\n");
		printf("1.프로세스 입력\n2.프로세스 실행\n");

		fflush(stdin);
		scanf("%d", &num);

		switch (num)
		{
		case 1:

			printf("프로세스의 정보를 입력해주세요(Name(10자이하), Priority, Arrive Time, Processing Time순으로)\n");
			while (flag == 0)
			{
				fflush(stdin);
				scanf("%s", name);

				fflush(stdin);
				scanf("%d", &priority);

				fflush(stdin);
				scanf("%d", &arrive_time);

				fflush(stdin);
				scanf("%d", &processing_time);

				rest_time = processing_time;
				insert_Process(ready_q, name, priority, arrive_time, processing_time, rest_time, 0, 0, 0, 0);

				printf("===============================================================================\n");
				printf("추가로 입력하시겠습니까? (Yes는 1, No는 2, 자동 입력 모드 3)\n");

				fflush(stdin);
				scanf("%d", &yes_no);

				if (yes_no == 2)
					flag = 1;
				else if (yes_no == 3) // 자동입력모드 실제 프로세스가 처리되는 상황을 시뮬레이션할 수 있는 기능
				{
					int choise = 0;
					int i = 0;

					printf("몇개의 랜덤 프로세스 만들래? 반드시 20개 이하만 \n");
					scanf("%d", &choise);
					srand(time(NULL));
					if (choise > 20)
					{
						exit(1);
					}

					for (i; i < choise; i++)
					{

						char *str = (char*)malloc(10 * sizeof(char));
						sprintf(str, "%s%d", "Ran", i);
						int time = (rand() % 5) + 1;
						insert_Process(ready_q, str, (rand() % 5), (rand() % 4) + now_time + 2, time, time, 0, 0, 0, 0);
					}
					break;
				}
				else
				{
					printf("===============================================================================\n");
					printf("다시 입력해주세요.(Name(10자이하), Arrive Time, Processing Time순으로)\n");
				}
			}

			break;

		case 2:
			while (num == 2)
			{
				running_Process(ready_q, running_q, ended_q);
				now = running_q->front + 1;

				system("cls");
				printf("현재시각: %d sec (0 sec부터 시작)\n\n", now_time);
				Task_Manager(running_q);

				printf("[Current Situation]\n");
				printf("도움말: ▶▶  s나 S 버튼 \n");
				printf("===============================================================================\n");
				printf("Ready Queue Information\n");
				PrintQueue(ready_q);
				printf("===============================================================================\n\n\n");
				printf("Running Queue Information\n");
				PrintQueue(running_q);
				Remaining_Time(running_q);
				printf("===============================================================================\n\n\n");
				printf("Ended Queue Information\n");
				PrintQueue(ended_q);
				printf("===============================================================================\n\n\n");
				//스타베이션 해결책
				Print_Starve_Process(running_q);

				Sleep(1000);
				now_time++;

				if (running_q->front != running_q->rear)
				{
					if (running_q->rear > running_q->front || running_q->rear == running_q->front)
						running_q->Element_arr[now]->Rest_t--;
				}

				Sleep(1000);



			}
			break;
		}
	}
	return 0;
}
int is_empty_Queue(Process_Queue_Type *q)
{
	return ((q->rear = 0) || (q->front = 0));
}
void init_Queue(Process_Queue_Type *q)
{
	q->front = -1;
	q->rear = -1;
}
void initHeap(Process_Heap_Type *h)
{
	h->heap_size = 0;
	h->heap[0] = NULL;
}
void insert_Process(Process_Queue_Type *q, char *name, int prior, int arr, int pro, int rest, int Time_1, int Time_2, int Weight_Value, int status)
{
	int i = 0;
	char* tmp_name;

	Process_Element* temp_node;

	tmp_name = (char*)malloc(sizeof(char) * 10);
	temp_node = (Process_Element*)malloc(sizeof(Process_Element));

	strcpy(tmp_name, name);

	temp_node->Name = tmp_name;

	temp_node->priority = prior;
	temp_node->Arrive_t = arr;
	temp_node->Processing_t = pro;
	temp_node->Rest_t = rest;

	temp_node->Time_1 = Time_1;
	temp_node->Time_2 = Time_2;
	temp_node->status = status;
	temp_node->Weight_Value = Weight_Value;



	i = ++(q->rear);

	q->Element_arr[i] = temp_node;
}
void delete_Process(Process_Queue_Type *q, int index)
{
	int i;

	if (index > q->rear)
		printf("삭제할 수 없습니다.\n");
	else
	{
		for (i = index; i < q->rear; i++)
			q->Element_arr[i] = q->Element_arr[i + 1];

		q->rear--;
	}

}
int is_empty_Heap(Process_Heap_Type*h)
{
	return (h->heap_size == 0);
}
int is_full_Heap(Process_Heap_Type*h)
{
	return (h->heap_size == MAX_ELEMENT);
}
void insertMinHeap(Process_Heap_Type *h, Process_Element item)
{
	// 구현 1. MinHeap h에 Item 프로세스를 추가해주는 함수
	if (!is_full_Heap(h))
	{
		//item은 지역변수이므로, 함수가 종료될때 사라진다. 따라서, 메모리를 할당한다.
		Process_Element* New_Element = (Process_Element*)malloc(sizeof(Process_Element));
		int i = (++h->heap_size);

		New_Element->Arrive_t = item.Arrive_t;
		New_Element->Name = item.Name;
		New_Element->priority = item.priority;
		New_Element->Processing_t = item.Processing_t;
		New_Element->Rest_t = item.Rest_t;

		New_Element->Time_1 = item.Time_1;
		New_Element->Time_2 = item.Time_2;
		New_Element->status = item.status;
		New_Element->Weight_Value = item.Weight_Value;

		//Heap_Type에 New_Element 의 주소를 추가 시켜준다.
		(h->heap[i]) = New_Element;

		// Upheap 기능 실행
		while (i >= 2 && ((h->heap[i])->priority < (h->heap[i / 2])->priority))
		{
			Process_Element* Temp = h->heap[i / 2];
			h->heap[i / 2] = h->heap[i];
			h->heap[i] = Temp;
			i = i / 2;
		}
		//PrintHeap(h);


	}
	else
	{
		printf("\n Memory Alloction Failed! \n");
		exit(1);
	}

	// 이 때, heap의 key에 해당되는 것은 process의 priority이다.
	// 이를 고려하여 min heap의 알맞은 위치에 item 항목을 추가할 것
}
Process_Element* deleteMinHeap(Process_Heap_Type *h)
{

	// 구현 2. MinHeap의 RootNode에 들어있는 프로세스를 return해주는 함수
	if (is_empty_Heap(h))
	{
		printf("Heap is Empty! Nothing to Delete! \n");
		return NULL;
	}

	Process_Element* Temp = h->heap[1];
	Process_Element* Swap = NULL;
	h->heap[1] = h->heap[h->heap_size--];

	//Down Heap 실행
	int i = 1;
	int High_Priority = 0;
	while (2 * i <= h->heap_size) // 자식노드가 있을 때까지 반봅
	{
		if (h->heap_size == (2 * i)) // 왼쪽 자식노드만 있을 때
		{
			if (h->heap[2 * i]->priority <  h->heap[i]->priority) // 자식의 우선순위가 더 높을 때 최종적으로 바꾸고 탈출
			{	// 위치변경
				Swap = h->heap[2 * i];
				h->heap[2 * i] = h->heap[i];
				h->heap[i] = Swap;
				break;
			}
			else
			{
				break;
			}
		}
		else if (h->heap[2 * i]->priority <= h->heap[(2 * i) + 1]->priority) //양쪽 자식노드가 있을때 :왼쪽 자식노드의 우선순위가 오른쪽 자식노드의 우선순위 보다 클때	
			High_Priority = 2 * i;
		else     //오른쪽 자식노드의 우선순위가 왼쪽 자식노드의 우선순위 보다 클때
			High_Priority = (2 * i) + 1;
		// 우선순위가 높은 대상과 스와핑 실시
		Swap = h->heap[High_Priority];
		h->heap[High_Priority] = h->heap[i];
		h->heap[i] = Swap;
		i = High_Priority;

	}

	//printf("Deleting %s : %d", Temp->Name, Temp->priority);

	return Temp;


}
void heapSort(Process_Queue_Type *running_q)
{
	// 구현 3. 히프 정렬을 수행하여 running_q의 원소들을 우선순위에 따라 재배열해주는 함수

	//Running Queue 내부에 있는 모든 Process를 히프내부에 복사.
	int i = 0;
	Process_Heap_Type Temp_Heap;
	initHeap(&Temp_Heap);

	for (i = (running_q->front + 1); i < (running_q->rear + 1); i++)
	{
		Process_Element Temp_Element = { running_q->Element_arr[i]->Name,running_q->Element_arr[i]->priority,running_q->Element_arr[i]->Arrive_t,running_q->Element_arr[i]->Processing_t,running_q->Element_arr[i]->Rest_t,running_q->Element_arr[i]->Time_1,running_q->Element_arr[i]->Time_2 ,running_q->Element_arr[i]->Weight_Value ,running_q->Element_arr[i]->status };
		insertMinHeap(&Temp_Heap, Temp_Element);
	}
	running_q->rear = running_q->front;
	for (; 0 != Temp_Heap.heap_size;)
	{
		Process_Element* Temp_Process_Element;
		Temp_Process_Element = deleteMinHeap(&Temp_Heap);
		insert_Process(running_q, Temp_Process_Element->Name, Temp_Process_Element->priority, Temp_Process_Element->Arrive_t, Temp_Process_Element->Processing_t, Temp_Process_Element->Rest_t, Temp_Process_Element->Time_1, Temp_Process_Element->Time_2, Temp_Process_Element->Weight_Value, Temp_Process_Element->status);
	}
	// 이 때, Process Heap Type의 변수 h를 일시적으로 생성하여
	// h에 히프 정렬을 수행한 값들을 정렬하고, 이를 통해 running_q를 재정렬해줄 것
}
void PrintHeap(Process_Heap_Type*h)
{
	int i = 1;
	while (i <= h->heap_size)
	{
		printf("\n %d번째의 히프 이름: %s,%d \n ", i, h->heap[i]->Name, h->heap[i]->priority);
		i++;
	}
}
void search(Process_Queue_Type *ready_q, Process_Queue_Type *running_q)
{
	int index = ready_q->front + 1;

	Process_Element *point;
	point = (Process_Element*)malloc(sizeof(Process_Element));


	while (index < ready_q->rear + 1)
	{
		point = ready_q->Element_arr[index];

		if (point->Arrive_t == now_time)
			insert_Process(running_q, point->Name, point->priority, point->Arrive_t, point->Processing_t, point->Rest_t, point->Time_1, point->Time_2, point->Weight_Value, point->status);

		index++;
	}

	index = ready_q->front + 1;

	while (index < ready_q->rear + 1)
	{
		point = ready_q->Element_arr[index];

		if (point->Arrive_t == now_time)
			delete_Process(ready_q, index);
		else
			index++;
	}
}
void running_Process(Process_Queue_Type *ready_q, Process_Queue_Type *running_q, Process_Queue_Type *ended_q)
{
	int now = (running_q->front) + 1;
	int i = 0;
	for (i = running_q->front + 1; i <= running_q->rear; i++)
	{
		Check_Starved_Process(running_q->Element_arr[i]);
	}

	if (running_q->rear == running_q->front) {
		if (ready_q->rear == ready_q->front) {
			system("cls");
			printf("\n\n모든 프로세스의 실행이 완료되었습니다\n");
			printf("프로세스 실행 최종 종료 시간 : %d sec\n\n\n\n", now_time - 1);
			printf("[Final Result]\n");
			printf("===============================================================================\n");
			printf("Ready Queue Information\n");
			PrintQueue(ready_q);
			printf("===============================================================================\n\n\n");
			printf("Running Queue Information\n");
			PrintQueue(running_q);
			printf("===============================================================================\n\n\n");
			printf("Ended Queue Information\n");
			PrintQueue(ended_q);
			printf("===============================================================================\n\n\n");

			Sleep(1000);
			num = 6;
		}
		else
		{
			search(ready_q, running_q);
			heapSort(running_q);
		}
	}
	else {

		search(ready_q, running_q);
		heapSort(running_q);

		if (running_q->front != running_q->rear)
		{
			if (running_q->Element_arr[now]->Rest_t == 0) {

				//				insert_Process(ended_q, running_q->Element_arr[now]->Name, running_q->Element_arr[now]->priority, running_q->Element_arr[now]->Arrive_t, running_q->Element_arr[now]->Processing_t, running_q->Element_arr[now]->Rest_t);
				insert_Process(ended_q, running_q->Element_arr[now]->Name, running_q->Element_arr[now]->priority, running_q->Element_arr[now]->Arrive_t, running_q->Element_arr[now]->Processing_t, running_q->Element_arr[now]->Rest_t, running_q->Element_arr[now]->Time_1, running_q->Element_arr[now]->Time_2, running_q->Element_arr[now]->Weight_Value, running_q->Element_arr[now]->status);


				printf("\n\n\n%s 프로세스가 종료됩니다.\n", running_q->Element_arr[now]->Name);
				printf("%s 프로세스의 종료 시각 : %d sec\n\n", running_q->Element_arr[now]->Name, now_time);

				running_q->front++;

				Sleep(1000);
			}
		}

	}
}
void PrintQueue(Process_Queue_Type *q)
{
	int i;

	printf("Name      Priority    Arrive Time    Processing Time    Rest Time\n");

	if ((q->front) == (q->rear))
		printf("      (Queue is empty)      \n");
	else
	{
		for (i = (q->front + 1); i < (q->rear + 1); i++)
			printf("%5s        %d		 %d		   %d		   %d\n", q->Element_arr[i]->Name, q->Element_arr[i]->priority, q->Element_arr[i]->Arrive_t, q->Element_arr[i]->Processing_t, q->Element_arr[i]->Rest_t);
	}

}

void Remaining_Time(Process_Queue_Type* q)
{
	int i = 0;
	int Remain_time = 0;
	int Total_time = 0;
	float Percent = 0;
	if (q->rear == -1)
	{
		return;
	}


	for (i = q->front + 1; i <= q->rear; i++)
	{
		Remain_time += q->Element_arr[i]->Rest_t;

	}
	for (i = 0; i <= q->rear; i++)
	{
		Total_time += q->Element_arr[i]->Processing_t;
	}

	printf("Remaining Time is %d Seconds \n", Remain_time);
	Percent = (((float)Total_time - (float)Remain_time) / (float)Total_time);
	printf("\n%g %% \n", Percent * 100);
	printf("0------10------20------30------40------50------60------70------80------90------100\n");
	for (i = 0; i < (Percent*LENGHT_BAR); i++)
	{
		printf("■");

	}
	printf("\n");

}
void Task_Manager(Process_Queue_Type* q)
{
	if (_kbhit())
	{
		if (_getch() == 's' || _getch() == 'S')
		{

			system("cls");
			printf("★★★★★★★★★★★★★★★작업관리자 모드로 입장하셨습니다★★★★★★★★★★★★★★★★★★★\n\n\n\n\n");
			printf("\n원하시는 메뉴를 선택하거나 명령어창에 기입하십시오\n");
			printf("                1. 시스템 종료 or shutdown 입력\n");
			printf("                2. 메인화면으로 or main 입력\n");
			printf("                3. 프로세스 우선순위 변경 chgpr 입력\n");
			printf("                4. 현재 진행중인 프로세스 파일 출력 or fout 입력\n");
			printf("                5. 아무것도 하지 않기!\n");
			char str[MAX_TERMS];
			scanf("%s", str);


			if (!strcmpi(str, "shutdown") || !strcmpi(str, "1"))
			{
				system("cls");
				printf("System is Now Shutting Down!!!");
				Sleep(500);
				num = 6;
				return;
			}
			else if (!strcmpi(str, "main") || !strcmpi(str, "2"))
			{
				Sleep(500);
				num = 1;
				return;
			}
			else if (!strcmpi(str, "chgpr") || !strcmpi(str, "3"))
			{
				char name[MAX_TERMS];
				int pri = 0;
				Sleep(500);
				PrintQueue(q);
				printf("\n 어떤 프로세스 인가요? \n");
				scanf("%s", name);
				printf("\n 우선순위는 얼마로 바꾸시겠습니까? ");
				scanf("%d", &pri);
				if (!Change_Prioirty(q, name, pri))
				{
					system("cls");
					Sleep(1000);
					printf("잘못입력하셨습니다. 다시시도 하세요");
				}
				return;
			}
			else if (!strcmpi(str, "fout") || !strcmpi(str, "4"))
			{
				FP = fopen("Process_Result.txt", "w");
				FPrintQueue(q);
				fclose(FP);

				printf("\nProcessing!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
				Sleep(2000);
				return;
			}
			else
			{
				printf("원래 상태로 복귀합니다 ! \n");
				return;
			}



		}

	}

}

void Check_Starved_Process(Process_Element* Temp_Node) //3초에 한번꼴로 연산해서 60초간의 예상연산수를 측정하여, 상태를 판단
{

	int OPERATION_PER_MIN = 0; //각 프로세스별 분당 연산수
	if ((now_time % 2) == 1)
	{
		Temp_Node->Time_2 = Temp_Node->Time_1; //Time_2은 과거에 측정한 남은시간
		Temp_Node->Time_1 = Temp_Node->Rest_t; // Time_1은 현재 측정한 프로세스의 남은시간
		OPERATION_PER_MIN = 30 * (Range(Temp_Node->Time_1, Temp_Node->Time_2)); // 과거에 측정한 프로세스의 남은시간과, 현재 측정한 프로세스의 남은시간의 차를 비교해 1분당 얼마나 연산했음을 확인함

		if (OPERATION_PER_MIN <= MINIMUM_OPERATION_PER_MINUTE) //프로세스가 분당 최소 연산수 보다 적은경우에 해당되면
		{
			if (Temp_Node->Weight_Value >= 10)
			{
				Temp_Node->status = 1;	//3초당 측정한 변화율의 변화율이 10번이나 변화가 없으면, Starvation으로 판단.
			}
			Temp_Node->Weight_Value++;  //3초당 측정한 변화율의 변화가 한번없을때마다, 가중치를 올림
		}
		else                                                  //그 프로세스가 분당 최소 연산수를 만족하면 다시 원래 상태로 인정
		{
			Temp_Node->status = 0;
			Temp_Node->Weight_Value = 0;
		}

	}

}
int Change_Prioirty(Process_Queue_Type* q, char* str, int pri)
{



	int i = 0;
	for (i = 0; i <= q->rear; i++)
	{
		if (!strcmpi(str, q->Element_arr[i]->Name))
		{
			system("cls");

			printf("%s 를 선택하셨습니다. %s \n", str, q->Element_arr[i]->Name);
			Sleep(1000);
			q->Element_arr[i]->priority = pri;
			return 1;
		}
	}
	return 0;


}
void FPrintQueue(Process_Queue_Type *q)
{
	int i;

	fprintf(FP, "Name      Priority    Arrive Time    Processing Time    Rest Time\n");

	if ((q->front) == (q->rear))
		fprintf(FP, "      (Queue is empty)      \n");
	else
	{
		for (i = (q->front + 1); i < (q->rear + 1); i++)
			fprintf(FP, "%5s        %d		 %d		   %d		   %d\n", q->Element_arr[i]->Name, q->Element_arr[i]->priority, q->Element_arr[i]->Arrive_t, q->Element_arr[i]->Processing_t, q->Element_arr[i]->Rest_t);
	}


}

void Print_Starve_Process(Process_Queue_Type*running_q)
{
	int i;
	//기아상태 프로세스 출력
	printf("===============================================================================\n\n\n");
	printf("다음의 프로세스의 우선순위를 올려주세요:");
	for (i = running_q->front + 1; i <= running_q->rear; i++)
	{
		if (running_q->Element_arr[i]->status)
		{
			printf("%s ,", running_q->Element_arr[i]->Name);
		}
	}
	printf("\n");
	////////////////////////////////////////////////////////////////////////////

}