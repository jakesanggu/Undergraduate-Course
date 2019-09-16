#include <stdlib.h>

int find_min(int val[], int len){

if(len <= 0)
	exit(1);

int min = val[0]; 
for(int i = 0; i < len  ; i ++){
	if( val[i] < min)
		min = val[i]; //최소값 갱신
} //end for

return min;
} //end find_min func

