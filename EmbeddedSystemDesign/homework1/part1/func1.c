
void func1(char in_string[], char out_string[], int len)
{
for(int i = 0, j = 0 ; i < len; i++ )
{ //입력배열을 탐색하여

if(in_string[i] != '0') //0이 아닌이상
        out_string[j++] =in_string[i]; //출력배열에 저장한다.

}
} //end func
