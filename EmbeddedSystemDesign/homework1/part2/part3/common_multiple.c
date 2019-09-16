#include <stdlib.h>
#include <string.h>
#include "my_numeric.h"


int l_common_multiple(int val[], int len){
// 3 18의 최소 공배수 -> 18
// 10 12 의 최소공배수 -> 60일건데    2   10  12   -> 2   5   6 
int com = g_common_divisor(val,len);
// val 내부에서 서로소 체크
if( com != 1 ) //만일 최대공약수가 존재하면
{
	int* divided_val =malloc(sizeof(int)*len);
	memcpy(divided_val, val, len* sizeof(int) );

	for(int i =0; i <len; i++)
		divided_val[i] /= com; //구하고자 하는 수를 최대공약수로 나눈다.


	return com * l_common_multiple(divided_val, len); //최소공배수는 = 최대공약수 *  서로소인 두수 
}//end if
else//최대 공약수가 존재하지 않으면
{
	int mul_val=1;
	for(int i = 0;  i <len ; i++)
		mul_val *= val[i];

	return mul_val; //서로소이면 두 서로소의 곱을 반환한다.
} //end else


}

