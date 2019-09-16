#include "./include/fnd.h"

void fnd_write(unsigned int seg_pos , char data){
int i;

	switch(data){

	case 'O':
		gpio_set_val(GPIO_SEG_DATA_A,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_B,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_C,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_D,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_E,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_F,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_G,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_H,GPIO_LOW);

		break;
	case 'F':
		gpio_set_val(GPIO_SEG_DATA_A,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_E,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_F,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_G,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_B,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_C,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_D,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_H,GPIO_LOW);

		break;
	case '1':

		gpio_set_val(GPIO_SEG_DATA_A,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_B,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_C,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_D,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_E,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_F,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_G,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_H,GPIO_LOW);

		break;
	case '2':
		gpio_set_val(GPIO_SEG_DATA_A,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_C,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_D,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_H,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_G,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_B,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_E,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_F,GPIO_LOW);

		break;

	case '3':
		gpio_set_val(GPIO_SEG_DATA_A,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_B,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_C,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_F,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_G,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_D,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_E,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_H,GPIO_LOW);
		break;

	case '4':
		gpio_set_val(GPIO_SEG_DATA_A,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_B,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_F,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_G,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_C,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_D,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_E,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_H,GPIO_LOW);
		break;

	case '5':
		gpio_set_val(GPIO_SEG_DATA_A,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_E,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_F,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_G,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_B,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_C,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_D,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_H,GPIO_LOW);
		break;

	case '6':
		gpio_set_val(GPIO_SEG_DATA_A,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_E,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_F,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_G,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_B,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_C,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_D,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_H,GPIO_LOW);
		break;
	case '7':
		gpio_set_val(GPIO_SEG_DATA_A,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_E,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_F,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_G,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_B,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_C,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_D,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_H,GPIO_LOW);
		break;
	case '8':
		gpio_set_val(GPIO_SEG_DATA_A,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_E,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_F,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_G,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_B,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_C,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_D,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_H,GPIO_LOW);
		break;
	case '9':
		gpio_set_val(GPIO_SEG_DATA_A,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_E,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_F,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_G,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_B,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_C,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_D,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_H,GPIO_LOW);
		break;

	case '0':
		gpio_set_val(GPIO_SEG_DATA_A,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_E,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_F,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_G,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_B,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_C,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_D,GPIO_HIGH);
		gpio_set_val(GPIO_SEG_DATA_H,GPIO_LOW);
		break;
	case 'E':
	         gpio_set_val(GPIO_SEG_DATA_A,GPIO_HIGH);
	         gpio_set_val(GPIO_SEG_DATA_B,GPIO_LOW);
	         gpio_set_val(GPIO_SEG_DATA_C,GPIO_LOW);
	         gpio_set_val(GPIO_SEG_DATA_D,GPIO_HIGH);
	         gpio_set_val(GPIO_SEG_DATA_E,GPIO_HIGH);
	         gpio_set_val(GPIO_SEG_DATA_F,GPIO_HIGH);
	         gpio_set_val(GPIO_SEG_DATA_G,GPIO_HIGH);
	         gpio_set_val(GPIO_SEG_DATA_H,GPIO_LOW);
	    break;

	   case 'r':
	         gpio_set_val(GPIO_SEG_DATA_A,GPIO_LOW);
	         gpio_set_val(GPIO_SEG_DATA_B,GPIO_LOW);
	         gpio_set_val(GPIO_SEG_DATA_C,GPIO_LOW);
	         gpio_set_val(GPIO_SEG_DATA_D,GPIO_LOW);
	         gpio_set_val(GPIO_SEG_DATA_E,GPIO_HIGH);
	         gpio_set_val(GPIO_SEG_DATA_F,GPIO_LOW);
	         gpio_set_val(GPIO_SEG_DATA_G,GPIO_HIGH);
	         gpio_set_val(GPIO_SEG_DATA_H,GPIO_LOW);
	         break;
	  case 't':
	  	         gpio_set_val(GPIO_SEG_DATA_A,GPIO_LOW);
	  	         gpio_set_val(GPIO_SEG_DATA_B,GPIO_LOW);
	  	         gpio_set_val(GPIO_SEG_DATA_C,GPIO_LOW);
	  	         gpio_set_val(GPIO_SEG_DATA_D,GPIO_HIGH);
	  	         gpio_set_val(GPIO_SEG_DATA_E,GPIO_HIGH);
	  	         gpio_set_val(GPIO_SEG_DATA_F,GPIO_HIGH);
	  	         gpio_set_val(GPIO_SEG_DATA_G,GPIO_HIGH);
	  	         gpio_set_val(GPIO_SEG_DATA_H,GPIO_LOW);
	  break;

	  case 'n':
	 	         gpio_set_val(GPIO_SEG_DATA_A,GPIO_LOW);
	 	         gpio_set_val(GPIO_SEG_DATA_B,GPIO_LOW);
	 	         gpio_set_val(GPIO_SEG_DATA_C,GPIO_HIGH);
	 	         gpio_set_val(GPIO_SEG_DATA_D,GPIO_LOW);
	 	         gpio_set_val(GPIO_SEG_DATA_E,GPIO_HIGH);
	 	         gpio_set_val(GPIO_SEG_DATA_F,GPIO_LOW);
	 	         gpio_set_val(GPIO_SEG_DATA_G,GPIO_HIGH);
	 	         gpio_set_val(GPIO_SEG_DATA_H,GPIO_LOW);
	 	         break;
	  case 'R':
		  	  	  	  	  	  	  gpio_set_val(GPIO_SEG_DATA_A,GPIO_HIGH);
		 			 	         gpio_set_val(GPIO_SEG_DATA_B,GPIO_HIGH);
		 			 	         gpio_set_val(GPIO_SEG_DATA_C,GPIO_HIGH);
		 			 	         gpio_set_val(GPIO_SEG_DATA_D,GPIO_LOW);
		 			 	         gpio_set_val(GPIO_SEG_DATA_E,GPIO_HIGH);
		 			 	         gpio_set_val(GPIO_SEG_DATA_F,GPIO_HIGH);
		 			 	         gpio_set_val(GPIO_SEG_DATA_G,GPIO_HIGH);
		 			 	         gpio_set_val(GPIO_SEG_DATA_H,GPIO_LOW);
		 			 	         break;


	  case 'A':
			 	         gpio_set_val(GPIO_SEG_DATA_A,GPIO_HIGH);
			 	         gpio_set_val(GPIO_SEG_DATA_B,GPIO_HIGH);
			 	         gpio_set_val(GPIO_SEG_DATA_C,GPIO_HIGH);
			 	         gpio_set_val(GPIO_SEG_DATA_D,GPIO_LOW);
			 	         gpio_set_val(GPIO_SEG_DATA_E,GPIO_HIGH);
			 	         gpio_set_val(GPIO_SEG_DATA_F,GPIO_HIGH);
			 	         gpio_set_val(GPIO_SEG_DATA_G,GPIO_HIGH);
			 	         gpio_set_val(GPIO_SEG_DATA_H,GPIO_LOW);
			 	         break;
	  case 'L':
				 	         gpio_set_val(GPIO_SEG_DATA_A,GPIO_LOW);
				 	         gpio_set_val(GPIO_SEG_DATA_B,GPIO_LOW);
				 	         gpio_set_val(GPIO_SEG_DATA_C,GPIO_LOW);
				 	         gpio_set_val(GPIO_SEG_DATA_D,GPIO_HIGH);
				 	         gpio_set_val(GPIO_SEG_DATA_E,GPIO_HIGH);
				 	         gpio_set_val(GPIO_SEG_DATA_F,GPIO_HIGH);
				 	         gpio_set_val(GPIO_SEG_DATA_G,GPIO_LOW);
				 	         gpio_set_val(GPIO_SEG_DATA_H,GPIO_LOW);
				 	         break;


	default:

		gpio_set_val(GPIO_SEG_DATA_A,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_E,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_F,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_G,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_B,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_C,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_D,GPIO_LOW);
		gpio_set_val(GPIO_SEG_DATA_H,GPIO_LOW);
		break;

	}

	gpio_set_val(seg_pos, GPIO_LOW);
	usleep(WRITE_TIME);
	gpio_set_val(seg_pos, GPIO_HIGH);


}


void fnd_write_string(char str[]){
	int i;

	for ( i = 0 ; i < 6 ; i ++){
		fnd_write(fndcontrol[i], str[i]);

	}


}

