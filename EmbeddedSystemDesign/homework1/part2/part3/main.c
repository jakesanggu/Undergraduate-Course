#include <stdio.h>
#include "my_numeric.h"
#include <unistd.h>



#define	_TO_STRING_(a)	#a
#define TO_STRING(a)	_TO_STRING_(a)

#define _MAX_LIMIT_	50000
#define INPUT_NUMBER	2


int main(int argc, char* argv[]){

int val[INPUT_NUMBER]={};
for(int i = 0 ; i < INPUT_NUMBER ;	){
	printf(TO_STRING(_MAX_LIMIT_) "자리 이하의 %d번째 수를 입력하세요\n",i+1); // 50000자리 이하 몇번째 수 입력
	scanf("%d",&val[i]); // scanf로 입력받는다.
	if(val[i] < _MAX_LIMIT_+1) //만일 50000이하라면 다음값 입력
		i++;
	else
		printf(TO_STRING(_MAX_LIMIT_) "이하의 수를 입력해주세요\n"); //50000이상이면 재입력
}


printf("최대 공약수는 %d 입니다\n", g_common_divisor(val,sizeof(val)/sizeof(int))); //최대 공약수 출력
printf("최소 공배수는 %d 입니다\n", l_common_multiple(val,sizeof(val)/sizeof(int))); //최소 공배수 출력
fflush(stdout);

if(argc > 1)
	execv(argv[1],&argv[1]); //만일 다음 프로그램이 인자로 전해지면, 덮어씌운다.

return 0;
}

