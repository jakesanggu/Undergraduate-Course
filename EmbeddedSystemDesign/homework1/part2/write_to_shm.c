#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define KEY_NUM 9222
#define MEM_SIZE        (sizeof(int)*2)

void write_to_shm(int sum, int mul){

int   mem_id; //메모리 fd
void* mem_addr; // part4 프로그램과 공유할 메모리 주소
if ( -1 == ( mem_id = shmget( (key_t)KEY_NUM, MEM_SIZE, IPC_CREAT|0666))) exit(1);
if ( ( void *)-1 == ( mem_addr = shmat( mem_id, ( void *)0, 0))) exit(1);

((int*)mem_addr)[0] = sum; //합의 값 기록
((int*)mem_addr)[1] = mul; //곱의 값 기록
}




