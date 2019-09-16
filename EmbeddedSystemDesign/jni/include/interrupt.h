/*
 * interrupt.h
 *
 *  Created on: 2019. 5. 10.
 *      Author: LEE SANG GU
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_


//SRC----------------------
#define	PB1			0
#define	PB2			1
#define	PB3			2
#define	PB4			3
#define	PB5			4
		//Request ----------------

			#define     BUTTON_RELEASED    		0
			#define     BUTTON_IS_PUSHED        1


//SRC----------------------
#define CALC_ERR	5

		//Request----------------

		#define TOO_SHORT			0
		#define CHAR_NOT_VALID		1
		#define ORDER_NOT_CRR		2
		#define PAREN_NOT_CRR		3
		#define	STACK_UNDERFLOW		4
		#define STACK_RESULT_ERR	5
		#define _ERROR_DIVE_ZERO 	6

//SRC----------------------
#define CALC_SUC	6

		//Request----------------

		#define INT			0
		#define DOUBLE		1


#define MODE_CHANGE	7

		//Request----------------

		#define INT			0
		#define DOUBLE		1

#define CALC_EXEC	8

	//Request----------------

		#define INT			0
		#define DOUBLE		1

#endif /* INTERRUPT_H_ */
