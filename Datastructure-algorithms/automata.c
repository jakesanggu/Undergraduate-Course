#define _CRT_SECURE_NO_WARNINGS

// HW04. �׷����� Ȱ���� Finte State Automata ����

// �а� :���ڰ�
// �й� : 201420703
// �̸� : �̻�

// ����ȯ�� : ������

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#define TRUE 1
#define FALSE 0
#define MAX_GRAHPH_V 10
#define INF 1000

typedef struct _edge {

	char transition;
	int cost;
} edge;

edge automata_graph[10][10] = { { { 'a',10 },{ 'c',30 },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'b',20 },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF } },
{ { 'n',INF },{ 'n',INF },{ 'a',10 },{ 'n',INF },{ 'b',20 },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF } },
{ { 'n',INF },{ 'n',INF },{ 'c',30 },{ 'b',20 },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF } },
{ { 'n',INF },{ 'n',INF },{ 'a',10 },{ 'n',INF },{ 'b',20 },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'c',30 },{ 'n',INF } },
{ { 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'a',10 },{ 'b',20 },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF } },
{ { 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'a',10 },{ 'c',30 },{ 'd',40 },{ 'n',INF },{ 'b',20 },{ 'n',INF } },
{ { 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF } },
{ { 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'b',20 },{ 'n',INF },{ 'c',30 },{ 'n',INF } },
{ { 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'd',40 } },
{ { 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'a',10 } } };

edge automata_graph_1[10][10] = { { { 'n',INF },{ 'a',10 },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'b',20 },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF } },
{ { 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'b',20 },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF } },
{ { 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'c',30 },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF } },
{ { 'n',INF },{ 'n',INF },{ 'b',20 },{ 'b',20 },{ 'a',10 },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'c',30 },{ 'n',INF } },
{ { 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'a',10 },{ 'n',INF },{ 'n',INF } },
{ { 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'd',40 },{ 'n',30 },{ 'c',30 },{ 'n',INF },{ 'n',INF },{ 'n',INF } },
{ { 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'a',10 },{ 'n',INF },{ 'n',INF } },
{ { 'n',INF },{ 'n',INF },{ 'n',INF },{ 'a',10 },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'a',10 },{ 'n',INF } },
{ { 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'd',40 } },
{ { 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF },{ 'n',INF } } };

int marked_state[10] = { 0, 0, 0, 0, 1, 0, 1, 0, 0, 1 };
int visited_state[10] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
int cost_state[10] = { INF, INF, INF, INF, INF, INF, INF, INF, INF, INF };
int vertices_set[10] = { INF, INF, INF, INF, INF, INF, INF, INF, INF, INF };

int vertices_last = 0;
typedef struct QueueElement {

	int node;

	struct QueueElement *llink;
	struct QueueElement *rlink;

}QueueElement;
typedef struct QueueType {

	QueueElement *front;
	QueueElement *rear;

	int count;

}QueueType;
int is_empty_Queue(QueueType *q);
void init_Queue(QueueType *q);
QueueElement* create_node(int searching_node);
void enqueue_node(QueueType *q, int searching_node);
void transition(int init_state, char str[]);
int dequeue_node(QueueType *q);
int is_Marked_state(int state);
int is_Reachable_state(int start_state, int end_state);
void depth_first_search(int initial_state);
void breadth_first_search(int initial_state);
int min_DistanceVertices();
int check_Reachability(int final_state);
int check_trace(int index);
void check_Shortest_path();
void print_AutomataTransition();
void print_AutomataCost();

int main(void)
{
	int i;

	printf("\n");

	printf("Finite State Automata�� Reachability �ľ�\n\n");
	for (i = 0; i< 10; i++)
		check_Reachability(i);

	

	check_Shortest_path();


	printf("\n");
	printf("===================================================================");
	printf("\n\n");

	printf("Djkstra Algorithm�� �����ϸ鼭, Ž���� Vertice ����\n");
	for (i = 0; i < 10; i++)
	{
		if (i == 9)
			printf("%d", vertices_set[i]);
		else
			printf("%d->", vertices_set[i]);
	}

	printf("\n\n");

	printf("Djkstra Algorithm�� ������ ����, Initial State�κ��� �� State������ Cost Ȯ��\n");

	for (i = 0; i < 10; i++)
		printf("%d	", i);

	printf("\n");

	for (i = 0; i < 10; i++)
		printf("%d	", cost_state[i]);

	printf("\n\n");

	printf("\n\n");

	//print_AutomataTransition();
	//print_AutomataCost();


	//�߰����
	transition(0, "cbbbc");




	return 0;
}
int is_empty_Queue(QueueType *q)
{
	return (q->count == 0);
}
void init_Queue(QueueType *q)
{
	q->front = NULL;
	q->rear = NULL;

	q->count = 0;
}
QueueElement* create_node(int searching_node)
{
	QueueElement *temp_item = (QueueElement*)malloc(sizeof(QueueElement));

	if (temp_item == NULL)
	{
		printf("�޸� �Ҵ� ����\n");
		exit(1);
	}
	else
	{
		temp_item->node = searching_node;
		temp_item->llink = NULL;
		temp_item->rlink = NULL;

		return temp_item;
	}
}
void enqueue_node(QueueType *q, int searching_node)
{
	QueueElement *new_node = create_node(searching_node);

	if (is_empty_Queue(q))
		q->front = new_node;
	else
	{
		q->rear->rlink = new_node;
		new_node->llink = q->rear;
	}

	q->rear = new_node;

	q->count++;
}
int dequeue_node(QueueType *q)
{
	int dequeued_nodeNumber;

	QueueElement *removed_node;

	if (is_empty_Queue(q))
		printf("���� Queue���� ����\n");
	else
	{
		removed_node = q->front;
		dequeued_nodeNumber = removed_node->node;
		q->front = q->front->rlink;

		free(removed_node);

		if (q->front == NULL)
			q->rear = NULL;
		else
			q->front->llink = NULL;
	}

	q->count--;
	return dequeued_nodeNumber;
}
int is_Marked_state(int state)
{
	if (marked_state[state] == 1)
		return 1;
	else
		return 0;
}
int is_Reachable_state(int start_state, int end_state)
{
	if (automata_graph[start_state][end_state].transition != 'n')
		return 1;
	else
		return 0;
}
void depth_first_search(int initial_state)
{
	// ���� 1
	int i = 0;

//1.  Recursive �� �����Ѵ�. ���� ���� state�� Visted _State�� �߰�
	visited_state[initial_state] = TRUE;
	//2.  For  ������ ���� ������ ���¸� Depth_Firs_Search�� �̿��Ͽ� ����
	for (i = 0; i < MAX_GRAHPH_V; i++)
	{
		if (!visited_state[i] && automata_graph[initial_state][i].transition != 'n')
			depth_first_search(i);
	}
}
void breadth_first_search(int initial_state)
{
	// ���� 2
	//ť�� ����ؾ� �ϹǷ�, ť ����
	QueueType BFS_Queue;
	init_Queue(&BFS_Queue);
	int i, j,w;

	//�湮�ؾ��� ��带 ť�� ����
	enqueue_node(&BFS_Queue, initial_state);
	visited_state[initial_state] = TRUE;
	while (!is_empty_Queue(&BFS_Queue))
	{
		j = dequeue_node(&BFS_Queue);
		for (w = 0; w < MAX_GRAHPH_V; w++)
		{
			if (automata_graph[j][w].transition != 'n' && !visited_state[w])
			{
				visited_state[w] = TRUE;
				enqueue_node(&BFS_Queue, w);
			}
		}

	}

}

int min_DistanceVertices()
{
	// ���� 3
	//�켱 Cost_State �迭�� ���θ� Ž���Ͽ�, �������Ͻ��� ���´�.
	int i = 0;
	int Min_Cost = INF;
	int Min_Location = 0;
	int copy_state[MAX_GRAHPH_V];

	for (i = 0; i < MAX_GRAHPH_V; i++)
	{
		copy_state[i]= cost_state[i];
	}

	//copy_state �迭�� cost_state ������ �����ϰ�

	for (i = 0; i < MAX_GRAHPH_V; i++)
	{	
		if (vertices_set[i] != INF)
			copy_state[vertices_set[i]] = (INF+1);
	}
	//copy_state �迭���� vertices_set�� �ִ� ����� ���� INF�� �ٲ�


	for (i = 0; i < MAX_GRAHPH_V; i++)
	{
		if (copy_state[i] <= Min_Cost)
		{
			Min_Cost = copy_state[i];
			Min_Location = i;
		}
	}

	return Min_Location;
}

int check_trace(int index)
{
	int i;

	for (i = 0; i < 10; i++)
		if (vertices_set[i] == index)
			return 1;

	return 0;

}

int check_Reachability(int final_state)
{
	int i;

	//depth_first_search(0);
	breadth_first_search(0);

	if (is_Marked_state(final_state))
	{
		if (visited_state[final_state] == TRUE)
		{
			printf("%d state�� ���� �����մϴ�\n", final_state);
			return 1;
		}
		else
		{
			printf("%d state�� ���� �Ұ����մϴ�\n", final_state);
			return 0;
		}
	}
	else
	{
		if (visited_state[final_state] == TRUE)
		{
			printf("%d state�� marked state�� �ƴ�����, ���� �����մϴ�\n", final_state);
			return 0;
		}
		else
		{
			printf("%d state�� marked state�� �ƴϰ�, ���� �Ұ����մϴ�\n", final_state);
			return 0;
		}
	}

}

void check_Shortest_path()
{
	// ���� 4 
	// ���� 0���� ���� ���Ͻ� �迭�� ������Ʈ
	int i = 0;
	int j = 0;
	int k = 0;

	while (k != (MAX_GRAHPH_V))
	{
		for (j = 0; j < MAX_GRAHPH_V; j++)
		{
			if (i == 0)
			{
				if (i == j)
					cost_state[j] = 0;
				else
				cost_state[j] = automata_graph[i][j].cost;
			}

			if (cost_state[j] > (automata_graph[i][j].cost + cost_state[i]) && i != 0)
			{
			cost_state[j] = automata_graph[i][j].cost + cost_state[i];
			}
		}
		vertices_set[k++] = i;
		//vertics�迭�� �湮��� �߰�
		i = min_DistanceVertices();
	}

}

void print_AutomataTransition()
{
	int i, j;

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
			printf("%c	", automata_graph[i][j].transition);

		printf("\n");
	}
}

void print_AutomataCost()
{
	int i, j;

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
			printf("%d	", automata_graph[i][j].cost);

		printf("\n");
	}
}

void transition(int init_state, char str[])
{
	//�ʱ� ���¿� ��ȭ ���ڸ� �ָ� ���� ������ �������
	int i = 0;
	char j = 0;
	int k = 0;
	int state = init_state;
	QueueType tmp;
	init_Queue(&tmp);
	for (k = 0; str[k] != 0; k++) 
	{
		enqueue_node(&tmp, str[k]);
	}
	enqueue_node(&tmp, 0); //������ Ȯ�� null���ڷ�

	j = dequeue_node(&tmp);
	printf("\n %d->", state);
	for (i=0;j != 0;i++)
	{
		
		if (automata_graph[state][i].transition == j)
		{
			j = dequeue_node(&tmp);
			printf("%d->", i);
			state = i;
			i = 0;
		}
		else if (i == MAX_GRAHPH_V)
		{
			break;
		}
	}
	if (j != 0)//Ž�� ���н�
	{
		printf("Ž�� ���� ����%d�� ���� ���� %c �� �������� ����\n", state, j);
	}

}