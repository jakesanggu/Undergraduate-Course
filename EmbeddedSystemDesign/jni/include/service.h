/*
 * service.h
 *
 *  Created on: 2019. 5. 9.
 *      Author: LEE SANG GU
 */

#ifndef SERVICE_H_
#define SERVICE_H_

#include <pthread.h>
#define CORE_SERVICE	0
#define PB_SERVICE		1
#define FND_SERVICE		2
#define NUMBER_OF_SERVICES		3


void*   core_service(void*);
void*	pushbutton_service(void*);
void*   fnd_service(void*);

#define THREAD_LOCK	pthread_mutex_lock(&mutex)
#define THREAD_UNLOCK	pthread_mutex_unlock(&mutex)
#define THREAD_WAIT	pthread_cond_wait(&cond,&mutex);
#define THREAD_SIG	pthread_cond_signal(&cond);


#ifdef MAIN

pthread_mutex_t mutex;
pthread_cond_t cond;
int thread_cont;
#endif

#ifndef MAIN
extern pthread_mutex_t mutex;
extern pthread_cond_t cond;
extern int thread_cont;
#endif

#endif /* SERVICE_H_ */
