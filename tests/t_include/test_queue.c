#include <pthread.h>
#include <time.h>
#include <stdlib.h>

#include <stdbool.h>
#include "queue.h"

void* pusher_thread(void* arg)
{
	msg_queue_t* queue = (msg_queue_t*) arg;
	srand(time(NULL));
	int random;
	while (true) {
		random = rand();
		msg_queue_push(queue, msg_new(random));
		msg_queue_debug(queue);
		sleep(1);
	}
}

void* popper_thread(void* arg)
{
	msg_queue_t* queue = (msg_queue_t*) arg;
	sleep(4);
	while (true) {
		msg_node_t* node = msg_queue_pop(queue);
		if (node == NULL) {
			sleep(2);
			continue;
		}
		msg_queue_debug(queue);
		sleep(1);
	}
}


int main(void)
{
	msg_queue_t* queue = msg_queue_new();

	pthread_t thread_id[2];
	pthread_create(&thread_id[0], NULL, pusher_thread, queue);
	pthread_create(&thread_id[1], NULL, popper_thread, queue);

	pthread_join(thread_id[0], NULL);
	pthread_join(thread_id[1], NULL);

	return EXIT_SUCCESS;
}

