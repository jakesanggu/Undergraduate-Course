/*
 * queue.h
 *
 *  Created on: 2019. 5. 9.
 *      Author: LEE SANG GU
 */

#ifndef QUEUE_H_
#define QUEUE_H_

typedef struct _queue_element{
	int src;
	int request;

} queue_element;

typedef struct _queue_node{

queue_element *data;
struct _queue_node *lnode;
struct _queue_node *rnode;
} queue_node;

typedef struct _queue_t{
queue_node* front;
queue_node* back;
int size;
} queue_t;

void queue_create(queue_t *queue);
void queue_enqueue(queue_t *queue ,queue_element data);
queue_node* queue_dequeue(queue_t* queue);
void queue_free(queue_node* node);




#endif /* QUEUE_H_ */
