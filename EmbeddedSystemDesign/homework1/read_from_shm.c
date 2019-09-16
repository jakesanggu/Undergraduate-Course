
#include <sys/ipc.h>
#include <sys/shm.h>

int read_from_shm(int key, int size, void** mem_addr )
{
int mem_id;
if ( -1 == ( mem_id = shmget( (key_t)key, size, IPC_CREAT|0666)))  return -1;
if ( ( void *)-1 == ( *mem_addr = shmat( mem_id, ( void *)0, 0))) return -1;
}

