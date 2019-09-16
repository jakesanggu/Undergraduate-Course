#define MAIN

#include <jni.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>


JavaVM* javaVM = NULL;
jobject OBJ;
jclass CLS;


#include "./include/gpio.h"
#include "./include/textlcd.h"
#include "./include/math_express.h"
#include "./include/push_button.h"
#include "./include/service.h"
#include "./include/queue.h"
#include "./include/fnd.h"
#include "./include/debug.h"
#include "./include/interrupt.h"


int services_cntl[NUMBER_OF_SERVICES];
queue_t request_queue; //irq handler queue
unsigned char fndstring[7] ="1nt   ";
char equation[MAX_EQUATION_LEN]= "Normal input";
int is_calc_succeed=0;
int calc_mode = 0;

pthread_t  process[NUMBER_OF_SERVICES];

extern unsigned int textlcd_control[3];
extern unsigned int textlcd_data[8];
unsigned int pushbutton[5] = {GPIO_SW1,GPIO_SW2,GPIO_SW3,GPIO_SW4,GPIO_SW5};
unsigned int fndcontrol[6] ={ GPIO_SEG_SEL0,GPIO_SEG_SEL1,GPIO_SEG_SEL2,GPIO_SEG_SEL3,GPIO_SEG_SEL4,GPIO_SEG_SEL5};
unsigned int fnddata[8] = {GPIO_SEG_DATA_A,GPIO_SEG_DATA_B,GPIO_SEG_DATA_C,GPIO_SEG_DATA_D,\
							GPIO_SEG_DATA_E,GPIO_SEG_DATA_F,GPIO_SEG_DATA_G,GPIO_SEG_DATA_H };




JNIEXPORT jint JNICALL Java_com_example_supercalc_MainActivity_writestring(JNIEnv * env, jobject obj, jstring jstr){

char *str = (*env)->GetStringUTFChars(env, jstr, NULL);

writestring(str,0,0);

return 1;

}

JNIEXPORT jint JNICALL Java_com_example_supercalc_MainActivity_init(JNIEnv * env, jobject obj){

#ifdef __DEBUG__
debug_fd = open(DEBUG_PATH, O_WRONLY|O_TRUNC);
__DEBUG_WRITE__("Init function called! %s \n"," ");
#endif


	int i = 0;

//INITIALIZE TEXTLCD GPIO-----------------------------------------------
	for(i =0; i < 3 ;i ++){
		gpio_export(textlcd_control[i]);
		gpio_set_dir(textlcd_control[i],GPIO_OUTPUT);
	}

	for(i =0; i < 8 ;i ++){
			gpio_export(textlcd_data[i]);
			gpio_set_dir(textlcd_data[i],GPIO_OUTPUT);
		}

	initializer_textlcd();
	writestring("Calculator> ",0,0);
//-----INITIALIZE PUSHBUTTON GPIO------------------------------------------

	for(i =0; i < 5 ;i ++){
			gpio_export(pushbutton[i]);
			gpio_set_dir(pushbutton[i],GPIO_INPUT);
		}

//-----INITIALIZE FND GPIO-------------------------------------------------

	for(i =0; i < 6 ;i ++){
				gpio_export(fndcontrol[i]);
				gpio_set_dir(fndcontrol[i],GPIO_OUTPUT);
				gpio_set_val(fndcontrol[i],GPIO_HIGH);
			}
	for(i =0; i < 8 ;i ++){
					gpio_export(fnddata[i]);
					gpio_set_dir(fnddata[i],GPIO_OUTPUT);
				}

//-------------------------------------------------------------------------

	gpio_export(PIZO);
	gpio_set_dir(PIZO,GPIO_OUTPUT);
	gpio_set_val(PIZO,GPIO_LOW);

	gpio_export(VIBRATOR);
	gpio_set_dir(VIBRATOR,GPIO_OUTPUT);
	gpio_set_val(VIBRATOR,GPIO_LOW);

	gpio_export(STATUS_LED);
	gpio_set_dir(STATUS_LED,GPIO_OUTPUT);
	gpio_set_val(STATUS_LED,GPIO_LOW);
//--------------------------pizo


#ifdef __DEBUG__
__DEBUG_WRITE__("GPIO SET COMPLETE %s \n"," ");
#endif

services_cntl[PB_SERVICE] =  1;
services_cntl[CORE_SERVICE] = 1;
services_cntl[FND_SERVICE] = 1;


queue_create(&request_queue);
pthread_mutex_init(&mutex,NULL);
pthread_cond_init(&cond,NULL);

pthread_create(&process[CORE_SERVICE],NULL,pushbutton_service,(void*)NULL);
pthread_create(&process[PB_SERVICE],NULL,core_service,(void*)NULL);
pthread_create(&process[FND_SERVICE],NULL,fnd_service,(void*)NULL);


return 1;

}


JNIEXPORT jint JNICALL Java_com_example_supercalc_MainActivity_terminate(JNIEnv * env, jobject obj){

	lcd_off();

	int i;

	//INITIALIZE TEXTLCD GPIO-----------------------------------------------
		for(i =0; i < 3 ;i ++){
			gpio_unexport(textlcd_control[i]);
		}

		for(i =0; i < 8 ;i ++){
				gpio_unexport(textlcd_data[i]);
			}

		writestring("bye",0,0);
	//-----INITIALIZE PUSHBUTTON GPIO------------------------------------------

		for(i =0; i < 5 ;i ++){
				gpio_unexport(pushbutton[i]);
			}

	//-----INITIALIZE FND GPIO-------------------------------------------------

		for(i =0; i < 6 ;i ++){
					gpio_unexport(fndcontrol[i]);
				}
		for(i =0; i < 8 ;i ++){
						gpio_unexport(fnddata[i]);
					}

	//-------------------------------------------------------------------------

		gpio_unexport(PIZO);
		gpio_unexport(VIBRATOR);
		gpio_unexport(STATUS_LED);

	//--------------------------pizo


#ifdef __DEBUG__
close(debug_fd);
#endif

	services_cntl[FND_SERVICE] = 0;
	services_cntl[PB_SERVICE] =  0;
	services_cntl[CORE_SERVICE] = 0;


	int ret[NUMBER_OF_SERVICES]; //number of services

	pthread_join(process[FND_SERVICE],(void**)&ret[FND_SERVICE]);
	pthread_join(process[PB_SERVICE],(void**)&ret[PB_SERVICE]);
	pthread_join(process[CORE_SERVICE],(void**)&ret[CORE_SERVICE]);

}

JNIEXPORT jdouble JNICALL Java_com_example_supercalc_MainActivity_dcalculate(JNIEnv * env, jobject obj, jstring jstr){



char *name = (*env)->GetStringUTFChars(env, jstr, NULL);
struct ret rt ={0,};
queue_element queue_detect = {CALC_SUC,DOUBLE};
calculate(name,_MODE_DOUBLE,&rt);


		if(rt.success == 1){
			is_calc_succeed = 1;
			THREAD_LOCK;
			queue_enqueue(&request_queue,queue_detect);
			THREAD_UNLOCK;
			return (jdouble) rt.val.dret;
		}
		else{
			queue_detect.src = CALC_ERR;
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
						queue_detect.request =_ERROR_DIVE_ZERO;
			break;
			default:
						queue_detect.request =STACK_RESULT_ERR;
											break;


			}
			is_calc_succeed = 0;
			THREAD_LOCK;
			queue_enqueue(&request_queue,queue_detect);
			THREAD_UNLOCK;
			return -1;
		}

}


JNIEXPORT jint JNICALL Java_com_example_supercalc_MainActivity_icalculate(JNIEnv * env, jobject obj, jstring jstr){


char *name = (*env)->GetStringUTFChars(env, jstr, NULL);
struct ret rt ={0,};
queue_element queue_detect = {CALC_SUC,INT};

calculate(name,_MODE_INT,&rt);



		if(rt.success == 1){
			is_calc_succeed = 1;
			THREAD_LOCK;
			queue_enqueue(&request_queue,queue_detect);
			THREAD_UNLOCK;
			return (jint) rt.val.iret;

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
				queue_detect.request =_ERROR_DIVE_ZERO;
									break;
			default:
				queue_detect.request =STACK_RESULT_ERR;
									break;


			}

#ifdef __DEBUG__
__DEBUG_WRITE__("Error Occured ! %d ",queue_detect.src);
__DEBUG_WRITE__(" %d \n",queue_detect.request);
#endif
			is_calc_succeed = 0;
			THREAD_LOCK;
			queue_enqueue(&request_queue,queue_detect);
			THREAD_UNLOCK;
			return -1;
		}
}

JNIEXPORT jint JNICALL Java_com_example_supercalc_MainActivity_signal(JNIEnv * env, jobject obj, jint source, jint request){

	queue_element queue_detect;

	queue_detect.src = source;
	queue_detect.request = request;
	THREAD_LOCK;
	queue_enqueue(&request_queue,queue_detect);
	THREAD_UNLOCK;

}

JNIEXPORT void JNICALL
Java_com_example_supercalc_MainActivity_Methodadd(JNIEnv *env, jobject obj){

	(*env)->GetJavaVM(env,&javaVM);
	jclass cls = (*env)->GetObjectClass(env,obj);
	CLS = (jclass)(*env)->NewGlobalRef(env,cls);
	OBJ = (*env)->NewGlobalRef(env,obj);


}

JNIEXPORT jint JNICALL Java_com_example_supercalc_MainActivity_issucceed(JNIEnv * env, jobject obj){
return is_calc_succeed;
}


/////////////////////////////////////////////////////Java function to C

void java_change_mode(){

	JNIEnv * env;
	(*javaVM)->AttachCurrentThread(javaVM,&env,NULL);
	jmethodID  method = (*env)->GetMethodID(env,CLS,"mode_change","()V");
	(*env)->CallVoidMethod(env,OBJ,method);

}




void java_clear_screen(){
	JNIEnv * env;
	(*javaVM)->AttachCurrentThread(javaVM,&env,NULL);
	jmethodID  method = (*env)->GetMethodID(env,CLS,"clear_string","()V");
	(*env)->CallVoidMethod(env,OBJ,method);

}

void java_update_str(char str[]){
	JNIEnv * env;
	(*javaVM)->AttachCurrentThread(javaVM,&env,NULL);
	jmethodID  method = (*env)->GetMethodID(env,CLS,"change_string","(Ljava/lang/String;)V");
	jstring name = (*env)->NewStringUTF(env,str);
	(*env)->CallVoidMethod(env,OBJ,method,name);
}







