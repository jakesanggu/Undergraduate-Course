/*
201420703 �̻� 
VISUAL STUDIO 2017 ������ ����Ͽ� ����
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

edge_route route[MAX_ROUTE_SIZE];       //REACHED_EDGE�� ���

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
		printf("-----------�����Ա� ����-----------\n\n\n");
		printf("---------------MENU---------------\n\n");
		printf("1. �� ����\n2. ������\n3. �ϵ���\n4. ũ������ ���\n5. ����\n6. â ���\n7. ȭ���ʱ�ȭ\n\n�Է� : "); //�޴� ����
		scanf("%d", &menu_sel);
		getchar();
		switch (menu_sel) {												//������ �޴��� �´� �Լ� ����
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
			printf("\n�����մϴ�...\n");
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
			printf("\n�߸��� �Է��Դϴ�. �ٽ� �������ּ���.\n");
			getchar();
			getchar();
			break;
		
		}
		system("cls");
	}
}
void PrintView(int map[][MAP_WIDTH], point* player, enemy en[ENEMY_NO], float play_time, int speed, int remain) {	//ȭ�鿡 ���� ���� ��Ȳ�� ������ִ� �Լ�
	
	//system("cls");			//ȭ���� ��� �������� �ŷ��� �̸� �ذ��ϱ� ���ؼ� cls ���ٴ� �׳� Ŀ���� ����ġ�� �ΰ� ������ ������� �����Ͽ���.
	printf("\n\n  ");
	SetConsoleCursorPosition(consoleHandle, Position);

	for (int j = 2; j < MAP_WIDTH + 4; j++)
	{
		printf("��");
	}
	printf("\n");
	for (int i = 0; i<MAP_HEIGHT; i++)
	{
		printf("  ��");
		for (int j = 0; j<MAP_WIDTH; j++)
		{
			if (i == player->y && j == player->x) {
				if (player->state == STAY_IN) printf("O ");
				else printf("��");
			}
			else if (EnemyPosition(en, j, i) >= 0) printf("X ");
			else if (EnemyKingPosition(en, j, i) >= 0) printf("��");
			else if (map[i][j] == MY_LAND) printf("��");
			else if (map[i][j] == REACHED_EDGE) printf("��");
			else printf("  ");
		}
		printf("��");
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
		case 10: printf("\t��:���� �̵�"); break;
		case 11: printf("\t��:�����̵� ��:�����̵�"); break;
		case 12: printf("\t��:�Ʒ��� �̵�"); break;
		case 13: printf("\tspace bar:��� ��ȯ"); break;
		case 14: printf("\tESC_KEY ���� �й��� ����!"); break;
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
		printf("��");
	}
	printf("\n");
}
void InitMap(int map[][MAP_WIDTH], point* player, enemy en[ENEMY_NO]) {				//�� �ʱ�ȭ �Լ�

	player->x = 0;
	player->y = 0;
	player->state = STAY_IN;
	
	for (int i = UP_EDGE; i <= BOTTOM_EDGE; i++) {
		for (int j = LEFT_EDGE; j <= RIGHT_EDGE; j++) {
			if (i == 0 && j == 0) {                     //�÷��̾�� �׻� ���� ���� ������ ����
				map[i][j] = MY_LAND;
			}
			else if (i == UP_EDGE || i == BOTTOM_EDGE || j == LEFT_EDGE || j == RIGHT_EDGE) {
				map[i][j] = MY_LAND;            //���۽� �����ڸ� EDGE
			}
			else {
				map[i][j] = EMPTY_LAND;				//�������� ��
			}
		}
	}

	for (int i = 0; i < ENEMY_NO; i++) {				//������ ��ġ ���� ����
		while (1) {
			en[i].x = (rand() % (MAP_WIDTH - 2)) + 1;
			en[i].y = (rand() % (MAP_HEIGHT - 2)) + 1;
			if (map[en[i].y][en[i].x] == EMPTY_LAND) {
				en[i].state = rand() % 8;				//������ �̵� ���� ���� ����
				en[i].life = EN_ALIVE;
				break;
			}
		}
	}

}
int EnemyPosition(enemy en[ENEMY_NO], int x, int y) {	//������ ��ġ�� Ȯ���ϴ� �Լ�
	for (int i = 0; i < ENEMY_NO; i++) {
		if (en[i].life == EN_ALIVE && en[i].x == x && en[i].y == y) { //���� ��ҳ� �׾��� Ȯ��
			return i;
		}
	}
	return -1;
}
int EnemyKingPosition(enemy en[ENEMY_NO], int x, int y) {	//������ ��ġ�� Ȯ���ϴ� �Լ�
	for (int i = 0; i < ENEMY_NO; i++) {
		if (en[i].life == EN_KING && en[i].x == x && en[i].y == y) { //���� ��ҳ� �׾��� Ȯ��
			return i;
		}
	}
	return -1;
}
int IsTouchWall(point* player, int direction) {		//�÷��̾ ������ ������ ���� �´���ִ��� Ȯ���ϴ� �Լ�
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
int IsOntheBoarder(int map[][MAP_WIDTH], point* player, int direction) {		//�÷��̾ �̵� ������ ��ġ�� �ִ��� Ȯ���ϴ� �Լ�
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
void MovePlayer(int map[][MAP_WIDTH], point* player, int key_input) {			//Ű�� �°� �÷��̾ �����̴� �Լ�
	//int x_pre = player->x;
	//int y_pre = player->y;
	
	switch (key_input) {				//���� ����
	case LEFT_KEY:						//����Ű�� ���� �÷��̾� �̵�
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

	if (player->state == GO_OUT && map[player->y][player->x] == EMPTY_LAND) {	//���� ������ �����鼭 ����� ���� ��ǥ ����
		map[player->y][player->x] = REACHED_EDGE;								//���� REACHED_EDGE�� ����
		route[0].sp++;
		route[route[0].sp].x = player->x;
		route[route[0].sp].y = player->y;
	}
	return;
}
void MoveByKey(int map[][MAP_WIDTH], point* player, int key_input) {	//Ű �Է¿� ���� �̵��������� Ȯ���ϰ� �̵��ϴ� �Լ�				
	if (key_input == LEFT_KEY || key_input == RIGHT_KEY || key_input == UP_KEY || key_input == DOWN_KEY) {
		if (IsOntheBoarder(map, player, key_input)) {
			//���� ����
			//�̵� �������� Ȯ�� �Ŀ� �����ϸ� �̵�
			MovePlayer(map, player, key_input);
		}
	}
	else if (key_input == SPACE_KEY && (map[player->y][player->x] == MY_LAND)) {
		if (player->state == STAY_IN)
			player->state = GO_OUT;
		else player->state = STAY_IN;
	}
}
void MoveEnemy(int map[][MAP_WIDTH], enemy *en) {			//���� �̵���Ű�� �Լ�
	int x_move = en->x + en->way_x;
	int y_move = en->y + en->way_y;
	int x_hit = 0;
	int y_hit = 0;


	if (map[en->y][x_move] == MY_LAND) x_hit = 1;			//x���� �浹 ����
	if (map[y_move][en->x] == MY_LAND) y_hit = 1;			//y���� �浹 ����

	if (x_hit == 0 && y_hit == 0) {                               //�浹 ���� : �̵������� �̵�
		en->x = x_move;
		en->y = y_move;
	}
	else if (x_hit == 1 && y_hit == 0) {                          //x���� �浹
		en->x -= en->way_x;                                     //x���� �����ؼ� ��ĭ �̵�
		en->y = y_move;                                         //y���� �״�� �̵�
		if (en->state <= ENE_R) en->state = 4 - en->state;       //�ٲ� ���⿡ �°� ���� ����
		else en->state = 12 - en->state;
	}
	else if (x_hit == 0 && y_hit == 1) {                          //y���� �浹
		en->x = x_move;                                         //x���� �״�� �̵�
		en->y -= en->way_y;                                     //y���� ���� �̵�
		if (en->state != ENE_L) en->state = 8 % en->state;       //���� ����
	}
	else if (x_hit == 1 && y_hit == 1) {                          //x,y �� �� �浹
		en->x -= en->way_x;                                     //�Ѵ� ���� �̵�
		en->y -= en->way_y;
		if (en->state < ENE_R) en->state += 4;                   //���� ����
		else en->state -= 4;
	}
}
void MoveEnemyKing(int map[][MAP_WIDTH], enemy *en)
{
	int x_move = en->x + en->way_x;
	int y_move = en->y + en->way_y;
	int x_hit = 0;
	int y_hit = 0;


	if (x_move <= 0 || x_move >= MAP_WIDTH - 1) x_hit = 1;			//x���� �浹 ����
	if (y_move <= 0 || y_move >= MAP_HEIGHT -1) y_hit = 1;			//y���� �浹 ����

	if (x_hit == 0 && y_hit == 0) {                               //�浹 ���� : �̵������� �̵�
		en->x = x_move;
		en->y = y_move;
	if (!(map[en->y][en->x] == REACHED_EDGE)) map[en->y][en->x] = EMPTY_LAND;
	}
	else if (x_hit == 1 && y_hit == 0) {                          //x���� �浹
		en->x -= en->way_x;                                     //x���� �����ؼ� ��ĭ �̵�
		en->y = y_move;
		map[en->y][en->x] = EMPTY_LAND;										//y���� �״�� �̵�
		if (en->state <= ENE_R) en->state = 4 - en->state;       //�ٲ� ���⿡ �°� ���� ����
		else en->state = 12 - en->state;
	}
	else if (x_hit == 0 && y_hit == 1) {                          //y���� �浹
		en->x = x_move;                                         //x���� �״�� �̵�
		en->y -= en->way_y;  
		map[en->y][en->x] = EMPTY_LAND;						//y���� ���� �̵�
		if (en->state != ENE_L) en->state = 8 % en->state;       //���� ����
	}
	else if (x_hit == 1 && y_hit == 1) {                          //x,y �� �� �浹
		en->x -= en->way_x;                                     //�Ѵ� ���� �̵�
		en->y -= en->way_y;
		map[en->y][en->x] = EMPTY_LAND;
		if (en->state < ENE_R) en->state += 4;                   //���� ����
		else en->state -= 4;
	}
	
}
void EnemyControl(int map[][MAP_WIDTH], enemy en[ENEMY_NO]) {
	for (int i = 0; i < ENEMY_NO; i++) {          //enemy�� ���¿� ���� �̵� ���� ������
		if (en[i].life == EN_ALIVE || en[i].life == EN_KING) {
			switch (en[i].state) {
			case ENE_L:                        //��
				en[i].way_x = -1;
				en[i].way_y = 0;
				break;
			case ENE_LU:                        //�»�
				en[i].way_x = -1;
				en[i].way_y = 1;
				break;
			case ENE_U:                        //��
				en[i].way_x = 0;
				en[i].way_y = 1;
				break;
			case ENE_RU:                        //���
				en[i].way_x = 1;
				en[i].way_y = 1;
				break;
			case ENE_R:                        //��
				en[i].way_x = 1;
				en[i].way_y = 0;
				break;
			case ENE_RD:                        //����
				en[i].way_x = 1;
				en[i].way_y = -1;
				break;
			case ENE_D:                        //��
				en[i].way_x = 0;
				en[i].way_y = -1;
				break;
			case ENE_LD:                        //����
				en[i].way_x = -1;
				en[i].way_y = -1;
				break;
			default:
				en[i].state = ENE_L;
				break;
			}
			//���� ����
			//������ ���� �̵� ���⿡ �°� ������
			if(en[i].life ==EN_ALIVE)
			MoveEnemy(map, &(en[i]));// ���� �����δ�.  
			//���⼭ ������ ���� �ڵ带 �ۼ��� ������ �߰������� �ۼ��� Enemy_king �� �Ϲ� enemy�� �����ϱ� ���ؼ��̴�.
			//�Ϲ����� ���� �̵��� MoveEnemy�� ���ؼ� �Լ��� �ѹ� ȣ��ɶ����� ���� state�� ���� ��ĭ�� �����δ�. 
			//Enemy_king�� ��� Ư¡�� ��ĭ�� �����̵�, �� ĭ�� �÷��̾��� ���ΰ�� ������ ���� ���Ѵ� ����� ���
			else if (en[i].life == EN_KING)
			MoveEnemyKing(map, &en[i]);
		}
	}
}
int MakeMap(int map[][MAP_WIDTH], point* player, enemy en[ENEMY_NO], float paly_time, int speed) { //���� �� �� Ȯ��
	int remain_empty = 0;
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (map[i][j] == EMPTY_LAND) remain_empty++;
		}
	}
	return remain_empty;
}
void CheckContour(int map[][MAP_WIDTH]) {			//����� ��θ� �������� ���� ������ �ٲپ���

		//���� ����
		while (route[0].sp >= 0) // ������ top �� -1�� �ɶ����� pop ���ÿ� �ִ� ������ ����̸� ���� ���ڸ��� ����� ��κ��� ���ʷ� my_land�� �ٲپ��ش�.
 		{
			map[route[route[0].sp].y][route[route[0].sp].x] = MY_LAND;
			route[0].sp--;
		}
}
int CalculateLand(int map[][MAP_WIDTH], point* player) {
	if (route[0].sp > -1 && map[player->y][player->x] == MY_LAND) {             //�� �Ա� ����
		CheckContour(map);
		player->state = STAY_IN;
		return 1;
	}
	return 0;
}
int CheckEnd(int map[][MAP_WIDTH], point* player, enemy en[ENEMY_NO], int remain) {
	if ((remain * 100) / (MAP_HEIGHT*MAP_WIDTH) < 40 && player->state == STAY_IN) return 1;            //���� ���� 30%�����̸� �¸�
	else {
		for (int i = 0; i < ENEMY_NO; i++) {                          //����ִ� ���� �÷��̾ �����ų� ����ִ� ���� Reached edge�� ������ �й�
			if ( (en[i].life == EN_ALIVE || en[i].life == EN_KING )&& (map[en[i].y][en[i].x] == REACHED_EDGE || (en[i].x == player->x && en[i].y == player->y)))
				return 0;
			
		}
	}
	return 2; // ��ȯ�� 0 : �й� 1 : �¸� 2 : ���� ���
}
int ManageNormalFlow(int map[][MAP_WIDTH], point* player, enemy en[ENEMY_NO], time_t startT, int speed) {	//��ü ������ �帧�� �����ϴ� �Լ�
	
	int remain_empty = 0;
	char key_input='0';
	int cheat = -1;
	time_t endT = 0, stop_T=0;

	//���� �ð��� ���ϴ� �Լ�
	endT = clock();													//���� �ð��� ��
	float play_time = (float)(endT - startT) / (CLOCKS_PER_SEC);	//���۽ð����� ����ð������� ����
																	//�� �� ������ �̿��Ͽ� �÷��� Ÿ���� ���� �� �ִ�
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
		if (cheat != 1)EnemyControl(map, en); // ġƮ�� �ߵ��� ���� ������ ���� �����̴�.

		for (int i = 0; i < speed + 5; i++) { //���ǵ� * unit_speed�� ���� �����̰� ���� ���ߴ� �ð��̴�. �� speed �� ���� �پ��� ���� ���� ��������.
			Sleep(UNIT_SPEED);
			end = CheckEnd(map, player, en, remain_empty);  // ������ �¸��ߴ���, �й��ߴ��� Ȯ�����ش�.
			play_time = (float)(clock() - startT) / (CLOCKS_PER_SEC);	 // ���� �ð��� ���ϴ� �Լ� ����ؼ� ���� �ð��� ����
			remain_empty = MakeMap(map, player, en, play_time, speed); 	  // ���� ���� ���� ����ؼ� ȭ�鿡 ����ִ� ������Ѵ�.
			if (end == 0)		//checkEnd�� ��ȯ�ϴ� ���� 0�϶� �й�, 1�϶� �¸��̴�. �� ��� �й�
			{
				STOP_SCREEN = 1; // ���������� ȭ������ϴ� ���� ���߰� �ϴ� �����̴�. ������ ���ο��� Ȯ��
				WaitForSingleObject(update_screen, INFINITE); //�����尡 ���������� ����Ǿ����� üũ�� �����ϰ� ����
				return 0;
			}
			else if (end == 1)	//checkEnd�� ��ȯ�ϴ� ���� 0�϶� �й�, 1�϶� �¸��̴�. �� ��� �¸�
			{
				STOP_SCREEN = 1;// ���������� ȭ������ϴ� ���� ���߰� �ϴ� �����̴�. ������ ���ο��� Ȯ��
				WaitForSingleObject(update_screen, INFINITE);//�����尡 ���������� ����Ǿ����� üũ�� �����ϰ� ����
				return 1;
			}
			
			if (_kbhit())		// Ű���尡 ������, ���۷κ��� �ϳ��� Ű�� �Է¹޴´�. �̷����ϴ� ������ _getch()�� BLOCKING�Լ��� �ƹ��͵� �������ʾҴµ� _getch�� �ϸ� �Է������������� ����Ѵ�. 
			{ 
				key_input = _getch();	//���ۿ� �ϳ��� ���� �а�
				if (key_input == -32) {	// key_input�� -32�϶� >> ���� ����Ű�� �ԷµǸ� �ΰ��� ���� ���ۿ� ����> 8��Ʈ�� ���� _getch()�� �������ִµ� 1110 0000 �� 128+64+32=224�� ���� ����� ��������
										//��ȯ�Ѵ�. 224�� -32�̶�� ���̹Ƿ� ������ ���� �Ǿ��ִ�.
					key_input = _getch();	//����Ű�� �ԷµǸ� ����Ű �������� �о����
					MoveByKey(map, player, key_input);		//�÷��̾ �����δ�.
				}
				else if(key_input==SPACE_KEY)	//���� �����̽�Ű�� ������
				{
					MoveByKey(map, player, key_input);	
				}
				else if (key_input == PAUSE_KEY)	//����ڰ� pŰ�� ������
				{
						STOP_SCREEN = 1;			//ȭ���� �۵���Ű�� ������ ����
						WaitForSingleObject(update_screen, INFINITE);	//������ �����ٸ���
						stop_T = clock();	//����ڰ� �����ð� üũ
						my_pause();		//ȭ�鿡 �ٸ���Ƽ��Ƽ�� ����, _getchar()�� ����
						startT += clock() - stop_T; // clcock()�Լ��� ���� ���ӽð��� ������ �ð��� �����ϹǷ�, ���۽ð��� �� �ð��� ���� ������Ž�� ���
						update_screen = CreateThread(NULL, 0, screen_update, (void*)&arg, 0, NULL);// ȭ���� ����ϴ� ������ �ٽ� ȣ��
				}
				else if (key_input == ESC_KEY) //����ڰ� ESCŰ�� ������,
				{
					STOP_SCREEN = 1; //ȭ�� �������
					WaitForSingleObject(update_screen, INFINITE);
					return 0; //����� �й�
				}
				else if (key_input == C_KEY)
				{
					cheat *= -1; //ġƮ�� 1�϶� �ߵ� -1�϶� ��ߵ�
				}
				
				
			}
			fflush(stdin);
		} 
	
	}
}
int ManageHardFlow(int map[][MAP_WIDTH], point* player, enemy en[ENEMY_NO], time_t startT, int speed) {	//��ü ������ �帧�� �����ϴ� �Լ�
	int cheat = -1;
	int remain_empty = 0;
	char key_input = '0';
	time_t endT = 0, stop_T = 0;

	//���� �ð��� ���ϴ� �Լ�

	endT = clock();													//���� �ð��� ��
	float play_time = (float)(endT - startT) / (CLOCKS_PER_SEC);	//���۽ð����� ����ð������� ����
																	//�� �� ������ �̿��Ͽ� �÷��� Ÿ���� ���� �� �ִ�
	int end = 2;

	remain_empty = MakeMap(map, player, en, play_time, speed);
	PrintView(map, player, en, play_time, speed, remain_empty);
	int lastkey_sec = 0;
	
	
	// ������ �Ѱ��� ���ڸ� ����ü �̿� ����


	struct _targ arg;
	arg.en = en;
	arg.map = map;
	arg.player = player;
	arg.play_time = &play_time;
	arg.speed = speed;
	arg.remain_empty = &remain_empty;

	update_screen = CreateThread(NULL, 0, screen_update, (void*)&arg, 0, NULL); //������ ����
	while (TRUE)
	{
		if (cheat != 1)EnemyControl(map, en);

		for (int i = 0; i < ENEMY_NO; i++)
		{
			en[i].state = rand() % 8;// ���� �̵������� ��ȯ
		}

		for (int i = 0; i < speed + 5; i++) { //���ǵ� * unit_speed�� ���� �����̰� ���� ���ߴ� �ð��̴�. �� speed �� ���� �پ��� ���� ���� ��������.
			Sleep(UNIT_SPEED);
			end = CheckEnd(map, player, en, remain_empty);
			play_time = (float)(clock() - startT) / (CLOCKS_PER_SEC);	 // ���� �ð��� ���ϴ� �Լ� ����ؼ� ���� �ð��� ����
			remain_empty = MakeMap(map, player, en, play_time, speed);
			if (end == 0)
			{
				STOP_SCREEN = 1; //������ ����
				WaitForSingleObject(update_screen, INFINITE); //������ ���� ���
				return 0;
			}
			else if (end == 1)
			{
				STOP_SCREEN = 1; //������ ����
				WaitForSingleObject(update_screen, INFINITE);//������ ���� ���
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
				else if (key_input == PAUSE_KEY) //����ڰ� ���� Ű�� ������
				{
						STOP_SCREEN = 1; //�����带 �����Ų��.
						WaitForSingleObject(update_screen, INFINITE); //������ ������
						stop_T = clock(); //���� �ð� üũ
						my_pause();	//_getchar�Լ� ȣ��
						startT += clock() - stop_T; //������ Ǯ���� ������ �ð���ŭ ���۽ð��� ������
						update_screen = CreateThread(NULL, 0, screen_update, (void*)&arg, 0, NULL); //�ٽ� ȭ�� ����
	
				}
				else if (key_input == ESC_KEY)
				{
					STOP_SCREEN = 1; //����ڰ� ���Ḧ ������, ������ ����
					WaitForSingleObject(update_screen, INFINITE);
					return 0; //�й�
				}
				else if (key_input == C_KEY)
				{
					cheat *= -1; //ġƮ�� 1�϶� �ߵ� -1�϶� ��ߵ�
				}


			}
			fflush(stdin);

		} // UNIT_SPEED * speed �� �ð�	

	}
}
int ManageCrazyFlow(int map[][MAP_WIDTH], point* player, enemy en[ENEMY_NO], time_t startT, int speed) {	//��ü ������ �帧�� �����ϴ� �Լ�
	int cheat = -1;
	int remain_empty = 0;
	char key_input = '0';
	time_t endT = 0, stop_T = 0;

	//���� �ð��� ���ϴ� �Լ�

	endT = clock();													//���� �ð��� ��
	float play_time = (float)(endT - startT) / (CLOCKS_PER_SEC);	//���۽ð����� ����ð������� ����
																	//�� �� ������ �̿��Ͽ� �÷��� Ÿ���� ���� �� �ִ�
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
		en[i].life = EN_KING;		//�� ������ ���� �°�!
	}
	update_screen = CreateThread(NULL, 0, screen_update, (void*)&arg, 0, NULL); //������ ȣ��
	while (TRUE)
	{
		if (cheat != 1)EnemyControl(map, en);
		if (speed >1) speed--;  		// ���Ǽӵ��� ���� ��������.					
		for (int i = 0; i < ENEMY_NO; i++)
		{
			en[i].state = rand() % 8;// ���� �̵������� ��ȯ
		}

		for (int i = 0; i < speed + 5; i++) { //���ǵ� * unit_speed�� ���� �����̰� ���� ���ߴ� �ð��̴�. �� speed �� ���� �پ��� ���� ���� ��������.
			Sleep(UNIT_SPEED);
			end = CheckEnd(map, player, en, remain_empty);
			play_time = (float)(clock() - startT) / (CLOCKS_PER_SEC);	 // ���� �ð��� ���ϴ� �Լ� ����ؼ� ���� �ð��� ����
			remain_empty = MakeMap(map, player, en, play_time, speed);
			if (end == 0)
			{
				STOP_SCREEN = 1;
				WaitForSingleObject(update_screen, INFINITE); //������ ���Ḧ ��޸���.
				return 0; // �й�
			}
			else if (end == 1)
			{
				STOP_SCREEN = 1; //������ ����
				WaitForSingleObject(update_screen, INFINITE);
				return 1; //�¸�
			}

			if (_kbhit())
			{
				key_input = _getch();
				if (key_input == -32) {
					key_input = _getch();
					MoveByKey(map, player, key_input); // �÷��̾ �����δ�.
				}
				else if (key_input == SPACE_KEY) //�����̽� Ű�� ������
				{
					MoveByKey(map, player, key_input);
				}
				else if (key_input == PAUSE_KEY) //���� Ű�� ������
				{
			
						STOP_SCREEN = 1;
						WaitForSingleObject(update_screen, INFINITE);
						stop_T = clock(); //����ڰ� ������ ������ �ð�
						my_pause();
						startT += clock() - stop_T; //����ڰ� ���� �����ð��� ������ �ѽð��� ���� ���۽ð��� �����ش�.
						update_screen = CreateThread(NULL, 0, screen_update, (void*)&arg, 0, NULL); //�ٽ� ȭ�� ������Ʈ
					
				}
				else if (key_input == ESC_KEY) 
				{
					STOP_SCREEN = 1;
					WaitForSingleObject(update_screen, INFINITE);
					return 0; //�й�
				}
				else if (key_input == C_KEY)
				{
					cheat *= -1; //ġƮ�� 1�϶� �ߵ� -1�϶� ��ߵ�
				}


			}
			fflush(stdin);

		} // UNIT_SPEED * speed �� �ð�	

	}
}
void RunNormalGame() {								//�Ϲݰ��� ����
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
		printf("\t\t\t����� ������ %d �Դϴ�. \n", (int)((MAP_WIDTH)*(MAP_HEIGHT)*(SCALE_FAC) / (time*speed)));
		printf("				Name : ");
		fflush(stdin);		
		scanf("%s", name);
		//�����߰��� ����
		//������ �ʴ� ���� �������� ���ߴ�. �� �Ѹ���/(�ѽð�*�ӵ�)�� �����̴�.
		AddScore(name, (int)((MAP_WIDTH)*(MAP_HEIGHT)*(SCALE_FAC)/(time*speed)));

	}
	else {
		printf("				G a m e  O v e r\n");
		Sleep(100);
		getchar();
		getchar();
	}

}
void ViewScoreBoard() {								//�������� ������
	int n = 0;
	char name[NAME_LENGTH] = { 0 };
	char score[NAME_LENGTH] = { 0 };
	struct _name_score name_score[MAX_LIST];

	FILE *fp = fopen("scoreBoard.txt", "r");

	if (fp == NULL) {
		printf("������ �� �� �����ϴ�.\n");
		fflush(stdin);
		getchar();
		return;
	}

	system("cls");
	print_logo();
	printf("\n\n=======SCORE=======\n");
	//���⸦ ����
	for (int i = 0; i<10 &&(fscanf(fp, "%s\n%d", name_score[i].name, &name_score[i].score) != EOF); i++)
	{
		printf("%d.\t%-10s\t%-5d\n",i+1, name_score[i].name, name_score[i].score);
	}
	// ScoreBoard.txt ������ �а�,
	// ���Ŀ� �°� ���������� ���
	printf("Enter AnyKeys");
	Sleep(100);
	getchar();
	getchar();
	//fflush(stdin);
}
void AddScore(char* name, int score) {				//������ ����
	int i=0, j=0, k=0, length = 0;
	char name_list[LIST_LENGTH][NAME_LENGTH] = { 0 };
	int score_list[LIST_LENGTH] = { 0 };

	FILE * fp;

	fp = fopen("scoreBoard.txt", "r"); // �켱 �б��������� �����͸� �о�´�.
	if (fp != NULL) {	//������ �����ϸ�!
			for (i=0;i < MAX_LIST;i++)	
			if (fscanf(fp, "%s\n%d", name_list[i], &score_list[i]) == EOF)	break;
		fclose(fp);// ���� �о�´����� �迭�� �����Ѵ�.
	}
	fp = fopen("scoreBoard.txt", "w"); //���� ���� �ۼ� ���� �ڷ� ����
	if (fp == NULL) {
		fflush(stdin);
		return;
	}
	while (score < score_list[j] && j <i && i != 0)
	{
		fprintf(fp, "%s\n%d\n", name_list[j], score_list[j]);
		j++; // score���� �� ���������� �ٽþ�
	}
	if (j < MAX_LIST) {	 //���� �� ���� 10������ ���� �� �̸��� ���� ���
		fprintf(fp, "%s\n%d\n", name, score); 
	}
	while (j < i)	//���� ����(j+1) �о�� �� i ���� ���������� �������� ä������
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
		printf("\t\t\t[crazy���]����� ������ %d �Դϴ�. \n", (int)((MAP_WIDTH)*(MAP_HEIGHT)*(SCALE_FAC*3) / (time*speed)));
		printf("				Name : ");

		fflush(stdin);
		scanf("%s", name);
		strcat(name, "[CRAZY]");
		//�����߰��� ����
		//������ �ʴ� ���� �������� ���ߴ�. �� �Ѹ���/(�ѽð�*�ӵ�)�� �����̴�. �ϵ����� ��� �߰������� �ִ�.
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
		printf("\t\t\t[�ϵ���]����� ������ %d �Դϴ�. \n", (int)((MAP_WIDTH)*(MAP_HEIGHT)*(SCALE_FAC*2) / (time*speed)));
		printf("				Name : ");

		fflush(stdin);
		scanf("%s", name);
		strcat(name, "[HARD]");
		//�����߰��� ����
		//������ �ʴ� ���� �������� ���ߴ�. �� �Ѹ���/(�ѽð�*�ӵ�)�� �����̴�. �ϵ����� ��� �߰������� �ִ�.
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
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); //�ܼ� �ڵ��� �޴´�.
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleTitle("�����Ա� ����");//cmdŸ��Ʋ�� �����Ա� �������� ����
	SetConsoleDisplayMode(consoleHandle, CONSOLE_FULLSCREEN_MODE, 0); //��üȭ������ ����
	SetConsoleCursorInfo(consoleHandle, &info); // �ܼ� Ŀ���� �Ⱥ��̰��Ѵ�.
}
void my_fflush(void)
{
	while (getchar() == '\n')break;
}
void my_pause(void)
{
	printf("������ �ٽý����Ϸ��� �ƹ�Ű�� ������!\n������ �����Ϸ��� ESC�� ��������!!\n\n\n");
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