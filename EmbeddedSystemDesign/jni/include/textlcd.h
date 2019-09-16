/*
 * textlcd.h
 *
 *  Created on: 2019. 5. 9.
 *      Author: LEE SANG GU
 */

#ifndef TEXTLCD_H_
#define TEXTLCD_H_

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

#define ROW		14
#define	COL		2

#define GPIO_OUTPUT		0
#define GPIO_INPUT		1
#define GPIO_LOW		0
#define GPIO_HIGH		1

#define GPIO_TEXT_EN	104
#define GPIO_TEXT_RW	105
#define GPIO_TEXT_RS	106

#define GPIO_TEXT_D0	150
#define GPIO_TEXT_D1	151
#define GPIO_TEXT_D2	152
#define GPIO_TEXT_D3	153
#define GPIO_TEXT_D4	154
#define GPIO_TEXT_D5	155
#define GPIO_TEXT_D6	156
#define GPIO_TEXT_D7	157

#define CLEAR_DISPLAY_COMMAND		0x01
#define CURSOR_EN_COMMAND			0x0e
#define CURSOR_DIS_COMMAND		0x0c
#define CURSOR_LEFT_SHIFT_COMMAND	0x14
#define CURSOR_RIGHT_SHIFT_COMMAND	0x10
#define RETURN_HOME_COMMAND		0x02

#define POS_00				0x80
#define POS_01				0x81
#define POS_02				0x82
#define POS_03				0x83
#define POS_04				0x84
#define POS_05				0x85
#define POS_06				0x86
#define POS_07				0x87
#define POS_08				0x88
#define POS_09				0x89
#define POS_010				0x8a
#define POS_011				0x8b
#define POS_012				0x8c
#define POS_013				0x8d
#define POS_014				0x8e
#define POS_015				0x8f

#define POS_10				0xc0
#define POS_11				0xc1
#define POS_12				0xc2
#define POS_13				0xc3
#define POS_14				0xc4
#define POS_15				0xc5
#define POS_16				0xc6
#define POS_17				0xc7
#define POS_18				0xc8
#define POS_19				0xc9
#define POS_110				0xca
#define POS_111				0xcb
#define POS_112				0xcc
#define POS_113				0xcd
#define POS_114				0xce
#define POS_115				0xcf

#define ENTRY_MODE_1		0x06
#define ENTRY_MODE_2		0x07

#define CURSOR_SR			0x14

#define UP_ARR				0x01
#define DOWN_ARR			0x02
#define SQRT				0x00
#define INV					0x03
#define TILTA				0x04


void setcommand(unsigned char command);
static void writebyte(unsigned char data);
static void generate_char(unsigned char sel , unsigned char arr[8]);
void initializer_textlcd(void);
void writestring(char str[] , int nth_line, int cursor_pos);
void move_cursor_right(void);
void move_cursor_left(void);
void move_line_up(void);
void move_line_down_mdchg(void);
void lcd_refresh(void);

static inline void lcd_off(void){

		setcommand(0x08);
}

int curpos2strpos(void);

void strchange(int pos);
#endif /* TEXTLCD_H_ */
