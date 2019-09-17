/*
201420703 이상구 
VISUAL STUDIO 2017 버전을 사용하여 구현
2018.5.5
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

//MAP Size
#define MAP_HEIGHT 30
#define MAP_WIDTH 30

//MAP Boarder
#define LEFT_EDGE 0
#define RIGHT_EDGE MAP_WIDTH-1
#define UP_EDGE 0
#define BOTTOM_EDGE MAP_HEIGHT-1

//# of ENEMY
#define ENEMY_NO 10

//ENEMY state
#define ENE_L 0
#define ENE_LU 1
#define ENE_U 2
#define ENE_RU 3
#define ENE_R 4
#define ENE_RD 5
#define ENE_D 6
#define ENE_LD 7

//PLAYER state
#define STAY_IN 0
#define GO_OUT 1

//MAP state
#define EMPTY_LAND 0
#define MY_LAND 1
#define REACHED_EDGE 2
#define NOT_MAP 3

//ENEMY life
#define EN_ALIVE 0
#define EN_DEAD 1
#define EN_KING 2

#define MAX_ROUTE_SIZE 2*(MAP_HEIGHT+MAP_WIDTH)

//KEY INPUT
#define LEFT_KEY 75
#define RIGHT_KEY 77
#define UP_KEY 72
#define DOWN_KEY 80
#define SPACE_KEY ' '
#define PAUSE_KEY 'p'
#define ESC_KEY	27
#define C_KEY	'c'


//SPEED
#define UNIT_SPEED 2

//SYSTEM
#define NAME_LENGTH 20
#define LIST_LENGTH 10
#define MAX_LIST 10
#define SCALE_FAC 100

#define Console_X 2
#define Console_Y 2


typedef struct {
	int x;
	int y;
	int sp;
} edge_route;

typedef struct {
	int x;
	int y;
	int state;
} point;

typedef struct {
	int x;
	int y;
	int state;
	int life;
	int way_x;
	int way_y;
} enemy;

struct _name_score {
	char name[NAME_LENGTH];
	int score;
};

struct _targ {
	int (*map)[MAP_WIDTH];
	point *player;
	enemy *en;
	float *play_time;
	int speed;
	int *remain_empty;
};

edge_route route[MAX_ROUTE_SIZE];       //REACHED_EDGE를 기록

void PrintView(int map[][MAP_WIDTH], point* player, enemy en[ENEMY_NO], float play_time, int speed, int remain);
void InitMap(int map[][MAP_WIDTH], point* player, enemy en[ENEMY_NO]);
int EnemyPosition(enemy en[ENEMY_NO], int x, int y);
int EnemyKingPosition(enemy en[ENEMY_NO], int x, int y);
int IsTouchWall(point* player, int direction);
int IsOntheBoarder(int map[][MAP_WIDTH], point* player, int direction);
void MovePlayer(int map[][MAP_WIDTH], point* player, int key_input);
void MoveByKey(int map[][MAP_WIDTH], point* player, int key_input);
void MoveEnemy(int map[][MAP_WIDTH], enemy *en);
void MoveEnemyKing(int map[][MAP_WIDTH], enemy *en);
void EnemyControl(int map[][MAP_WIDTH], enemy en[ENEMY_NO]);
int MakeMap(int map[][MAP_WIDTH], point* player, enemy en[ENEMY_NO], float paly_time, int speed);
void CheckContour(int map[][MAP_WIDTH]);
int CalculateLand(int map[][MAP_WIDTH], point* player);
int CheckEnd(int map[][MAP_WIDTH], point* player, enemy en[ENEMY_NO], int remain);
int ManageNormalFlow(int map[][MAP_WIDTH], point* player, enemy en[ENEMY_NO], time_t startT, int speed);
int ManageCrazyFlow(int map[][MAP_WIDTH], point* player, enemy en[ENEMY_NO], time_t startT, int speed);
int ManageHardFlow(int map[][MAP_WIDTH], point* player, enemy en[ENEMY_NO], time_t startT, int speed);
void RunNormalGame();
void RunHardGame();
void RunCrazyGame();
void ViewScoreBoard();
void AddScore(char* name, int score);
void my_fflush(void);
void my_pause(void);
void init_console(void);
void print_logo(void);
int STOP_SCREEN=0;
HANDLE update_screen;
COORD Position = { Console_X, Console_Y };
HANDLE consoleHandle;
CONSOLE_CURSOR_INFO info;

DWORD WINAPI screen_update(void* data) {

	STOP_SCREEN = 0;
	struct _targ* tdata = (struct _targ*)data;
	system("cls");
		while (STOP_SCREEN == 0)
		{
			SetConsoleCursorInfo(consoleHandle, &info);
			PrintView(tdata->map, tdata->player, tdata->en, *(tdata->play_time), tdata->speed, *(tdata->remain_empty));
			CalculateLand(tdata->map, tdata->player);

		}
	system("cls");
	return 0;
}
int main(void) {
	int menu_sel = 0;
	init_console();
	while (1) {
		print_logo();
		printf("-----------땅따먹기 게임-----------\n\n\n");
		printf("---------------MENU---------------\n\n");
		printf("1. 새 게임\n2. 점수판\n3. 하드모드\n4. 크래이지 모드\n5. 종료\n6. 창 모드\n7. 화면초기화\n\n입력 : "); //메뉴 선택
		scanf("%d", &menu_sel);
		getchar();
		switch (menu_sel) {												//각각의 메뉴에 맞는 함수 실행
		case 1:
			RunNormalGame();
			break;
		case 2:
			ViewScoreBoard();
			break;
		case 3:
			RunHardGame();
			break;
		case 4:
			RunCrazyGame();
			break;
		case 5:
			printf("\n종료합니다...\n");
			return 0;
			break;
		case 6:
			SetConsoleDisplayMode(consoleHandle, CONSOLE_WINDOWED_MODE, 0);
			system("mode con: cols=120 lines=60");
			break;
		case 7:
			init_console();
			break;
		default:
			printf("\n잘못된 입력입니다. 다시 선택해주세요.\n");
			getchar();
			getchar();
			break;
		
		}
		system("cls");
	}
}
void PrintView(int map[][MAP_WIDTH], point* player, enemy en[ENEMY_NO], float play_time, int speed, int remain) {	//화면에 현재 맵의 상황을 출력해주는 함수
	
	//system("cls");			//화면이 계속 깜빡깜빡 거려서 이를 해결하기 위해서 cls 보다는 그냥 커서를 원위치에 두고 덮어씌우는 방식으로 진행하였다.
	printf("\n\n  ");
	SetConsoleCursorPosition(consoleHandle, Position);

	for (int j = 2; j < MAP_WIDTH + 4; j++)
	{
		printf("■");
	}
	printf("\n");
	for (int i = 0; i<MAP_HEIGHT; i++)
	{
		printf("  ■");
		for (int j = 0; j<MAP_WIDTH; j++)
		{
			if (i == player->y && j == player->x) {
				if (player->state == STAY_IN) printf("O ");
				else printf("▨");
			}
			else if (EnemyPosition(en, j, i) >= 0) printf("X ");
			else if (EnemyKingPosition(en, j, i) >= 0) printf("★");
			else if (map[i][j] == MY_LAND) printf("■");
			else if (map[i][j] == REACHED_EDGE) printf("□");
			else printf("  ");
		}
		printf("■");
		switch (i) {
		case 0:  printf(""); break;
		case 1:  printf("\ttime : %.2f", play_time); break;
		case 2:  printf(""); break;
		case 3:  printf(""); break;
		case 4:  printf(""); break;
		case 5:  printf(""); break;
		case 6:  printf(""); break;
		case 7:  printf(""); break;
		case 8:  printf(""); break;
		case 9:  printf("\tKey"); break;
		case 10: printf("\t↑:위로 이동"); break;
		case 11: printf("\t←:좌측이동 →:우측이동"); break;
		case 12: printf("\t↓:아래로 이동"); break;
		case 13: printf("\tspace bar:모드 전환"); break;
		case 14: printf("\tESC_KEY 게임 패배후 종료!"); break;
		case 15: printf(""); break;
		case 16: printf("\tRemain : %d %%", ((remain * 100) / (MAP_HEIGHT*MAP_WIDTH))); break;
		case 17:  printf("\tSpeed : %d", speed); break;
		case 18: printf(""); break;
		case 19: printf(""); break;
		}
		printf("\n");
	}
	printf("  ");
	for (int j = 2; j < MAP_WIDTH + 4; j++)
	{
		printf("■");
	}
	printf("\n");
}
void InitMap(int map[][MAP_WIDTH], point* player, enemy en[ENEMY_NO]) {				//맵 초기화 함수

	player->x = 0;
	player->y = 0;
	player->state = STAY_IN;
	
	for (int i = UP_EDGE; i <= BOTTOM_EDGE; i++) {
		for (int j = LEFT_EDGE; j <= RIGHT_EDGE; j++) {
			if (i == 0 && j == 0) {                     //플레이어는 항상 왼쪽 가장 위에서 생성
				map[i][j] = MY_LAND;
			}
			else if (i == UP_EDGE || i == BOTTOM_EDGE || j == LEFT_EDGE || j == RIGHT_EDGE) {
				map[i][j] = MY_LAND;            //시작시 가장자리 EDGE
			}
			else {
				map[i][j] = EMPTY_LAND;				//나머지는 빈땅
			}
		}
	}

	for (int i = 0; i < ENEMY_NO; i++) {				//적들의 위치 랜덤 생성
		while (1) {
			en[i].x = (rand() % (MAP_WIDTH - 2)) + 1;
			en[i].y = (rand() % (MAP_HEIGHT - 2)) + 1;
			if (map[en[i].y][en[i].x] == EMPTY_LAND) {
				en[i].state = rand() % 8;				//적들의 이동 방향 랜덤 생성
				en[i].life = EN_ALIVE;
				break;
			}
		}
	}

}
int EnemyPosition(enemy en[ENEMY_NO], int x, int y) {	//적들의 위치를 확인하는 함수
	for (int i = 0; i < ENEMY_NO; i++) {
		if (en[i].life == EN_ALIVE && en[i].x == x && en[i].y == y) { //적이 살았나 죽었나 확인
			return i;
		}
	}
	return -1;
}
int EnemyKingPosition(enemy en[ENEMY_NO], int x, int y) {	//적들의 위치를 확인하는 함수
	for (int i = 0; i < ENEMY_NO; i++) {
		if (en[i].life == EN_KING && en[i].x == x && en[i].y == y) { //적이 살았나 죽었나 확인
			return i;
		}
	}
	return -1;
}
int IsTouchWall(point* player, int direction) {		//플레이어가 가려는 방향의 벽에 맞닿아있는지 확인하는 함수
	if (direction == LEFT_KEY)
	{
		if (player->x == LEFT_EDGE)
			return 1;
		return 0;
	}
	else if (direction == RIGHT_KEY)
	{
		if (player->x == RIGHT_EDGE)
			return 1;
		return 0;
	}
	else if (direction == UP_KEY) {
		if (player->y == UP_EDGE)
			return 1;
		return 0;
	}
	else if (direction == DOWN_KEY) {
		if (player->y == BOTTOM_EDGE)
			return 1;
		return 0;
	}
	return 1;
}
int IsOntheBoarder(int map[][MAP_WIDTH], point* player, int direction) {		//플레이어가 이동 가능한 위치에 있는지 확인하는 함수
	if (!IsTouchWall(player, direction)) {
		if (player->state == STAY_IN) {
			switch (direction) {
			case LEFT_KEY:
				if (map[player->y][player->x - 1] == MY_LAND) { return 1; }
				break;
			case RIGHT_KEY:
				if (map[player->y][player->x + 1] == MY_LAND) { return 1; }
				break;
			case UP_KEY:
				if (map[player->y - 1][player->x] == MY_LAND) { return 1; }
				break;
			case DOWN_KEY:
				if (map[player->y + 1][player->x] == MY_LAND) { return 1; }
				break;
			default: break;
			}
		}
		else {
			switch (direction) {
			case LEFT_KEY:
				if (map[player->y][player->x - 1] == MY_LAND || map[player->y][player->x - 1] == EMPTY_LAND) { return 1; }
				break;
			case RIGHT_KEY:
				if (map[player->y][player->x + 1] == MY_LAND || map[player->y][player->x + 1] == EMPTY_LAND) { return 1; }
				break;
			case UP_KEY:
				if (map[player->y - 1][player->x] == MY_LAND || map[player->y - 1][player->x] == EMPTY_LAND) { return 1; }
				break;
			case DOWN_KEY:
				if (map[player->y + 1][player->x] == MY_LAND || map[player->y + 1][player->x] == EMPTY_LAND) { return 1; }
				break;
			default: break;
			}
		}

	}
	return 0;
}
void MovePlayer(int map[][MAP_WIDTH], point* player, int key_input) {			//키에 맞게 플레이어를 움직이는 함수
	//int x_pre = player->x;
	//int y_pre = player->y;
	
	switch (key_input) {				//여기 구현
	case LEFT_KEY:						//방향키에 따라 플레이어 이동
		player->x += -1;
		break;
	case RIGHT_KEY:
		player->x += 1;
		break;
	case UP_KEY:
		player->y += -1;
		break;
	case DOWN_KEY:
		player->y += 1;
		break;
	default: return;
	}

	if (player->state == GO_OUT && map[player->y][player->x] == EMPTY_LAND) {	//빈땅을 먹으러 나가면서 통과한 땅의 좌표 저장
		map[player->y][player->x] = REACHED_EDGE;								//빈땅을 REACHED_EDGE로 변경
		route[0].sp++;
		route[route[0].sp].x = player->x;
		route[route[0].sp].y = player->y;
	}
	return;
}
void MoveByKey(int map[][MAP_WIDTH], point* player, int key_input) {	//키 입력에 따라 이동가능한지 확인하고 이동하는 함수				
	if (key_input == LEFT_KEY || key_input == RIGHT_KEY || key_input == UP_KEY || key_input == DOWN_KEY) {
		if (IsOntheBoarder(map, player, key_input)) {
			//여기 구현
			//이동 가능한지 확인 후에 가능하면 이동
			MovePlayer(map, player, key_input);
		}
	}
	else if (key_input == SPACE_KEY && (map[player->y][player->x] == MY_LAND)) {
		if (player->state == STAY_IN)
			player->state = GO_OUT;
		else player->state = STAY_IN;
	}
}
void MoveEnemy(int map[][MAP_WIDTH], enemy *en) {			//적을 이동시키는 함수
	int x_move = en->x + en->way_x;
	int y_move = en->y + en->way_y;
	int x_hit = 0;
	int y_hit = 0;


	if (map[en->y][x_move] == MY_LAND) x_hit = 1;			//x방향 충돌 감지
	if (map[y_move][en->x] == MY_LAND) y_hit = 1;			//y방향 충돌 감지

	if (x_hit == 0 && y_hit == 0) {                               //충돌 없음 : 이동방향대로 이동
		en->x = x_move;
		en->y = y_move;
	}
	else if (x_hit == 1 && y_hit == 0) {                          //x방향 충돌
		en->x -= en->way_x;                                     //x방향 반전해서 한칸 이동
		en->y = y_move;                                         //y방향 그대로 이동
		if (en->state <= ENE_R) en->state = 4 - en->state;       //바뀐 방향에 맞게 상태 변경
		else en->state = 12 - en->state;
	}
	else if (x_hit == 0 && y_hit == 1) {                          //y방향 충돌
		en->x = x_move;                                         //x방향 그대로 이동
		en->y -= en->way_y;                                     //y방향 반전 이동
		if (en->state != ENE_L) en->state = 8 % en->state;       //상태 변경
	}
	else if (x_hit == 1 && y_hit == 1) {                          //x,y 둘 다 충돌
		en->x -= en->way_x;                                     //둘다 반전 이동
		en->y -= en->way_y;
		if (en->state < ENE_R) en->state += 4;                   //상태 변경
		else en->state -= 4;
	}
}
void MoveEnemyKing(int map[][MAP_WIDTH], enemy *en)
{
	int x_move = en->x + en->way_x;
	int y_move = en->y + en->way_y;
	int x_hit = 0;
	int y_hit = 0;


	if (x_move <= 0 || x_move >= MAP_WIDTH - 1) x_hit = 1;			//x방향 충돌 감지
	if (y_move <= 0 || y_move >= MAP_HEIGHT -1) y_hit = 1;			//y방향 충돌 감지

	if (x_hit == 0 && y_hit == 0) {                               //충돌 없음 : 이동방향대로 이동
		en->x = x_move;
		en->y = y_move;
	if (!(map[en->y][en->x] == REACHED_EDGE)) map[en->y][en->x] = EMPTY_LAND;
	}
	else if (x_hit == 1 && y_hit == 0) {                          //x방향 충돌
		en->x -= en->way_x;                                     //x방향 반전해서 한칸 이동
		en->y = y_move;
		map[en->y][en->x] = EMPTY_LAND;										//y방향 그대로 이동
		if (en->state <= ENE_R) en->state = 4 - en->state;       //바뀐 방향에 맞게 상태 변경
		else en->state = 12 - en->state;
	}
	else if (x_hit == 0 && y_hit == 1) {                          //y방향 충돌
		en->x = x_move;                                         //x방향 그대로 이동
		en->y -= en->way_y;  
		map[en->y][en->x] = EMPTY_LAND;						//y방향 반전 이동
		if (en->state != ENE_L) en->state = 8 % en->state;       //상태 변경
	}
	else if (x_hit == 1 && y_hit == 1) {                          //x,y 둘 다 충돌
		en->x -= en->way_x;                                     //둘다 반전 이동
		en->y -= en->way_y;
		map[en->y][en->x] = EMPTY_LAND;
		if (en->state < ENE_R) en->state += 4;                   //상태 변경
		else en->state -= 4;
	}
	
}
void EnemyControl(int map[][MAP_WIDTH], enemy en[ENEMY_NO]) {
	for (int i = 0; i < ENEMY_NO; i++) {          //enemy의 상태에 따라 이동 방향 정해줌
		if (en[i].life == EN_ALIVE || en[i].life == EN_KING) {
			switch (en[i].state) {
			case ENE_L:                        //좌
				en[i].way_x = -1;
				en[i].way_y = 0;
				break;
			case ENE_LU:                        //좌상
				en[i].way_x = -1;
				en[i].way_y = 1;
				break;
			case ENE_U:                        //상
				en[i].way_x = 0;
				en[i].way_y = 1;
				break;
			case ENE_RU:                        //우상
				en[i].way_x = 1;
				en[i].way_y = 1;
				break;
			case ENE_R:                        //우
				en[i].way_x = 1;
				en[i].way_y = 0;
				break;
			case ENE_RD:                        //우하
				en[i].way_x = 1;
				en[i].way_y = -1;
				break;
			case ENE_D:                        //하
				en[i].way_x = 0;
				en[i].way_y = -1;
				break;
			case ENE_LD:                        //좌하
				en[i].way_x = -1;
				en[i].way_y = -1;
				break;
			default:
				en[i].state = ENE_L;
				break;
			}
			//여기 구현
			//각각의 적을 이동 방향에 맞게 움직임
			if(en[i].life ==EN_ALIVE)
			MoveEnemy(map, &(en[i]));// 적을 움직인다.  
			//여기서 다음과 같이 코드를 작성한 이유는 추가적으로 작성한 Enemy_king 과 일반 enemy를 구분하기 위해서이다.
			//일반적인 적의 이동은 MoveEnemy를 통해서 함수가 한번 호출될때마다 적은 state에 따라 한칸을 움직인다. 
			//Enemy_king의 경우 특징은 한칸을 움직이되, 그 칸이 플레이어의 땅인경우 빈땅으로 땅을 빼앗는 기능을 담당
			else if (en[i].life == EN_KING)
			MoveEnemyKing(map, &en[i]);
		}
	}
}
int MakeMap(int map[][MAP_WIDTH], point* player, enemy en[ENEMY_NO], float paly_time, int speed) { //남은 빈땅 수 확인
	int remain_empty = 0;
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (map[i][j] == EMPTY_LAND) remain_empty++;
		}
	}
	return remain_empty;
}
void CheckContour(int map[][MAP_WIDTH]) {			//저장된 경로를 기준으로 먹은 땅으로 바꾸어줌

		//여기 구현
		while (route[0].sp >= 0) // 스택의 top 이 -1이 될때까지 pop 스택에 있는 정보는 경로이며 가장 마자막에 저장된 경로부터 차례로 my_land로 바꾸어준다.
 		{
			map[route[route[0].sp].y][route[route[0].sp].x] = MY_LAND;
			route[0].sp--;
		}
}
int CalculateLand(int map[][MAP_WIDTH], point* player) {
	if (route[0].sp > -1 && map[player->y][player->x] == MY_LAND) {             //땅 먹기 성공
		CheckContour(map);
		player->state = STAY_IN;
		return 1;
	}
	return 0;
}
int CheckEnd(int map[][MAP_WIDTH], point* player, enemy en[ENEMY_NO], int remain) {
	if ((remain * 100) / (MAP_HEIGHT*MAP_WIDTH) < 40 && player->state == STAY_IN) return 1;            //남은 땅이 30%이하이면 승리
	else {
		for (int i = 0; i < ENEMY_NO; i++) {                          //살아있는 적과 플레이어가 만나거나 살아있는 적이 Reached edge에 닿으면 패배
			if ( (en[i].life == EN_ALIVE || en[i].life == EN_KING )&& (map[en[i].y][en[i].x] == REACHED_EDGE || (en[i].x == player->x && en[i].y == player->y)))
				return 0;
			
		}
	}
	return 2; // 반환값 0 : 패배 1 : 승리 2 : 게임 계속
}
int ManageNormalFlow(int map[][MAP_WIDTH], point* player, enemy en[ENEMY_NO], time_t startT, int speed) {	//전체 게임의 흐름을 제어하는 함수
	
	int remain_empty = 0;
	char key_input='0';
	int cheat = -1;
	time_t endT = 0, stop_T=0;

	//현재 시간을 구하는 함수
	endT = clock();													//현재 시간을 잼
	float play_time = (float)(endT - startT) / (CLOCKS_PER_SEC);	//시작시간부터 현재시간까지를 구함
																	//위 두 구문을 이용하여 플레이 타임을 구할 수 있다
	int end = 2;

	remain_empty = MakeMap(map, player, en, play_time, speed);
	PrintView(map, player, en, play_time, speed, remain_empty);
	int lastkey_sec = 0;
	
	struct _targ arg;
	arg.en = en;
	arg.map = map;
	arg.player = player;
	arg.play_time = &play_time;
	arg.speed = speed;
	arg.remain_empty = &remain_empty;

	update_screen = CreateThread(NULL, 0, screen_update, (void*)&arg, 0, NULL);
	while (TRUE)
	{
		if (cheat != 1)EnemyControl(map, en); // 치트가 발동이 되지 않으면 적이 움직이다.

		for (int i = 0; i < speed + 5; i++) { //스피드 * unit_speed는 적이 움직이고난 이후 멈추는 시간이다. 즉 speed 의 값이 줄어들면 적이 더욱 빨라진다.
			Sleep(UNIT_SPEED);
			end = CheckEnd(map, player, en, remain_empty);  // 게임이 승리했는지, 패배했는지 확인해준다.
			play_time = (float)(clock() - startT) / (CLOCKS_PER_SEC);	 // 현재 시간을 구하는 함수 사용해서 현재 시간을 구함
			remain_empty = MakeMap(map, player, en, play_time, speed); 	  // 현재 남은 땅을 계산해서 화면에 띄어주는 기능을한다.
			if (end == 0)		//checkEnd가 반환하는 값이 0일때 패배, 1일때 승리이다. 이 경우 패배
			{
				STOP_SCREEN = 1; // 전역변수로 화면출력하는 것을 멈추게 하는 변수이다. 쓰래드 내부에서 확인
				WaitForSingleObject(update_screen, INFINITE); //쓰래드가 정상적으로 종료되었는지 체크후 안전하게 리턴
				return 0;
			}
			else if (end == 1)	//checkEnd가 반환하는 값이 0일때 패배, 1일때 승리이다. 이 경우 승리
			{
				STOP_SCREEN = 1;// 전역변수로 화면출력하는 것을 멈추게 하는 변수이다. 쓰래드 내부에서 확인
				WaitForSingleObject(update_screen, INFINITE);//쓰래드가 정상적으로 종료되었는지 체크후 안전하게 리턴
				return 1;
			}
			
			if (_kbhit())		// 키보드가 눌리면, 버퍼로부터 하나의 키를 입력받는다. 이렇게하는 이유는 _getch()가 BLOCKING함수라 아무것도 눌리지않았는데 _getch를 하면 입력을받을때까지 대기한다. 
			{ 
				key_input = _getch();	//버퍼에 하나의 값을 읽고
				if (key_input == -32) {	// key_input이 -32일때 >> 이유 방향키가 입력되면 두개의 값을 버퍼에 저장> 8비트의 값을 _getch()가 전달해주는데 1110 0000 는 128+64+32=224의 값과 방향과 고유값을
										//반환한다. 224는 -32이라는 값이므로 다음과 같이 되어있다.
					key_input = _getch();	//방향키가 입력되면 방향키 고유값을 읽어오고
					MoveByKey(map, player, key_input);		//플레이어를 움직인다.
				}
				else if(key_input==SPACE_KEY)	//만일 스페이스키가 눌려도
				{
					MoveByKey(map, player, key_input);	
				}
				else if (key_input == PAUSE_KEY)	//사용자가 p키를 누르면
				{
						STOP_SCREEN = 1;			//화면을 작동시키는 스래드 종료
						WaitForSingleObject(update_screen, INFINITE);	//스래드 종료기다리며
						stop_T = clock();	//사용자가 정지시간 체크
						my_pause();		//화면에 다른액티비티를 띄우며, _getchar()로 정지
						startT += clock() - stop_T; // clcock()함수를 띄우면 게임시간이 정지된 시간을 포함하므로, 시작시간에 이 시간을 더해 실제플탐을 계산
						update_screen = CreateThread(NULL, 0, screen_update, (void*)&arg, 0, NULL);// 화면을 출력하는 쓰래드 다시 호출
				}
				else if (key_input == ESC_KEY) //사용자가 ESC키를 누르면,
				{
					STOP_SCREEN = 1; //화면 출력종료
					WaitForSingleObject(update_screen, INFINITE);
					return 0; //사용자 패배
				}
				else if (key_input == C_KEY)
				{
					cheat *= -1; //치트는 1일때 발동 -1일때 비발동
				}
				
				
			}
			fflush(stdin);
		} 
	
	}
}
int ManageHardFlow(int map[][MAP_WIDTH], point* player, enemy en[ENEMY_NO], time_t startT, int speed) {	//전체 게임의 흐름을 제어하는 함수
	int cheat = -1;
	int remain_empty = 0;
	char key_input = '0';
	time_t endT = 0, stop_T = 0;

	//현재 시간을 구하는 함수

	endT = clock();													//현재 시간을 잼
	float play_time = (float)(endT - startT) / (CLOCKS_PER_SEC);	//시작시간부터 현재시간까지를 구함
																	//위 두 구문을 이용하여 플레이 타임을 구할 수 있다
	int end = 2;

	remain_empty = MakeMap(map, player, en, play_time, speed);
	PrintView(map, player, en, play_time, speed, remain_empty);
	int lastkey_sec = 0;
	
	
	// 쓰래드 넘겨줄 인자를 구조체 이용 정의


	struct _targ arg;
	arg.en = en;
	arg.map = map;
	arg.player = player;
	arg.play_time = &play_time;
	arg.speed = speed;
	arg.remain_empty = &remain_empty;

	update_screen = CreateThread(NULL, 0, screen_update, (void*)&arg, 0, NULL); //쓰래드 생성
	while (TRUE)
	{
		if (cheat != 1)EnemyControl(map, en);

		for (int i = 0; i < ENEMY_NO; i++)
		{
			en[i].state = rand() % 8;// 적의 이동방향의 전환
		}

		for (int i = 0; i < speed + 5; i++) { //스피드 * unit_speed는 적이 움직이고난 이후 멈추는 시간이다. 즉 speed 의 값이 줄어들면 적이 더욱 빨라진다.
			Sleep(UNIT_SPEED);
			end = CheckEnd(map, player, en, remain_empty);
			play_time = (float)(clock() - startT) / (CLOCKS_PER_SEC);	 // 현재 시간을 구하는 함수 사용해서 현재 시간을 구함
			remain_empty = MakeMap(map, player, en, play_time, speed);
			if (end == 0)
			{
				STOP_SCREEN = 1; //쓰래드 종료
				WaitForSingleObject(update_screen, INFINITE); //쓰래드 종료 대기
				return 0;
			}
			else if (end == 1)
			{
				STOP_SCREEN = 1; //쓰래드 종료
				WaitForSingleObject(update_screen, INFINITE);//쓰래드 종료 대기
				return 1;
			}

			if (_kbhit())
			{
				key_input = _getch();
				if (key_input == -32) {
					key_input = _getch();
					MoveByKey(map, player, key_input);
				}
				else if (key_input == SPACE_KEY)
				{
					MoveByKey(map, player, key_input);
				}
				else if (key_input == PAUSE_KEY) //사용자가 중지 키를 누르면
				{
						STOP_SCREEN = 1; //쓰래드를 종료시킨다.
						WaitForSingleObject(update_screen, INFINITE); //쓰래드 종료대기
						stop_T = clock(); //중지 시각 체크
						my_pause();	//_getchar함수 호출
						startT += clock() - stop_T; //정지가 풀리면 정지한 시간만큼 시작시간에 더해줌
						update_screen = CreateThread(NULL, 0, screen_update, (void*)&arg, 0, NULL); //다시 화면 복귀
	
				}
				else if (key_input == ESC_KEY)
				{
					STOP_SCREEN = 1; //사용자가 종료를 누르면, 쓰래드 종료
					WaitForSingleObject(update_screen, INFINITE);
					return 0; //패배
				}
				else if (key_input == C_KEY)
				{
					cheat *= -1; //치트는 1일때 발동 -1일때 비발동
				}


			}
			fflush(stdin);

		} // UNIT_SPEED * speed 의 시간	

	}
}
int ManageCrazyFlow(int map[][MAP_WIDTH], point* player, enemy en[ENEMY_NO], time_t startT, int speed) {	//전체 게임의 흐름을 제어하는 함수
	int cheat = -1;
	int remain_empty = 0;
	char key_input = '0';
	time_t endT = 0, stop_T = 0;

	//현재 시간을 구하는 함수

	endT = clock();													//현재 시간을 잼
	float play_time = (float)(endT - startT) / (CLOCKS_PER_SEC);	//시작시간부터 현재시간까지를 구함
																	//위 두 구문을 이용하여 플레이 타임을 구할 수 있다
	int end = 2;

	remain_empty = MakeMap(map, player, en, play_time, speed);
	PrintView(map, player, en, play_time, speed, remain_empty);
	int lastkey_sec = 0;

	struct _targ arg;
	arg.en = en;
	arg.map = map;
	arg.player = player;
	arg.play_time = &play_time;
	arg.speed = speed;
	arg.remain_empty = &remain_empty;
	for (int i = 0; i < ENEMY_NO; i++)
	{
		en[i].life = EN_KING;		//적 왕으로 적을 승격!
	}
	update_screen = CreateThread(NULL, 0, screen_update, (void*)&arg, 0, NULL); //쓰래드 호출
	while (TRUE)
	{
		if (cheat != 1)EnemyControl(map, en);
		if (speed >1) speed--;  		// 적의속도가 점차 빨라진다.					
		for (int i = 0; i < ENEMY_NO; i++)
		{
			en[i].state = rand() % 8;// 적의 이동방향의 전환
		}

		for (int i = 0; i < speed + 5; i++) { //스피드 * unit_speed는 적이 움직이고난 이후 멈추는 시간이다. 즉 speed 의 값이 줄어들면 적이 더욱 빨라진다.
			Sleep(UNIT_SPEED);
			end = CheckEnd(map, player, en, remain_empty);
			play_time = (float)(clock() - startT) / (CLOCKS_PER_SEC);	 // 현재 시간을 구하는 함수 사용해서 현재 시간을 구함
			remain_empty = MakeMap(map, player, en, play_time, speed);
			if (end == 0)
			{
				STOP_SCREEN = 1;
				WaitForSingleObject(update_screen, INFINITE); //쓰래드 종료를 기달린다.
				return 0; // 패배
			}
			else if (end == 1)
			{
				STOP_SCREEN = 1; //쓰래드 정지
				WaitForSingleObject(update_screen, INFINITE);
				return 1; //승리
			}

			if (_kbhit())
			{
				key_input = _getch();
				if (key_input == -32) {
					key_input = _getch();
					MoveByKey(map, player, key_input); // 플레이어를 움직인다.
				}
				else if (key_input == SPACE_KEY) //스패이스 키를 누르면
				{
					MoveByKey(map, player, key_input);
				}
				else if (key_input == PAUSE_KEY) //중지 키를 누르면
				{
			
						STOP_SCREEN = 1;
						WaitForSingleObject(update_screen, INFINITE);
						stop_T = clock(); //사용자가 중지를 시작한 시각
						my_pause();
						startT += clock() - stop_T; //사용자가 중지 해제시각과 중지를 한시각의 차를 시작시간에 더해준다.
						update_screen = CreateThread(NULL, 0, screen_update, (void*)&arg, 0, NULL); //다시 화면 업데이트
					
				}
				else if (key_input == ESC_KEY) 
				{
					STOP_SCREEN = 1;
					WaitForSingleObject(update_screen, INFINITE);
					return 0; //패배
				}
				else if (key_input == C_KEY)
				{
					cheat *= -1; //치트는 1일때 발동 -1일때 비발동
				}


			}
			fflush(stdin);

		} // UNIT_SPEED * speed 의 시간	

	}
}
void RunNormalGame() {								//일반게임 실행
	int map[MAP_HEIGHT][MAP_WIDTH] = { 0 };
	enemy en[ENEMY_NO];
	time_t startT = 0;
	time_t end_T = 0;
	int speed = 100;
	int score;
	char name[NAME_LENGTH];
	point player;
	int i = 0;
	route[0].sp = -1;
	srand(time(NULL));
	InitMap(map, &player, en);

	startT = clock();

	if (ManageNormalFlow(map, &player, en, startT, speed) == 1) {
		end_T = clock();
		float time = (float)(end_T - startT) / (CLOCKS_PER_SEC);
		printf("\n				W   I   N\n");
		printf("\t\t\t당신의 점수는 %d 입니다. \n", (int)((MAP_WIDTH)*(MAP_HEIGHT)*(SCALE_FAC) / (time*speed)));
		printf("				Name : ");
		fflush(stdin);		
		scanf("%s", name);
		//점수추가부 구현
		//점수는 초당 영역 차지율로 정했다. 즉 총면적/(총시간*속도)가 점수이다.
		AddScore(name, (int)((MAP_WIDTH)*(MAP_HEIGHT)*(SCALE_FAC)/(time*speed)));

	}
	else {
		printf("				G a m e  O v e r\n");
		Sleep(100);
		getchar();
		getchar();
	}

}
void ViewScoreBoard() {								//점수판을 보여줌
	int n = 0;
	char name[NAME_LENGTH] = { 0 };
	char score[NAME_LENGTH] = { 0 };
	struct _name_score name_score[MAX_LIST];

	FILE *fp = fopen("scoreBoard.txt", "r");

	if (fp == NULL) {
		printf("파일을 열 수 없습니다.\n");
		fflush(stdin);
		getchar();
		return;
	}

	system("cls");
	print_logo();
	printf("\n\n=======SCORE=======\n");
	//여기를 구현
	for (int i = 0; i<10 &&(fscanf(fp, "%s\n%d", name_score[i].name, &name_score[i].score) != EOF); i++)
	{
		printf("%d.\t%-10s\t%-5d\n",i+1, name_score[i].name, name_score[i].score);
	}
	// ScoreBoard.txt 파일을 읽고,
	// 형식에 맞게 순차적으로 출력
	printf("Enter AnyKeys");
	Sleep(100);
	getchar();
	getchar();
	//fflush(stdin);
}
void AddScore(char* name, int score) {				//점수를 더함
	int i=0, j=0, k=0, length = 0;
	char name_list[LIST_LENGTH][NAME_LENGTH] = { 0 };
	int score_list[LIST_LENGTH] = { 0 };

	FILE * fp;

	fp = fopen("scoreBoard.txt", "r"); // 우선 읽기전용으로 데이터를 읽어온다.
	if (fp != NULL) {	//파일이 존재하면!
			for (i=0;i < MAX_LIST;i++)	
			if (fscanf(fp, "%s\n%d", name_list[i], &score_list[i]) == EOF)	break;
		fclose(fp);// 전부 읽어온다음에 배열에 저장한다.
	}
	fp = fopen("scoreBoard.txt", "w"); //쓰기 모드로 작성 기존 자료 삭제
	if (fp == NULL) {
		fflush(stdin);
		return;
	}
	while (score < score_list[j] && j <i && i != 0)
	{
		fprintf(fp, "%s\n%d\n", name_list[j], score_list[j]);
		j++; // score보다 더 높은점수는 다시씀
	}
	if (j < MAX_LIST) {	 //현재 쓴 양이 10번보다 작을 때 이름과 점수 기록
		fprintf(fp, "%s\n%d\n", name, score); 
	}
	while (j < i)	//만일 쓴량(j+1) 읽어온 수 i 보다 작을때까지 나머지를 채워넣음
	{	fprintf(fp, "%s\n%d\n", name_list[j], score_list[j]); j++;}
	fclose(fp);

}
void RunCrazyGame() {
	int map[MAP_HEIGHT][MAP_WIDTH] = { 0 };
	enemy en[ENEMY_NO];
	time_t startT = 0;
	time_t end_T = 0;
	int speed = 100;
	int score;
	char name[NAME_LENGTH];
	point player;
	int i = 0;
	route[0].sp = -1;
	srand(time(NULL));
	InitMap(map, &player, en);

	startT = clock();

	if (ManageCrazyFlow(map, &player, en, startT, speed) == 1) {
		end_T = clock();
		float time = (float)(end_T - startT) / (CLOCKS_PER_SEC);
		printf("\n				W   I   N\n");
		printf("\t\t\t[crazy모드]당신의 점수는 %d 입니다. \n", (int)((MAP_WIDTH)*(MAP_HEIGHT)*(SCALE_FAC*3) / (time*speed)));
		printf("				Name : ");

		fflush(stdin);
		scanf("%s", name);
		strcat(name, "[CRAZY]");
		//점수추가부 구현
		//점수는 초당 영역 차지율로 정했다. 즉 총면적/(총시간*속도)가 점수이다. 하드모드의 경우 추가점수가 있다.
		AddScore(name, (int)((MAP_WIDTH)*(MAP_HEIGHT)*(SCALE_FAC * 3) / (time*speed)));

	}
	else {
		printf("				G a m e  O v e r\n");
		Sleep(100);
		getchar();
		getchar();
	}

}
void RunHardGame() {
	int map[MAP_HEIGHT][MAP_WIDTH] = { 0 };
	enemy en[ENEMY_NO];
	time_t startT = 0;
	time_t end_T = 0;
	int speed = 50;
	int score;
	char name[NAME_LENGTH];
	point player;
	int i = 0;
	route[0].sp = -1;
	srand(time(NULL));
	InitMap(map, &player, en);
	
	startT = clock();

	if (ManageHardFlow(map, &player, en, startT, speed) == 1) {
		end_T = clock();
		float time = (float)(end_T - startT) / (CLOCKS_PER_SEC);
		printf("\n				W   I   N\n");
		printf("\t\t\t[하드모드]당신의 점수는 %d 입니다. \n", (int)((MAP_WIDTH)*(MAP_HEIGHT)*(SCALE_FAC*2) / (time*speed)));
		printf("				Name : ");

		fflush(stdin);
		scanf("%s", name);
		strcat(name, "[HARD]");
		//점수추가부 구현
		//점수는 초당 영역 차지율로 정했다. 즉 총면적/(총시간*속도)가 점수이다. 하드모드의 경우 추가점수가 있다.
		AddScore(name, (int)((MAP_WIDTH)*(MAP_HEIGHT)*(SCALE_FAC*2) / (time*speed)));

	}
	else {
		printf("				G a m e  O v e r\n");
		Sleep(100);
		getchar();
		getchar();
	}

}
void init_console(void)
{
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); //콘솔 핸들을 받는다.
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleTitle("땅따먹기 게임");//cmd타이틀을 땅따먹기 게임으로 설정
	SetConsoleDisplayMode(consoleHandle, CONSOLE_FULLSCREEN_MODE, 0); //전체화면으로 세팅
	SetConsoleCursorInfo(consoleHandle, &info); // 콘솔 커서를 안보이게한다.
}
void my_fflush(void)
{
	while (getchar() == '\n')break;
}
void my_pause(void)
{
	printf("게임을 다시시작하려면 아무키나 눌러요!\n게임을 종료하려면 ESC를 누르세요!!\n\n\n");
	print_logo();
	_getch();
}
void print_logo(void) {

	printf("\t _____   _____   _   _   _____           _____   _____           _   _   _____   _   _   _   _   _____  \n");
	printf("\t|  _  \\ /  _  \\ | \\ | | /  _  \\         |  _  \\ /  _  \\         | | | | /  _  \\ | | | | | | | | |_   _| \n");
	printf("\t| | | | | |_| | |  \\| | | | |_|         | | | | | |_| |         |  v  | | | | | | |/ /  | |/ /    | |   \n");
	printf("\t| | | | |  _  | | \\   | | | __          | | | | |  _  |         | \\_/ | | | | | |   <   |   <     | |   \n");
	printf("\t| |_| | | | | | | |\\  | | |_\\ \\         | |_| | | | | |         | | | | | |_| | | |\\ \\  | |\\ \\   _| |_  \n");
	printf("\t|_____/ |_| |_| |_| |_| \\___|_|         |_____/ |_| |_|         |_| |_| \\_____/ |_| |_| |_| |_| |_____|\n\n\n");
}