
// HW03. ���� ������ �̿��� ���μ��� �����췯

// �а� : ���ڰ��а�
// �й� : 201402703
// �̸� : �̻�

// ����ȯ�� : VS2017 

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
// �ð��� ��Ÿ���� ����

FILE * FP;// ��������½�


int now_time = 0;
int num = 0;
// �ڷᱸ�� ����

typedef struct Process_Element {
	char *Name;

	int priority;

	int Arrive_t;
	int Processing_t;
	int Rest_t;

	//��Ÿ���̼� �ð�üũ�� ���� �ʿ��� ����
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

		printf("\n\n���ϴ� ��ȣ�� �Է����ּ���.\n\n");
		printf("1.���μ��� �Է�\n2.���μ��� ����\n");

		fflush(stdin);
		scanf("%d", &num);

		switch (num)
		{
		case 1:

			printf("���μ����� ������ �Է����ּ���(Name(10������), Priority, Arrive Time, Processing Time������)\n");
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
				printf("�߰��� �Է��Ͻðڽ��ϱ�? (Yes�� 1, No�� 2, �ڵ� �Է� ��� 3)\n");

				fflush(stdin);
				scanf("%d", &yes_no);

				if (yes_no == 2)
					flag = 1;
				else if (yes_no == 3) // �ڵ��Է¸�� ���� ���μ����� ó���Ǵ� ��Ȳ�� �ùķ��̼��� �� �ִ� ���
				{
					int choise = 0;
					int i = 0;

					printf("��� ���� ���μ��� ���鷡? �ݵ�� 20�� ���ϸ� \n");
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
					printf("�ٽ� �Է����ּ���.(Name(10������), Arrive Time, Processing Time������)\n");
				}
			}

			break;

		case 2:
			while (num == 2)
			{
				running_Process(ready_q, running_q, ended_q);
				now = running_q->front + 1;

				system("cls");
				printf("����ð�: %d sec (0 sec���� ����)\n\n", now_time);
				Task_Manager(running_q);

				printf("[Current Situation]\n");
				printf("����: ����  s�� S ��ư \n");
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
				//��Ÿ���̼� �ذ�å
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
		printf("������ �� �����ϴ�.\n");
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
	// ���� 1. MinHeap h�� Item ���μ����� �߰����ִ� �Լ�
	if (!is_full_Heap(h))
	{
		//item�� ���������̹Ƿ�, �Լ��� ����ɶ� �������. ����, �޸𸮸� �Ҵ��Ѵ�.
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

		//Heap_Type�� New_Element �� �ּҸ� �߰� �����ش�.
		(h->heap[i]) = New_Element;

		// Upheap ��� ����
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

	// �� ��, heap�� key�� �ش�Ǵ� ���� process�� priority�̴�.
	// �̸� ����Ͽ� min heap�� �˸��� ��ġ�� item �׸��� �߰��� ��
}
Process_Element* deleteMinHeap(Process_Heap_Type *h)
{

	// ���� 2. MinHeap�� RootNode�� ����ִ� ���μ����� return���ִ� �Լ�
	if (is_empty_Heap(h))
	{
		printf("Heap is Empty! Nothing to Delete! \n");
		return NULL;
	}

	Process_Element* Temp = h->heap[1];
	Process_Element* Swap = NULL;
	h->heap[1] = h->heap[h->heap_size--];

	//Down Heap ����
	int i = 1;
	int High_Priority = 0;
	while (2 * i <= h->heap_size) // �ڽĳ�尡 ���� ������ �ݺ�
	{
		if (h->heap_size == (2 * i)) // ���� �ڽĳ�常 ���� ��
		{
			if (h->heap[2 * i]->priority <  h->heap[i]->priority) // �ڽ��� �켱������ �� ���� �� ���������� �ٲٰ� Ż��
			{	// ��ġ����
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
		else if (h->heap[2 * i]->priority <= h->heap[(2 * i) + 1]->priority) //���� �ڽĳ�尡 ������ :���� �ڽĳ���� �켱������ ������ �ڽĳ���� �켱���� ���� Ŭ��	
			High_Priority = 2 * i;
		else     //������ �ڽĳ���� �켱������ ���� �ڽĳ���� �켱���� ���� Ŭ��
			High_Priority = (2 * i) + 1;
		// �켱������ ���� ���� ������ �ǽ�
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
	// ���� 3. ���� ������ �����Ͽ� running_q�� ���ҵ��� �켱������ ���� ��迭���ִ� �Լ�

	//Running Queue ���ο� �ִ� ��� Process�� �������ο� ����.
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
	// �� ��, Process Heap Type�� ���� h�� �Ͻ������� �����Ͽ�
	// h�� ���� ������ ������ ������ �����ϰ�, �̸� ���� running_q�� ���������� ��
}
void PrintHeap(Process_Heap_Type*h)
{
	int i = 1;
	while (i <= h->heap_size)
	{
		printf("\n %d��°�� ���� �̸�: %s,%d \n ", i, h->heap[i]->Name, h->heap[i]->priority);
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
			printf("\n\n��� ���μ����� ������ �Ϸ�Ǿ����ϴ�\n");
			printf("���μ��� ���� ���� ���� �ð� : %d sec\n\n\n\n", now_time - 1);
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


				printf("\n\n\n%s ���μ����� ����˴ϴ�.\n", running_q->Element_arr[now]->Name);
				printf("%s ���μ����� ���� �ð� : %d sec\n\n", running_q->Element_arr[now]->Name, now_time);

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
		printf("��");

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
			printf("�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡ��۾������� ���� �����ϼ̽��ϴ١ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�\n\n\n\n\n");
			printf("\n���Ͻô� �޴��� �����ϰų� ��ɾ�â�� �����Ͻʽÿ�\n");
			printf("                1. �ý��� ���� or shutdown �Է�\n");
			printf("                2. ����ȭ������ or main �Է�\n");
			printf("                3. ���μ��� �켱���� ���� chgpr �Է�\n");
			printf("                4. ���� �������� ���μ��� ���� ��� or fout �Է�\n");
			printf("                5. �ƹ��͵� ���� �ʱ�!\n");
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
				printf("\n � ���μ��� �ΰ���? \n");
				scanf("%s", name);
				printf("\n �켱������ �󸶷� �ٲٽðڽ��ϱ�? ");
				scanf("%d", &pri);
				if (!Change_Prioirty(q, name, pri))
				{
					system("cls");
					Sleep(1000);
					printf("�߸��Է��ϼ̽��ϴ�. �ٽýõ� �ϼ���");
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
				printf("���� ���·� �����մϴ� ! \n");
				return;
			}



		}

	}

}

void Check_Starved_Process(Process_Element* Temp_Node) //3�ʿ� �ѹ��÷� �����ؼ� 60�ʰ��� ���󿬻���� �����Ͽ�, ���¸� �Ǵ�
{

	int OPERATION_PER_MIN = 0; //�� ���μ����� �д� �����
	if ((now_time % 2) == 1)
	{
		Temp_Node->Time_2 = Temp_Node->Time_1; //Time_2�� ���ſ� ������ �����ð�
		Temp_Node->Time_1 = Temp_Node->Rest_t; // Time_1�� ���� ������ ���μ����� �����ð�
		OPERATION_PER_MIN = 30 * (Range(Temp_Node->Time_1, Temp_Node->Time_2)); // ���ſ� ������ ���μ����� �����ð���, ���� ������ ���μ����� �����ð��� ���� ���� 1�д� �󸶳� ���������� Ȯ����

		if (OPERATION_PER_MIN <= MINIMUM_OPERATION_PER_MINUTE) //���μ����� �д� �ּ� ����� ���� ������쿡 �ش�Ǹ�
		{
			if (Temp_Node->Weight_Value >= 10)
			{
				Temp_Node->status = 1;	//3�ʴ� ������ ��ȭ���� ��ȭ���� 10���̳� ��ȭ�� ������, Starvation���� �Ǵ�.
			}
			Temp_Node->Weight_Value++;  //3�ʴ� ������ ��ȭ���� ��ȭ�� �ѹ�����������, ����ġ�� �ø�
		}
		else                                                  //�� ���μ����� �д� �ּ� ������� �����ϸ� �ٽ� ���� ���·� ����
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

			printf("%s �� �����ϼ̽��ϴ�. %s \n", str, q->Element_arr[i]->Name);
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
	//��ƻ��� ���μ��� ���
	printf("===============================================================================\n\n\n");
	printf("������ ���μ����� �켱������ �÷��ּ���:");
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