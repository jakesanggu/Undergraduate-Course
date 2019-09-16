#define _STR_LENGTH_	9
#define _TO_STRING(a)    #a
#define TO_STRING(a)	_TO_STRING(a)

#include "extra.h"

int main(int argc, char* argv[])
{

char in_string[_STR_LENGTH_+1]={0}; //입력문자열
int sum_val=0, mul_val=1; // 합의 값과 곱의 값이 저장될 위치

printf(TO_STRING(_STR_LENGTH_) "자리의 수를 입력해주세요\n"); // _STR_LENGTH_에 따라 출력이 달라짐
scanf("%"TO_STRING(_STR_LENGTH_)"s",in_string); // %(n)s 에서 입력받을 최대문자열 길이 지정
func2(in_string,_STR_LENGTH_,&sum_val,&mul_val);  //모든 자리수를 합한다. // 모든 자리수를 곱하여 sumval mulval에 대입
printf("합의 값: %d 곱의 값: %d\n\n\n",sum_val, mul_val); //각자리의 합 곱 출력
fflush(stdout);



if(argc > 1){
	write_to_shm(sum_val,mul_val); //만일  part1, part2, part3를 출력한다면 part4와 공유하는 메모리에 마름모의 가로 세로를 씀
	execv(argv[1],&argv[1]);//다음 프로그램의 이미지를 덮어씀 
	}
return 0;
}

