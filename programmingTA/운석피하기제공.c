#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define MAP_WIDTH	30	//���� ���α���
#define MAP_HEIGHT	30	//���� ���α���
#define MAX_ROCK	20	//�ִ� ������ ����
#define PLAYER_LIFE	100	//���ּ� �ִ�ü��
#define MIN_SCORE	5	//�����ǿ� ��ϵ� �ּ� ����
#define UNIT_SLEEP	20	//������
#define NAME_LENGHT	20
#define MAX_LIST	20

//���� ���� ��������� 0 , �����̰� ������ 1 , ���ּ��� ������ 2
#define EMPTY	0
#define ROCK	1
#define SHIP	2

// Ű�� ��
#define ESC_KEY	27
#define RIGHT_KEY	77
#define LEFT_KEY	75
#define DOWN_KEY	80
#define UP_KEY	72
#define P_KEY	'p'

HANDLE consoleHandle;	//�⺻���� �ڵ� ����
COORD console_pos = { 0, 0 };	//�⺻ ���� �ڵ� ����


typedef struct {
	int xpos, ypos; //���ּ��� x, y ��ǥ
	int health; //���ּ��� ����
}t_ship;
typedef struct {
	int xpos, ypos;	//���� x, y ��ǥ
	int rock_size; //�� ũ�Ⱑ ũ��, ���ּ��� �浹�Ͽ��� �� �� ���� ���ذ� ����.
}t_rock;
struct Player{
	int rank;
	char name[NAME_LENGHT];
	float time;
};	//GameScore.txt���� �����͸� �ҷ��� ������ ����ü

float startGame(float);
void initGame(void);

void gameSettings(float*);

void viewScore(void);
void addScore(float score);

void updateShipHealth(t_ship*,t_rock*);

void moveShip(t_ship* ship, int direction);
void moveRock(t_rock* rock);

void printMap(int map[][MAP_WIDTH]);
void printSquare(int num);
void updateMap(int map[][MAP_WIDTH], t_ship* ship,t_rock * rock);

int main(void)
{
	int menu_sel = 0;
	float score = 0;
	float game_speed = 9.2f;	//1�ʿ� 9.2�� �ִ� �����δ�.
	initGame();	//�⺻ �ܼ� �����Լ��� �����Ǿ���
	
	while (TRUE)
	{
		Sleep(1000);	//1000ms ���� = 1�ʰ� ����
		system("cls");	//ȭ���� �����.
		printf("� ���ϱ� ����\n");
		printf("�޴��� ���� ���ּ���!\n");
		printf("\t[1] ���� ����\n\t[2] ������ Ȯ��\n\t[3] ���� ����\n\t[4] ���� ����\n\n"); //�޴� ����
		printf("�� :");
		scanf("%d%*c", &menu_sel); //%*c �� ����Ű ����
		switch (menu_sel)
		{
		case 1:
			score=startGame(game_speed);
			if(score > MIN_SCORE) addScore(score);	//�����ǿ� ��ϵǷ���, MIN_SCORE���� ���ƾ��Ѵ�. //addScore �Լ��� GameScore.txt�� �����ϴ� �Լ�
			break;
		case 2: 
			viewScore();	//GameScore.txt�� ���� �о�� �� ����ϴ� �Լ�
			break;
		case 3: 
			gameSettings(&game_speed);	//���Ӽ������� �����ϴ� �Լ�
			break;
		case 4:
			printf("\n������ �����մϴ�\n");
			Sleep(1000);
			return 0;
		}

	}
	return 0;
}
float startGame(float game_speed)
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {0};	//map�迭���� ������ �ϳ��� ��ϵ�. ROCK(1), EMPTY(0) SHIP(2)
	t_ship ship = { MAP_HEIGHT / 2,MAP_WIDTH / 2, PLAYER_LIFE }; // ���ּ��� ó�� ���ӽ��۶� �߾ӿ��� ����, PLAYER_LIFE��ŭ�� ü�����ν���
	t_rock rock[MAX_ROCK];	//����ü �迭 ����
	//�������� ��ġ�� ũ�⸦ �������� �����Ѵ�.


	for (int i = 0; i < MAX_ROCK; i++)
	{
		rock[i].rock_size = rand() % 100;
		rock[i].xpos = rand() % MAP_WIDTH;
		rock[i].ypos = rand() % MAP_HEIGHT;

	}
	

	unsigned char key = 0; //������� Ű �Է��� ������ ����
	time_t start_time, end_time, mid_time; // ������ ������ �ð�, ������ ����� �ð��� ������ ���� , �߰��߰� �ð��� üũ�ϴ� ����
	start_time = clock(); //����ð��� start_time�� ��ϵȴ�.
	mid_time = clock();	
	
	
	
	while (ship.health > 0)	//���ּ��� ü���� 0���� Ŭ�� ������ �������
	{
		updateShipHealth(&ship, rock);	
													
		if ((float)(clock() - mid_time)/CLOCKS_PER_SEC > 1/game_speed)	//		(1/game_speed) �ʸ��� �����̸� �����δ�
		{	 //���� �ӵ� game_speed �� 1��ȸ �����̰� ��ĭ�����̴��� ��ǥ, �� 1ĭ�����̴µ� �ð��� 1/game_speed
			moveRock(rock); //�����̸� ���� �¿�� �����̴� �Լ�
			mid_time = clock();	//�����̸� ������ �ð� üũ
		} 

		updateMap(map, &ship, rock); //map�迭�� ������, ���ּ� ������ ����
		printMap(map);	//�ٲ� ������ ����Ѵ�.
		
		printf("���� �ð�: \n%.2f\n", (float)(mid_time-start_time)/CLOCKS_PER_SEC);	//ȭ�鿡 �ð� ���





		if (_kbhit()) //Ű���尡 ������
		{
			key = _getch();	// Ű����κ��� �ϳ��� ���ڸ� �д´�. 0~255������ ���� ��ȯ�� �ȴ�!
		
			if (key == 224) //����Ű�� ������ 224�� �������Ű�� ���� 2���� ��ȯ��, ������� ������ ����Ű�� ������ 224, 77 �̶�� �� 2���� Ȯ���ؾ���!
			{
				key = _getch();	//�ι�° ����Ű���� Ű����κ��� �д´�. 
				switch (key)
				{
				case LEFT_KEY:  moveShip(&ship, 0);	 break;
				case RIGHT_KEY: moveShip(&ship, 1);	 break;
				case UP_KEY:	moveShip(&ship, 2);  break;
				case DOWN_KEY:	moveShip(&ship, 3);  break;
				}

			}
			else // ����Ű�� ������ ������ , �� �Ϲ�Ű�� ������
				switch (key)
				{
				case P_KEY:		break; //�����ϴ� �˰��� ����



/*�����ᱸ�������������ᱸ�����������������ᱸ��������������
[0.3��]
�����ϴ� �˰���  ���� �Ͻÿ� pŰ�� �������� ȭ���� ���߾�� �Ѵ�. while�� ��������, ���� ����/�߰�/���� ��ΰ���

��������������������������������������������������*/




				case ESC_KEY:	return 0; break;	// ����
				}
		
		}
		Sleep(UNIT_SLEEP);
	}

	end_time = clock(); //������ ���� �ð��� ��ϵȴ�.
	system("cls");
	puts("GAME OVER");
	return (float)(end_time - start_time)/CLOCKS_PER_SEC;		//�ð��� ���̸� ��ȯ�ϰ� �����Ѵ�.
}
void addScore(float score)
{	
	FILE * fp;
	char name[NAME_LENGHT];
	printf("����� ������ %.2f�Դϴ�. GameScore.txt ���Ͽ� �����ϱ� ���ؼ� �̸��� �ʿ��մϴ�.\n",score);
	printf("�̸� �� :");
	scanf("%s",name);

 /*������ᱸ�����������������ᱸ���������������ᱸ������������
 [0.7��]
 struct Player	player[MAX_LIST];
 GameScore.txt�κ��� �����͸� �а� �÷��̾��� ���, �̸� , ������ player�� �ɹ������� �ִ´�.
 
 struct Player{
 int rank;	//����� ������ �ɹ�
 char name[NAME_LENGHT];	//�̸��� ������ �ɹ�
 float time;	//������ ������ �ɹ�
 };

 ��� ������ ��ģ ������� ����(�÷��̽ð�)�� �̸�, ����� ����ü �迭(player)�� �ִ´�. �� ������ ������������ �����ؾ��Ѵ�.
 

 //GameScore.txt�� ����ü �迭�� [���]	[�̸�]	[����] ������� �����Ѵ�.

 ��������������������������������������������������*/


	

}
void viewScore(void)	//�Լ��� ȣ��� ȭ���� ����� ȭ�鿡 GameScore.txt ���Ϸκ��� ������ ������ ȭ�鿡 ����ϴ� �Լ�
{
	FILE * fp;
	fp = fopen("GameScore.txt", "r");
	if (fp == NULL) {
		printf("����� �����Ͱ� �����ϴ�!\n");
		return;
	}
	else 

	{	
		system("cls");

		/*������ᱸ�����������������ᱸ���������������ᱸ������������
		[0.3��]
		GameScore.txt�� ����� ������ �о�� �� �̸� ȭ�鿡 ����Ѵ�.

		���	�̸�	������ ȭ�鿡 ��ϵǾ���Ѵ�. ������ �ڸ����� �������
		1		�����1		12.22
		2		�����2		10.33
		3		�����3		5.55
	

		�������������������������������������������������� */
	}


}	
void moveShip(t_ship* ship, int direction)
{
	switch (direction)
	{

	/*�����ᱸ�������������ᱸ�����������������ᱸ��������������
	[0.2��]
	ship ����ü�� �����̴� �Լ��� ���������� ship ����ü�� �ɹ��� ��ġ�� �ٲٴ� �Լ�
	
	case 0:	if(ship->xpos > 0) ship->xpos--;  break; ��Ʈ�̸�, ������ �Լ��� ���� �Ͻÿ�

	��������������������������������������������������*/

	}


}
void gameSettings(float* game_speed)//���� �ӵ� ���� & �߰����� �߰� ����
{
	
	/*�����ᱸ�������������ᱸ�����������������ᱸ��������������
	[0.2��]
	�⺻������ ���� �ӵ� �����ϴ� �Լ� ����, �߰������� �پ��� ���ٰ�����.


	------�߰�������� ������ �� ����-------
	EX) ���ּ��� ������ �ٲٴ� ���
	EX) ��� ������ �ٲٴ� ��� => ���α׷��� �����Ͽ� ����
	�پ��� �߰������ ������ �����ϴ�.

	��������������������������������������������������*/
}
void updateMap(int map[][MAP_WIDTH], t_ship* ship, t_rock * rock)	//updateMap �Լ��� ���ּ��� ���� ��ġ�� map�迭�� �������ִ� ���
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			map[i][j] = EMPTY;
		}
	}
	//���� EMPTY�������� �ٲپ��ش�.

	/*�����ᱸ�������������ᱸ�����������������ᱸ��������������
	[0.3��]
	1. map�迭�� ���ּ��� �ִ� ���� ���� SHIP���� �ٲپ��ش�.
	2. map�迭�� ��� �ִ� ���� ��ġ�� ROCK���� �ٲپ��ش�.

	��������������������������������������������������*/

}
void printMap(int map[][MAP_WIDTH])		//���� map�迭�� ������ ȭ�鿡 ����ִ� �Լ��� �⺻ �����ڵ�
{
	//system("cls");
	SetConsoleCursorPosition(consoleHandle, console_pos);
	printSquare(MAP_WIDTH+2);
	for (int i = 0; i < MAP_HEIGHT; i++) {
		printf("��");
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			switch (map[i][j])
			{
			case EMPTY: printf("  "); break;
			case ROCK:  printf("��"); break;
			case SHIP: printf("��"); break;
			}
		}
		printf("��");

		switch (i)
		{
		case 2: printf("\t    ���� ���"); break;
		case 3: printf("\t\tUP");
		case 4: printf("\t\t��"); break;
		case 5: printf("\t LEFT�� �� �� RIGHT"); break;
		case 6: printf("\t\t��"); break;
		case 7: printf("\t       DOWN"); break;
		case 15: printf("\t ESC KEY ���� ����!"); break;
		}
		printf("\n");
	}
	printSquare(MAP_WIDTH +2);
//	fflush(stdout);
}
void printSquare(int num)	//�����ڵ�� num����ŭ�� �簢���� ȭ�鿡 �����
{
	for (; num > 0; num --)
	{
		printf("��");
	}
	printf("\n");

}
void updateShipHealth(t_ship* ship,  t_rock* rock) //���ּ��� ���� �浹�ߴ��� �Ǻ��ϰ�, �浹�ߴٸ� ���ּ��� ü�� - ���� ũ�⸦ �Ѵ�.
{
	/*�����ᱸ�������������ᱸ�����������������ᱸ��������������

	1. ��� ��ġ�� ���ּ��� ��ġ�� ������ �浹������ �ǹ��Ѵ�.
	2. �浹�Ұ�� ���ּ��� ü�� - ���  ũ��

	��������������������������������������������������*/



}
void initGame(void)	//�⺻�����ڵ�
{
	CONSOLE_CURSOR_INFO info = { 100,FALSE };
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(consoleHandle, &info);
	SetConsoleTitle("����ϱ� ����");
	system("mode con: cols=120 lines=60");
	srand((unsigned int)time(NULL));
}
void moveRock(t_rock* rock)
{

	/*�����ᱸ�������������ᱸ�����������������ᱸ��������������
	[0.7��]
	���� �����̴� �˰���, �� �� �Լ��� �ѹ� ȣ���� �Ǹ�, ���� �������� �Ѵ�.

	1. ���� ���� ���� �ܺη� ���� �� ����.
	
	���� �����̴� �˰����� �پ��� ������� ������ �����ϴ�.

	*���� ������ ���Ƿ� �����δ�. �ѹ� ȣ���� �ɶ����� ������ ��������  ���� ��ġ���� ��ĭ �����δ�.	
	*���� ������ ���⸸���� �����ϴٰ� ���� �ε����� ������ �ݴ�������� ���� => �� ����ü ���氡��
	
	��� �پ��� ������� ������ �����ϸ�, ���� ������ �߰����� �ο�

	��������������������������������������������������*/


}