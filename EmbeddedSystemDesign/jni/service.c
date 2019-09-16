#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#include "./include/queue.h"
#include "./include/service.h"
#include "./include/push_button.h"
#include "./include/textlcd.h"
#include "./include/fnd.h"
#include "./include/debug.h"
#include "./include/math_express.h"
#include "./include/interrupt.h"

void update_screen();
static void perform_task(int,int);

extern int calc_mode;
extern int is_calc_succeed;
extern int services_cntl[NUMBER_OF_SERVICES];
extern char equation[MAX_EQUATION_LEN];
extern queue_t request_queue; //irq handler queue
extern unsigned char fndstring[7];
extern unsigned int fndcontrol[6];
extern unsigned int fnddata[8];

void* pushbutton_service1(void* arg);
void* pushbutton_service2(void* arg);
void* pushbutton_service3(void* arg);
void* pushbutton_service4(void* arg);
void* pushbutton_service5(void* arg);

void* core_service(void* arg)
{
#ifdef __DEBUG__
__DEBUG_WRITE__("Core Service On! %s \n"," ");
#endif


while(services_cntl[CORE_SERVICE])
{
	usleep(60000);
	if( request_queue.size > 0 )
	{
		THREAD_LOCK;
	queue_node *task = queue_dequeue(&request_queue);
		THREAD_UNLOCK;
	perform_task(task->data->src, task->data->request);
#ifdef __DEBUG__
__DEBUG_WRITE__("Completed task %s \n"," ");
#endif

	queue_free(task);

	}

}

}


void* pushbutton_service(void* arg)
{
#ifdef __DEBUG__
__DEBUG_WRITE__("PB Service On! %s \n"," ");
#endif
pthread_t  pb[5];
int ret[5];
pthread_create(&(pb[0]),NULL,pushbutton_service1,(void*)NULL);
pthread_create(&(pb[1]),NULL,pushbutton_service2,(void*)NULL);
pthread_create(&(pb[2]),NULL,pushbutton_service3,(void*)NULL);
pthread_create(&(pb[3]),NULL,pushbutton_service4,(void*)NULL);
pthread_create(&(pb[4]),NULL,pushbutton_service5,(void*)NULL);

pthread_join(pb[0],(void**)&ret[0]);
pthread_join(pb[1],(void**)&ret[1]);
pthread_join(pb[2],(void**)&ret[2]);
pthread_join(pb[3],(void**)&ret[3]);
pthread_join(pb[4],(void**)&ret[4]);



}

void* fnd_service(void* arg)
{
#ifdef __DEBUG__
__DEBUG_WRITE__("FND service On! %s \n"," ");
#endif


while(services_cntl[FND_SERVICE]){

	fnd_write_string(fndstring);

}


}




static void perform_task(int src, int req)
{
char buff[200];
struct ret rt ={0,};
queue_element queue_detect = {CALC_ERR,INT};

#ifdef __DEBUG__
__DEBUG_WRITE__("Signal SRC: %d",src);
__DEBUG_WRITE__("Req: %d \n", req);
#endif

switch(src)
{
case PB1:
          switch(req)
           {

          case BUTTON_IS_PUSHED: //up
        	  move_line_down_mdchg();// up button
        	  lcd_refresh();
        	  break;
           }
break;

case PB2:
           switch(req)
           {
           case BUTTON_IS_PUSHED:
        	   move_cursor_left(); //left button
        	   lcd_refresh();

       	break;
           }
    break;


case PB3:
           switch(req)
           {
           case BUTTON_IS_PUSHED: //move_cursor_right;
        	   strchange(curpos2strpos());
        	   //java_clear_string();
        	   //java_change_string('1');
        	   break;
           }
   break;


case PB4:
          switch(req)
          {
          case BUTTON_IS_PUSHED:
        	  move_cursor_right();
        	  lcd_refresh();			// right button
                    break;
          }
break;

case PB5:
          switch(req)
          {
          case BUTTON_IS_PUSHED:
          	   move_line_up();// down button
           	   lcd_refresh();
                              break;
          }
break;


case CALC_ERR:



	 	 	 	 fndstring[0] = 'E';
	          	 fndstring[1] = 'r';
	          	 fndstring[2] = 'r';
	          	 fndstring[3] = ' ';
	             fndstring[4] = ' ';
	          	 fndstring[5] = ' ';
           switch(req)
           {
           case CHAR_NOT_VALID:
        	   strcpy(equation,"Char p");
        	   lcd_refresh();
           break;
           case ORDER_NOT_CRR:
        	   strcpy(equation,"Order p");
        	   lcd_refresh();
                 break;
           case PAREN_NOT_CRR:
        	   strcpy(equation,"braccket p");
        	   lcd_refresh();
        	   break;
           case TOO_SHORT:
        	   strcpy(equation,"short p");
        	   lcd_refresh();
        	  break;
           case STACK_UNDERFLOW:
        	   strcpy(equation,"wrong op");
        	   lcd_refresh();
        	    break;
           case STACK_RESULT_ERR:

        	   strcpy(equation,"Calc failed");

        	   lcd_refresh();
        	    break;

           default:

           break;
          }
     gpio_set_val(PIZO,GPIO_HIGH);
     gpio_set_val(VIBRATOR,GPIO_HIGH);
     usleep(100000);
     gpio_set_val(PIZO,GPIO_LOW);
     gpio_set_val(VIBRATOR,GPIO_LOW);

break;


#ifdef __DEBUG__
__DEBUG_WRITE__("Calc Error detection ! %d ",src);
__DEBUG_WRITE__(" %d \n",req);
#endif
           case CALC_SUC:

                      switch(req)
                      {
                      case INT:
                    	  fndstring[0] = '1';
                    	  fndstring[1] = 'n';
                    	  fndstring[2] = 't';
                    	  fndstring[3] = ' ';

                    	  fndstring[4] = ' ';
                    	  fndstring[5] = ' ';
                      break;

                      case DOUBLE:
                    	  fndstring[0] = 'R';
                    	  fndstring[1] = 'E';
                    	  fndstring[2] = 'A';
                    	  fndstring[3] = 'L';
                    	  fndstring[4] = ' ';
                    	  fndstring[5] = ' ';
                            break;

                     }
           break;


case MODE_CHANGE	:
       	   switch(req){

       	   case INT:
       		  fndstring[0] = '1';
       		                    	  fndstring[1] = 'n';
       		                    	  fndstring[2] = 't';
       		                    	  fndstring[3] = ' ';
       		                    	  fndstring[4] = ' ';
       		                    	  fndstring[5] = ' ';
       		    calc_mode = INT;
       	   break;

       	   case DOUBLE:
       		 fndstring[0] = 'R';
       		                    	  fndstring[1] = 'E';
       		                    	  fndstring[2] = 'A';
       		                    	  fndstring[3] = 'L';
       		                    	  fndstring[4] = ' ';
       		                    	  fndstring[5] = ' ';
       		    calc_mode = DOUBLE;
       	   break;


        	   }
break;


case CALC_EXEC:
	switch(req){

	case INT:
		calculate(equation,_MODE_INT,&rt);
		if(rt.success == 1){
					queue_detect.src = CALC_SUC;
					queue_detect.request = INT;
					THREAD_LOCK;
					queue_enqueue(&request_queue,queue_detect);
					THREAD_UNLOCK;
					is_calc_succeed = 1;
					sprintf(buff,"%d",rt.val.iret);
					strcpy(equation,buff);
					lcd_refresh();
				}
		else{

				queue_detect.src =CALC_ERR;
					switch(rt.err_code){
					case _ERROR_EQUATION_TOO_SHORT:
									queue_detect.request =TOO_SHORT;
							break;
					case _ERROR_EQUATION_CHAR_NOT_VALID:
									queue_detect.request =CHAR_NOT_VALID;
							break;
					case _ERROR_EQUATION_ORDER_NOT_CRR:
									queue_detect.request =ORDER_NOT_CRR;
							break;
					case _ERROR_EQUATION_PAREN_NOT_CRR:
									queue_detect.request =PAREN_NOT_CRR;
							break;
					case _ERROR_STACK_UNDERFLOW:
									queue_detect.request =STACK_UNDERFLOW;
							break;
					case _ERROR_STACK_RESULT_ERR:
									queue_detect.request =STACK_RESULT_ERR;
							break;
					case _ERROR_DIVE_ZERO_:
								queue_detect.request =STACK_RESULT_ERR;
							break;
					default :
						break;

					}
					is_calc_succeed = 0;
					THREAD_LOCK;
					queue_enqueue(&request_queue,queue_detect);
					THREAD_UNLOCK;
				}

		break;
	case DOUBLE:

		calculate(equation,_MODE_DOUBLE,&rt);

				if(rt.success == 1){
					queue_detect.src = CALC_SUC;
					queue_detect.request = DOUBLE;
							THREAD_LOCK;
							queue_enqueue(&request_queue,queue_detect);
							THREAD_UNLOCK;
							is_calc_succeed = 1;
							sprintf(buff,"%lf",rt.val.dret);
							strcpy(equation,buff);
							lcd_refresh();
						}
				else{
						queue_detect.src =CALC_ERR;
							switch(rt.err_code){
							case _ERROR_EQUATION_TOO_SHORT:
											queue_detect.request =TOO_SHORT;
									break;
							case _ERROR_EQUATION_CHAR_NOT_VALID:
											queue_detect.request =CHAR_NOT_VALID;
									break;
							case _ERROR_EQUATION_ORDER_NOT_CRR:
											queue_detect.request =ORDER_NOT_CRR;
									break;
							case _ERROR_EQUATION_PAREN_NOT_CRR:
											queue_detect.request =PAREN_NOT_CRR;
									break;
							case _ERROR_STACK_UNDERFLOW:
											queue_detect.request =STACK_UNDERFLOW;
									break;
							case _ERROR_STACK_RESULT_ERR:
											queue_detect.request =STACK_RESULT_ERR;
									break;
							case _ERROR_DIVE_ZERO_:
											queue_detect.request =STACK_RESULT_ERR;
									break;
							default :
								break;


							}
							is_calc_succeed = 0;
							THREAD_LOCK;
							queue_enqueue(&request_queue,queue_detect);
							THREAD_UNLOCK;
						}


		break;




	}
	break;


default:
	break;

}

    gpio_set_val(STATUS_LED,GPIO_HIGH);
    usleep(10000);
    gpio_set_val(STATUS_LED,GPIO_LOW);

}


