void func2(char in_string[], int len, int* sum_val, int* mul_val){

for(int i=0 ; i <= len ; i++){
//입력받은 문자열 탐색
switch(in_string[i]){ //문자 -> 정수표현으로 곱과 합을 더하거나 곱함
        case '0': *sum_val += 0; *mul_val *= 0; break;
        case '1': *sum_val += 1; *mul_val *= 1; break;
        case '2': *sum_val += 2; *mul_val *= 2; break;
        case '3': *sum_val += 3; *mul_val *= 3; break;
        case '4': *sum_val += 4; *mul_val *= 4; break;
        case '5': *sum_val += 5; *mul_val *= 5; break;
        case '6': *sum_val += 6; *mul_val *= 6; break;
        case '7': *sum_val += 7; *mul_val *= 7; break;
        case '8': *sum_val += 8; *mul_val *= 8; break;
        case '9': *sum_val += 9; *mul_val *= 9; break;
        default:                              break;

} // end switch

} //end for


}
