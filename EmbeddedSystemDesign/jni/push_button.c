#include  "./include/queue.h"
#include "./include/gpio.h"
#include "./include/push_button.h"
#include "./include/service.h"
#include "./include/interrupt.h"
#include <unistd.h>

#define delay	100000
extern queue_t request_queue;
extern int services_cntl[NUMBER_OF_SERVICES];



void* pushbutton_service1(void* arg){

queue_element queue_detect = {PB1,BUTTON_IS_PUSHED};

while(services_cntl[PB_SERVICE]){
	usleep(delay);
	if(gpio_read_val(GPIO_SW1) == BUTTON_IS_PUSHED ){
		while(services_cntl[PB_SERVICE]){
			usleep(delay);
			if(gpio_read_val(GPIO_SW1) == BUTTON_RELEASED ){
				THREAD_LOCK;
				queue_enqueue(&request_queue,queue_detect);
				THREAD_UNLOCK;
				break;
			}
		}
	}
}
}
void* pushbutton_service2(void* arg){
queue_element queue_detect = {PB2,BUTTON_IS_PUSHED};

while(services_cntl[PB_SERVICE]){
	usleep(delay);
	if(gpio_read_val(GPIO_SW2) == BUTTON_IS_PUSHED ){
		while(services_cntl[PB_SERVICE]){
			usleep(delay);
			if(gpio_read_val(GPIO_SW2) == BUTTON_RELEASED ){
				THREAD_LOCK;
				queue_enqueue(&request_queue,queue_detect);
				THREAD_UNLOCK;
				break;
			}
		}
	}
}
}
void* pushbutton_service3(void* arg){

queue_element queue_detect = {PB3,BUTTON_IS_PUSHED};

while(services_cntl[PB_SERVICE]){
	usleep(delay);
	if(gpio_read_val(GPIO_SW3) == BUTTON_IS_PUSHED ){
		while(services_cntl[PB_SERVICE]){
			usleep(delay);
			if(gpio_read_val(GPIO_SW3) == BUTTON_RELEASED ){
				THREAD_LOCK;
				queue_enqueue(&request_queue,queue_detect);
				THREAD_UNLOCK;
				break;
			}
		}
	}
}
}
void* pushbutton_service4(void* arg){

queue_element queue_detect = {PB4,BUTTON_IS_PUSHED};

while(services_cntl[PB_SERVICE]){
	usleep(delay);
	if(gpio_read_val(GPIO_SW4) == BUTTON_IS_PUSHED ){
		while(services_cntl[PB_SERVICE]){
			usleep(delay);
			if(gpio_read_val(GPIO_SW4) == BUTTON_RELEASED ){
				THREAD_LOCK;
				queue_enqueue(&request_queue,queue_detect);
				THREAD_UNLOCK;
				break;
			}
		}
	}
}
}
void* pushbutton_service5(void* arg){

queue_element queue_detect = {PB5,BUTTON_IS_PUSHED};

while(services_cntl[PB_SERVICE]){
	usleep(delay);
	if(gpio_read_val(GPIO_SW5) == BUTTON_IS_PUSHED ){
		while(services_cntl[PB_SERVICE]){
			usleep(delay);
			if(gpio_read_val(GPIO_SW5) == BUTTON_RELEASED ){
				THREAD_LOCK;
				queue_enqueue(&request_queue,queue_detect);
				THREAD_UNLOCK;
				break;
			}
		}
	}
}
}


