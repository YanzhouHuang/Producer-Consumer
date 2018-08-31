

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define BUFFER_SIZE 10	//storage buffer size
#define MAX 500			//max number need count
#define NUM_PRODUCERS 5	//producer threads
#define NUM_CONSUMERS 4	//consumer threads

//binary 
#define true 1
#define false 0

int n = 0;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;
sem_t empty, full, mutex;


int main(char argc, char* argv) {

	//initialize semaphores
	sem_init(&empty, 0, BUFFER_SIZE);
	sem_init(&full, 0, 0);
	sem_init(&mutex, 0, 1);

	//loop counter for non-C99 mode
	int i;

	//producer thread creation


void *producer(void *arg) {
	int isMax = false;

	do {
		sem_wait(&empty);
		sem_wait(&mutex);
		// critical section
		if (n <= MAX) {
			buffer[in] = n;
			n++;
			in = (in + 1) % BUFFER_SIZE;
		} else {
			isMax = true;
		}
		sem_post(&mutex);
		sem_post(&full);
	} while (!isMax);
}

void *consumer(void *arg) {
	int isMax = false;

	do {
		sem_wait(&full);
		sem_wait(&mutex);
		// critical section
		int o = buffer[out];
		if (o < MAX) {
			out = (out + 1) % BUFFER_SIZE;
		} else {
			isMax = true;
		}
		sem_post(&mutex);
		sem_post(&empty);

		// consume the item
		printf("%i, ", o);

	} while (!isMax);
}
	pthread_t t_producer[NUM_PRODUCERS];
	for (i = 0; i < NUM_PRODUCERS; i++) {
		long t_p;
		int r_p = pthread_create(&t_producer[i], NULL, producer, (void *)t_p);
		if (r_p) {
			printf("ERROR in pthread creation: %d\n", r_p);
			return(-1);
		}
	}

	//consumer thread creation
	pthread_t t_consumer[NUM_CONSUMERS];
	for (i = 0; i < NUM_CONSUMERS; i++) {
		long t_c;
		int r_c = pthread_create(&t_consumer[i], NULL, consumer, (void *)t_c);
		if (r_c) {
			printf("ERROR in pthread creation: %d\n", r_c);
			return(-1);
		}
	}

	//join all threads
	for (i = 0; i < NUM_PRODUCERS; i++) {
		pthread_join(t_producer[i], NULL);
	}
	for (i = 0; i < NUM_CONSUMERS; i++) {
		pthread_join(t_consumer[i], NULL);
	}

	//print all staff
	printf("\n");

	return 0;
}