#ifndef QUEUE_H
#define QUEUE_H

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#include "wrappers.h"
// #include "message.h"

/* DEBUG **********************************************************************/

struct msg {
	int value;
};
typedef struct msg msg_t;

static inline msg_t* msg_new(int value)
{
	msg_t* msg = malloc(sizeof(msg_t));
	if (msg == NULL) {
		fprintf(stderr, "Error: msg alloc failed.\n");
		return NULL;
	}
	msg->value = value;
	return msg;
}

static inline void msg_delete(msg_t* msg)
{
	SAFE_FREE(msg);
}

/****************************************************************************/

struct msg_node {
	msg_t* msg;
	struct msg_node* next;
};
typedef struct msg_node msg_node_t;

struct msg_queue {
	size_t size;
	pthread_mutex_t lock;
	msg_node_t* head;
	msg_node_t* tail;
};
typedef struct msg_queue msg_queue_t;

static inline msg_node_t* msg_node_new(msg_t* msg, msg_node_t* next)
{
	msg_node_t* msg_node = malloc(sizeof(msg_queue_t));
	if (msg_node == NULL) {
		fprintf(stderr, "Error: msg_node alloc failed.\n");
		return NULL;
	}
	msg_node->msg = msg;
	msg_node->next = next;
	return msg_node;
}

static inline void msg_node_delete(msg_node_t* msg_node)
{
	msg_delete(msg_node->msg);
	msg_node->next = NULL;
	free(msg_node);
}

// The queue is created with an empty head
static inline msg_queue_t* msg_queue_new()
{
	msg_queue_t* queue = malloc(sizeof(msg_queue_t));
	if (queue == NULL) {
		fprintf(stderr, "Error: queue alloc failed.\n");
		return NULL;
	}

	queue->size = 0;
	queue->head = msg_node_new(NULL, NULL);
	if (queue->head == NULL) {
		return NULL;
	}
	queue->tail = queue->head;

	if (pthread_mutex_init(&(queue->lock), NULL) != 0) {
		fprintf(stderr, "Error: mutex init failed.\n");
		return NULL;
	}
	return queue;
}

static inline void msg_queue_delete(msg_queue_t* queue)
{
	msg_node_t* msg_node;
	while (queue->head->next != NULL) {
		msg_node = queue->head->next;
		queue->head->next = msg_node->next;
		msg_node_delete(msg_node);
		msg_node = NULL;
	}
	pthread_mutex_destroy(&(queue->lock));
	SAFE_FREE(queue->head);
	SAFE_FREE(queue);
}

static inline void msg_queue_push(msg_queue_t* queue, msg_t* msg)
{
	pthread_mutex_lock(&queue->lock);
	queue->size += 1;
	msg_node_t* node = msg_node_new(msg, NULL);
	queue->tail->next = node;
	queue->tail = node;
	pthread_mutex_unlock(&queue->lock);
}

static inline msg_node_t* msg_queue_pop(msg_queue_t* queue)
{
	if (queue->size == 0 || queue->head->next == NULL) {
		return NULL;
	}

	pthread_mutex_lock(&queue->lock);
	queue->size -= 1;
	msg_node_t* msg_node = queue->head->next;
	queue->head->next = msg_node->next;
	// TODO: msg_node_delete
	pthread_mutex_unlock(&queue->lock);

	return msg_node;
}

static inline void msg_queue_debug(msg_queue_t* queue)
{
	if (queue->size == 0) {
		printf("The queue is empty!");
	}

	pthread_mutex_lock(&queue->lock);
	printf("Queue: ");
	msg_node_t* node = queue->head->next;
	while (node != NULL) {
		printf("%d ", node->msg->value);
		node = node->next;
	}
	printf("(size: %ld)\n", queue->size);
	pthread_mutex_unlock(&queue->lock);
}



#endif // $ifndef QUEUE_H
