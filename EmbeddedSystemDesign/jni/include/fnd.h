/*
 * fnd.h
 *
 *  Created on: 2019. 5. 9.
 *      Author: LEE SANG GU
 */

#ifndef FND_H_
#define FND_H_

#define GPIO_SEG_SEL0 112
#define GPIO_SEG_SEL1 113
#define GPIO_SEG_SEL2 114
#define GPIO_SEG_SEL3 115
#define GPIO_SEG_SEL4 116
#define GPIO_SEG_SEL5 108

#define GPIO_SEG_DATA_A		192
#define GPIO_SEG_DATA_B		193
#define GPIO_SEG_DATA_C		194
#define GPIO_SEG_DATA_D		195
#define GPIO_SEG_DATA_E		196
#define GPIO_SEG_DATA_F		197
#define GPIO_SEG_DATA_G		198
#define GPIO_SEG_DATA_H		199


#define	WRITE_TIME			1000
#define DELAY_TIME			1000

#include "./include/gpio.h"
#include <unistd.h>

extern unsigned int fndcontrol[6];
extern unsigned int fnddata[8];


void fnd_write(unsigned int seg_pos , char data);
void fnd_write_string(char str[]);

#endif /* FND_H_ */

