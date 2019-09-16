
#include "./include/textlcd.h"
#include "./include/gpio.h"
#include "./include/math_express.h"
#include "./include/debug.h"
#include "./include/queue.h"
#include "./include/interrupt.h"
#include "./include/service.h"

#define MAX_EQUATION_LEN	200
#define EXECUTE_CALC	-3

unsigned int textlcd_control[3] = {GPIO_TEXT_EN , GPIO_TEXT_RW,GPIO_TEXT_RS};
unsigned int textlcd_data[8] = {GPIO_TEXT_D0, GPIO_TEXT_D1,GPIO_TEXT_D2,GPIO_TEXT_D3,GPIO_TEXT_D4,GPIO_TEXT_D5,GPIO_TEXT_D6,GPIO_TEXT_D7};


int  lcd_line_pos = 0;
int  lcd_cur_pos = 0;
extern char equation[MAX_EQUATION_LEN];
extern int calc_mode;
extern queue_t request_queue; //irq handler queue

void setcommand(unsigned char command){

int i = 0;
gpio_set_val( textlcd_control[2], GPIO_LOW);
gpio_set_val( textlcd_control[1], GPIO_LOW);
gpio_set_val( textlcd_control[0], GPIO_LOW);

usleep(10);

for(i = 0 ; i < 8 ; i++){

	if(command & 0x01 )
		gpio_set_val(textlcd_data[i],GPIO_HIGH);
	else
		gpio_set_val(textlcd_data[i],GPIO_LOW);

	command >>= 1;
}

usleep(10);

gpio_set_val( textlcd_control[0], GPIO_HIGH);
usleep(10);
gpio_set_val( textlcd_control[0], GPIO_LOW);
usleep(41);
}


static void writebyte(unsigned char data){

int i = 0;
gpio_set_val( textlcd_control[1], GPIO_LOW);
gpio_set_val( textlcd_control[2], GPIO_HIGH);
gpio_set_val( textlcd_control[0], GPIO_LOW);
usleep(10);

switch(data){
case '*':
			data = 'x';
			break;

case '@':
			data = SQRT;
			break;
case '~':
			data = TILTA;
default :
			break;
}




for(i = 0 ; i < 8 ; i++){
					if(data & 0x01 )
							gpio_set_val(textlcd_data[i],GPIO_HIGH);
					else
							gpio_set_val(textlcd_data[i],GPIO_LOW);
					data >>= 1;


}

usleep(10);
gpio_set_val( textlcd_control[0], GPIO_HIGH);
usleep(10);
gpio_set_val( textlcd_control[0], GPIO_LOW);
usleep(41);
}


static void generate_char(unsigned char sel , unsigned char arr[8]){

	int i;

	setcommand(0x40 | ((sel & 0x07)<<3));

	for ( i = 0 ;  i < 8 ; i++){
		writebyte(arr[i]);
	}

}


void initializer_textlcd(void){

setcommand(0x38);
setcommand(CURSOR_EN_COMMAND);
setcommand(CLEAR_DISPLAY_COMMAND);
usleep(1960);
setcommand(ENTRY_MODE_1);


/*
 * special char bit pattern
 *
 * sqrt , uparr, downarr, inv
 */

unsigned char sqrt[] = {0x03,0x02,0x02,0x12,0x0a,0x06,0x02,0x00};
unsigned char uparr[] ={0x04,0x0e,0x1f,0x04,0x04,0x04,0x04,0x04};
unsigned char downarr[]= {0x00,0x04,0x04,0x04,0x04,0x1f,0x0e,0x04};
unsigned char box[] = {0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f};
unsigned char tilta[] = {0x00,0x00,0x00,0x15,0x0a,0x00,0x00,0x00};

generate_char(SQRT,sqrt);
generate_char(UP_ARR,uparr);
generate_char(DOWN_ARR,downarr);
generate_char(TILTA,tilta);

}

void writestring(char tstr[] , int nth_line, int cursor_pos){

int len = equation_length(tstr);
char str[200] ={0,};

int i=0, j =0;

while(tstr[i] != 0){

	if(tstr[i] == ' ')
		i++;
	else
		str[j++]=tstr[i++];
}
str[j] = 0;

change_symbol(str,"sqrt_","@");
change_symbol(str, "exp_","e");
change_symbol(str, "<<","<");
change_symbol(str, ">>",">");

int total_line = strlen(str) / ROW ;

strcpy(equation,str);

nth_line = nth_line;
int start_pos = ROW * nth_line;
i =0;

setcommand(CLEAR_DISPLAY_COMMAND);
setcommand(POS_02);



if(start_pos > strlen(str) ){
#ifdef __DEBUG__
	__DEBUG_WRITE__("Last pos writing WRITE %d",1);
#endif
	writestring(equation,total_line,0);
	return ;
}


while( (i < ROW) && (str[i + start_pos] != 0 ) ){
	writebyte(str[i + start_pos]);
	i++;
}


if( total_line - nth_line > 0){
	i =0;
	setcommand(POS_12);
	while( (i < ROW) && str[i + ( start_pos + ROW) ] != 0 ){
	writebyte(str[i + ( start_pos + ROW)]);
	i++;
	}
}
else{
	setcommand(POS_114);
	writebyte(':');
	writebyte('C');
}

// writing arrows

if(nth_line >  0 ){
	setcommand(POS_00);
	writebyte(UP_ARR);
}
if(nth_line < total_line){
	setcommand(POS_10);
		writebyte(DOWN_ARR);
}



if((cursor_pos < 0)){
	setcommand(POS_01);
	setcommand(CURSOR_SR);
}
else if(cursor_pos < ROW){
	setcommand(POS_02 + cursor_pos - 1);
	setcommand(CURSOR_SR);
}
else if( cursor_pos < (2*ROW)){
	setcommand(POS_12 + (cursor_pos % ROW) - 1);
	setcommand(CURSOR_SR);
}
else{
	setcommand(POS_114);
	setcommand(CURSOR_SR);
}


}

void move_cursor_right(void){
	if(lcd_cur_pos < 2*ROW -1)
		lcd_cur_pos++;
}
void move_cursor_left(void){
	if(lcd_cur_pos > 0)
		lcd_cur_pos--;
	else
		lcd_cur_pos = 2*ROW -1;
}

void move_line_up(void){

	int total_line = strlen(equation) / ROW ;

	if(lcd_line_pos <= total_line)
		lcd_line_pos++;

}

void move_line_down_mdchg(void){
	if(lcd_line_pos == 0){
		java_change_mode();
	}
	if(lcd_line_pos > 0)
		lcd_line_pos--;
}

void lcd_refresh(void){

		writestring(equation ,lcd_line_pos, lcd_cur_pos);
}

int curpos2strpos(void){

	int ret= (lcd_line_pos * ROW) + lcd_cur_pos;

	if((lcd_cur_pos ==2*ROW-1) &&  (lcd_line_pos ==strlen(equation) /(2*ROW) ) )
			return EXECUTE_CALC;

	if(ret < strlen(equation)){
#ifdef __DEBUG__
	__DEBUG_WRITE__("The selected char is %c\n",equation[ret]);
#endif
		return ret;

	}
	else
		return	-1;
}

void strchange(int pos){

	if(pos == EXECUTE_CALC){
		queue_element queue_detect = {CALC_EXEC,INT};
		queue_detect.request = calc_mode;
		THREAD_LOCK;
		queue_enqueue(&request_queue,queue_detect);
		THREAD_UNLOCK;
	}

	if(pos < 0)
		return;

	switch(equation[pos]){

	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
		equation[pos]++;
		break;
	case '9':
		equation[pos] = '0';
		break;
	case '+':
		equation[pos] = '-';
		break;
	case '-':
		equation[pos] = '*';
			break;
	case '*':
		equation[pos] = '/';
		break;
	case '/':
		equation[pos] = '^';
		break;
	case '^':
		equation[pos] = '%';
		break;
	case '%':
		equation[pos] = '>';
		break;
	case '>':
		equation[pos] = '<';
		break;
	case '<':
		equation[pos] = '&';
		break;
	case '&':
		equation[pos] = '|';
		break;
	case '|':
		equation[pos] = '=';
		break;
	case '=':
		equation[pos] = '+';
		break;
	default:

		break;
	}
lcd_refresh();
java_update_str(equation);
}



