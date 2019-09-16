/*
 * debug.h
 *
 *  Created on: 2019. 5. 10.
 *      Author: LEE SANG GU
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#define __DEBUG__
#define DEBUG_PATH	"/data/debug"
#define __DEBUG_WRITE__(STR,VAL)	do{	sprintf(mseg,STR,VAL);			\
						write(debug_fd,mseg,strlen(mseg));	\
					}while(0)


#ifndef MAIN

extern int debug_fd;
extern char mseg[150];
#endif

#ifdef MAIN
int debug_fd;
char mseg[150];
#endif


#endif /* DEBUG_H_ */
