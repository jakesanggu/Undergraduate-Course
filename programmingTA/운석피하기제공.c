#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define MAP_WIDTH	30	//맵의 가로길이
#define MAP_HEIGHT	30	//맵의 세로길이
#define MAX_ROCK	20	//최대 돌맹이 개수
#define PLAYER_LIFE	100	//우주선 최대체력
#define MIN_SCORE	5	//점수판에 기록될 최소 점수
#define UNIT_SLEEP	20	//딜레이
#define NAME_LENGHT	20
#define MAX_LIST	20

//맵의 상태 비어있으면 0 , 돌맹이가 있으면 1 , 우주선이 있으면 2
#define EMPTY	0
#define ROCK	1
#define SHIP	2

// 키의 값
#define ESC_KEY	27
#define RIGHT_KEY	77
#define LEFT_KEY	75
#define DOWN_KEY	80
#define UP_KEY	72
#define P_KEY	'p'

HANDLE consoleHandle;	//기본제공 코드 내용
COORD console_pos = { 0, 0 };	//기본 제공 코드 내용


typedef struct {
	int xpos, ypos; //우주선의 x, y 좌표
	int health; //우주선의 수명
}t_ship;
typedef struct {
	int xpos, ypos;	//돌의 x, y 좌표
	int rock_size; //돌 크기가 크면, 우주선과 충돌하였을 때 더 많은 피해가 간다.
}t_rock;
struct Player{
	int rank;
	char name[NAME_LENGHT];
	float time;
};	//GameScore.txt에서 데이터를 불러와 저장할 구조체

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
	float game_speed = 9.2f;	//1초에 9.2번 최대 움직인다.
	initGame();	//기본 콘솔 세팅함수로 제공되어짐
	
	while (TRUE)
	{
		Sleep(1000);	//1000ms 정지 = 1초간 정지
		system("cls");	//화면을 지운다.
		printf("운석 피하기 게임\n");
		printf("메뉴를 선택 해주세요!\n");
		printf("\t[1] 게임 시작\n\t[2] 점수판 확인\n\t[3] 게임 설정\n\t[4] 게임 종료\n\n"); //메뉴 선택
		printf("☞ :");
		scanf("%d%*c", &menu_sel); //%*c 는 엔터키 제외
		switch (menu_sel)
		{
		case 1:
			score=startGame(game_speed);
			if(score > MIN_SCORE) addScore(score);	//점수판에 기록되려면, MIN_SCORE보다 높아야한다. //addScore 함수는 GameScore.txt에 저장하는 함수
			break;
		case 2: 
			viewScore();	//GameScore.txt로 부터 읽어온 후 출력하는 함수
			break;
		case 3: 
			gameSettings(&game_speed);	//게임설정관련 수정하는 함수
			break;
		case 4:
			printf("\n게임을 종료합니다\n");
			Sleep(1000);
			return 0;
		}

	}
	return 0;
}
float startGame(float game_speed)
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {0};	//map배열에는 다음중 하나가 기록됨. ROCK(1), EMPTY(0) SHIP(2)
	t_ship ship = { MAP_HEIGHT / 2,MAP_WIDTH / 2, PLAYER_LIFE }; // 우주선이 처음 게임시작때 중앙에서 시작, PLAYER_LIFE만큼의 체력으로시작
	t_rock rock[MAX_ROCK];	//구조체 배열 생성
	//돌맹이의 위치와 크기를 랜덤으로 배정한다.


	for (int i = 0; i < MAX_ROCK; i++)
	{
		rock[i].rock_size = rand() % 100;
		rock[i].xpos = rand() % MAP_WIDTH;
		rock[i].ypos = rand() % MAP_HEIGHT;

	}
	

	unsigned char key = 0; //사용자의 키 입력을 저장할 변수
	time_t start_time, end_time, mid_time; // 게임을 시작한 시간, 게임이 종료된 시간을 저장할 변수 , 중간중간 시간을 체크하는 변수
	start_time = clock(); //현재시간이 start_time에 기록된다.
	mid_time = clock();	
	
	
	
	while (ship.health > 0)	//우주선의 체력이 0보다 클때 게임을 계속진행
	{
		updateShipHealth(&ship, rock);	
													
		if ((float)(clock() - mid_time)/CLOCKS_PER_SEC > 1/game_speed)	//		(1/game_speed) 초마다 돌맹이를 움직인다
		{	 //게임 속도 game_speed 는 1초회 돌맹이가 몇칸움직이는지 지표, 즉 1칸움직이는데 시간은 1/game_speed
			moveRock(rock); //돌맹이를 상하 좌우로 움직이는 함수
			mid_time = clock();	//돌맹이를 움직인 시간 체크
		} 

		updateMap(map, &ship, rock); //map배열에 돌맹이, 우주선 정보를 저장
		printMap(map);	//바뀐 정보를 출력한다.
		
		printf("게임 시간: \n%.2f\n", (float)(mid_time-start_time)/CLOCKS_PER_SEC);	//화면에 시간 출력





		if (_kbhit()) //키보드가 눌리면
		{
			key = _getch();	// 키보드로부터 하나의 숫자를 읽는다. 0~255까지의 수가 반환이 된다!
		
			if (key == 224) //방향키가 눌리면 224와 방향고유키의 값이 2개가 반환됨, 예를들어 오른쪽 방향키를 누를시 224, 77 이라는 값 2개를 확인해야함!
			{
				key = _getch();	//두번째 방향키값을 키보드로부터 읽는다. 
				switch (key)
				{
				case LEFT_KEY:  moveShip(&ship, 0);	 break;
				case RIGHT_KEY: moveShip(&ship, 1);	 break;
				case UP_KEY:	moveShip(&ship, 2);  break;
				case DOWN_KEY:	moveShip(&ship, 3);  break;
				}

			}
			else // 방향키가 눌리지 않으면 , 즉 일반키가 눌리면
				switch (key)
				{
				case P_KEY:		break; //중지하는 알고리즘 구현



/*■■■■■구현■■■■■■■■■■■구현■■■■■■■■■■■■■■■구현■■■■■■■■■■■
[0.3점]
중지하는 알고리즘  구현 하시오 p키가 눌렀을때 화면이 멈추어야 한다. while문 수정가능, 변수 생성/추가/변경 모두가능

■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■*/




				case ESC_KEY:	return 0; break;	// 종료
				}
		
		}
		Sleep(UNIT_SLEEP);
	}

	end_time = clock(); //게임이 끝난 시간이 기록된다.
	system("cls");
	puts("GAME OVER");
	return (float)(end_time - start_time)/CLOCKS_PER_SEC;		//시간의 차이를 반환하고 종료한다.
}
void addScore(float score)
{	
	FILE * fp;
	char name[NAME_LENGHT];
	printf("당신의 점수는 %.2f입니다. GameScore.txt 파일에 저장하기 위해서 이름이 필요합니다.\n",score);
	printf("이름 ☞ :");
	scanf("%s",name);

 /*■■■■■■구현■■■■■■■■■■■■■■■구현■■■■■■■■■■■■■구현■■■■■■■■■
 [0.7점]
 struct Player	player[MAX_LIST];
 GameScore.txt로부터 데이터를 읽고 플레이어의 등수, 이름 , 점수를 player의 맴버변수에 넣는다.
 
 struct Player{
 int rank;	//등수를 저장할 맴버
 char name[NAME_LENGHT];	//이름을 저장할 맴버
 float time;	//점수를 저장할 맴버
 };

 방금 게임을 마친 사용자의 점수(플레이시간)와 이름, 등수를 구조체 배열(player)에 넣는다. 단 점수는 내림차순으로 정렬해야한다.
 

 //GameScore.txt에 구조체 배열을 [등수]	[이름]	[점수] 순서대로 저장한다.

 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■*/


	

}
void viewScore(void)	//함수를 호출시 화면을 지우고 화면에 GameScore.txt 파일로부터 점수를 읽은후 화면에 출력하는 함수
{
	FILE * fp;
	fp = fopen("GameScore.txt", "r");
	if (fp == NULL) {
		printf("저장된 데이터가 없습니다!\n");
		return;
	}
	else 

	{	
		system("cls");

		/*■■■■■■구현■■■■■■■■■■■■■■■구현■■■■■■■■■■■■■구현■■■■■■■■■
		[0.3점]
		GameScore.txt에 저장된 점수를 읽어온 후 이를 화면에 출력한다.

		등수	이름	점수가 화면에 기록되어야한다. 점수의 자리수는 상관없음
		1		사용자1		12.22
		2		사용자2		10.33
		3		사용자3		5.55
	

		■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ */
	}


}	
void moveShip(t_ship* ship, int direction)
{
	switch (direction)
	{

	/*■■■■■구현■■■■■■■■■■■구현■■■■■■■■■■■■■■■구현■■■■■■■■■■■
	[0.2점]
	ship 구조체를 움직이는 함수로 실질적으로 ship 구조체의 맴버중 위치를 바꾸는 함수
	
	case 0:	if(ship->xpos > 0) ship->xpos--;  break; 힌트이며, 나머지 함수를 구현 하시오

	■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■*/

	}


}
void gameSettings(float* game_speed)//게임 속도 수정 & 추가적인 추가 설정
{
	
	/*■■■■■구현■■■■■■■■■■■구현■■■■■■■■■■■■■■■구현■■■■■■■■■■■
	[0.2점]
	기본적으로 게임 속도 변경하는 함수 구현, 추가적으로 다양한 접근가능함.


	------추가기능으로 가능한 것 예시-------
	EX) 우주선의 아이콘 바꾸는 기능
	EX) 운석의 개수를 바꾸는 기능 => 프로그램을 수정하여 개선
	다양한 추가기능의 구현이 가능하다.

	■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■*/
}
void updateMap(int map[][MAP_WIDTH], t_ship* ship, t_rock * rock)	//updateMap 함수는 우주선과 돌의 위치를 map배열에 기입해주는 기능
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			map[i][j] = EMPTY;
		}
	}
	//맵을 EMPTY영역으로 바꾸어준다.

	/*■■■■■구현■■■■■■■■■■■구현■■■■■■■■■■■■■■■구현■■■■■■■■■■■
	[0.3점]
	1. map배열에 우주선이 있는 곳의 값을 SHIP으로 바꾸어준다.
	2. map배열에 운석이 있는 곳의 위치를 ROCK으로 바꾸어준다.

	■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■*/

}
void printMap(int map[][MAP_WIDTH])		//현재 map배열의 정보를 화면에 띄워주는 함수로 기본 제공코드
{
	//system("cls");
	SetConsoleCursorPosition(consoleHandle, console_pos);
	printSquare(MAP_WIDTH+2);
	for (int i = 0; i < MAP_HEIGHT; i++) {
		printf("□");
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			switch (map[i][j])
			{
			case EMPTY: printf("  "); break;
			case ROCK:  printf("＊"); break;
			case SHIP: printf("▲"); break;
			}
		}
		printf("□");

		switch (i)
		{
		case 2: printf("\t    조작 방법"); break;
		case 3: printf("\t\tUP");
		case 4: printf("\t\t↑"); break;
		case 5: printf("\t LEFT← ◆ → RIGHT"); break;
		case 6: printf("\t\t↓"); break;
		case 7: printf("\t       DOWN"); break;
		case 15: printf("\t ESC KEY 게임 종료!"); break;
		}
		printf("\n");
	}
	printSquare(MAP_WIDTH +2);
//	fflush(stdout);
}
void printSquare(int num)	//제공코드로 num개만큼의 사각형을 화면에 띄워줌
{
	for (; num > 0; num --)
	{
		printf("□");
	}
	printf("\n");

}
void updateShipHealth(t_ship* ship,  t_rock* rock) //우주선이 돌과 충돌했는지 판별하고, 충돌했다면 우주선의 체력 - 돌의 크기를 한다.
{
	/*■■■■■구현■■■■■■■■■■■구현■■■■■■■■■■■■■■■구현■■■■■■■■■■■

	1. 운석의 위치와 우주선의 위치가 같으면 충돌했음을 의미한다.
	2. 충돌할경우 우주선의 체력 - 운석의  크기

	■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■*/



}
void initGame(void)	//기본제공코드
{
	CONSOLE_CURSOR_INFO info = { 100,FALSE };
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(consoleHandle, &info);
	SetConsoleTitle("운석피하기 게임");
	system("mode con: cols=120 lines=60");
	srand((unsigned int)time(NULL));
}
void moveRock(t_rock* rock)
{

	/*■■■■■구현■■■■■■■■■■■구현■■■■■■■■■■■■■■■구현■■■■■■■■■■■
	[0.7점]
	돌을 움직이는 알고리즘, 즉 이 함수가 한번 호출이 되면, 돌은 움직여야 한다.

	1. 돌은 게임 영역 외부로 나갈 수 없다.
	
	돌을 움직이는 알고리즘은 다양한 방법으로 구현이 가능하다.

	*돌의 방향이 임의로 움직인다. 한번 호출이 될때마다 랜덤한 방향으로  기존 위치에서 한칸 움직인다.	
	*돌이 일정한 방향만으로 진행하다가 벽에 부딪히면 기존과 반대방향으로 진행 => 돌 구조체 변경가능
	
	등등 다양한 방법으로 구현이 가능하며, 고난도 구현시 추가점수 부여

	■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■*/


}