#include "my_numeric.h"

int g_common_divisor(int val[], int len){
//최대 공약수를 찾기 위하여,  N개의 수중에 최소값을 찾는다.
for(int i = find_min(val,len) ; i > 0 ; i--){
	if(i == 1)	return 1; //만일 a,b,c,d,e ... 의 수중 최소값이 1이면 최대공약수도 1이다.

	for(int j =0, k =0 ; j < len; j++){  //입력된 값들의 배열을 탐색한다. 

	if( val[j] % i == 0) //입력된 수의 최소값 i 가 입력된 모든 값들과 나누어 나머지가 0일때까지 반복
		k++;
	if(k == len)
		return i; // 즉 i가 모든 수와 나누어떨어지면 i가 최대공약수
	}

}


}

