/*
 * gpio.h
 *
 *  Created on: 2019. 5. 9.
 *      Author: LEE SANG GU
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

#define GPIO_OUTPUT		0
#define GPIO_INPUT		1
#define GPIO_LOW		0
#define GPIO_HIGH		1

#define PIZO		202
#define VIBRATOR	162
#define STATUS_LED	207

#define SYSFS_GPIO_DIR "sys/class/gpio"
#define MAX_BUF	128





int gpio_export(unsigned int gpio);
int gpio_unexport(unsigned int gpio);
int gpio_set_dir(unsigned int gpio, unsigned int dir);
int gpio_set_val(unsigned int gpio, unsigned int val);
int gpio_get_val(unsigned int gpio, unsigned int*val);





#endif /* GPIO_H_ */
