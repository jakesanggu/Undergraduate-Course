#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#define	KEY_NUM	9222
#define MEM_SIZE	(sizeof(int)*2)

int read_from_shm(int, int, void* );
double func0(int, int); //마름모 넓이 계산

int main(void){

int pid  = fork();

if( pid < 0) return -1;

else if(pid == 0) //child
	execlp("./part1/Part1.out", "./part1/Part1.out","./part2/Part2.out","./part2/part3/Part3.out",NULL);
else //parent
{

wait(NULL); //part1~3 가 끝나길 기다리다.
void* mem_addr;
if(-1 != read_from_shm(KEY_NUM, MEM_SIZE, &mem_addr)) //ipc 를 통하여 part2의 가로 세로의 길이를 얻어온다.
	printf("마름모의 넓이는 %lf입니다\n", func0( ((int*)mem_addr)[0],((int*)mem_addr)[1])); //마름모 넓이 계산 func0

}

return 0;


}
