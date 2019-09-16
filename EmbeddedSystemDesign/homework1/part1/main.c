#define _STR_LENGTH_ 10
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void func1(char [], char [], int);
void printarr(char []);

int main(int argc, char* argv[])
{
char in_string[_STR_LENGTH_]; //입력을 저장할 배열
char out_string[_STR_LENGTH_];//출력을 저장할 배열

printf("학번 입력: "); //학번을 입력:
scanf("%9s", in_string); // scanf로 학번을 입력받는다.

func1(in_string, out_string, _STR_LENGTH_); // 0이 아닌 값들만 outstring에 복사
printarr(out_string);

if(argc > 1) //만일 인자에 다음 프로그램 실행 파일의 위치가 존재하면
	execv(argv[1], &argv[1]); //종료하지 않고 다음 프로그램의 이미지를 덮어씌운다.

return 0;
}

