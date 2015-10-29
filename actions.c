#ifndef actions_c
#define actions_c

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>
#include <semaphore.h>
#include <pthread.h>

#include "actions.h"

int cur_order_size;
sem_t sema;
sem_t print;

void get_payment_method()
{
        printf("Payment method received.\n");
}

void dispatch_factory_lines()
{
	printf("Factory lines dispatched.\n");
	/* Seed the random number generator with the current time */
	srand(time(NULL));
	
	uint8_t rc = 0;
	int order_size;
	void* status = NULL;
	thread_args t_args[5];
	sem_init(&sema, 0, 1);
	sem_init(&print, 0, 1);

	/* Assign a random number between 1000 and 2000 (inclusive)*/
	order_size = (rand() % 1001) + 1000;
	cur_order_size = 0;

	pthread_t threads[5];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	printf("Order size: %d\n", order_size);
	int i;
	for(i = 0; i < 5; i++)
	{
	  t_args[i].thread_id = i;
	  /* Assign a random number between 10 and 50 (inclusive) */
	  t_args[i].capacity = (rand() % 41) + 10;
	  t_args[i].duration = (rand() % 5) + 1;
	  t_args[i].order_size = order_size;
	  t_args[i].cur_order_size = &cur_order_size;
	  printf("Manufacturing Line[%d]: \n\tCapacity-%d \n\tDuration-%d\n", i,
		      t_args[i].capacity, t_args[i].duration);

	  rc = pthread_create(&threads[i], &attr, (void *)manufacture, (void *) (&(t_args[i])));
	
	  assert(rc == 0);

	}
	for(i = 0; i < 5; i++)
        {
	  rc = pthread_join (threads[i], &status);
	  assert(rc == 0);
	}

	printf("Items Made: %d\n", cur_order_size);
	
}

void manufacture(void* args)
{
	int count = 0;
	int total_made = 0;
	thread_args t_args;
	memcpy(&t_args,args,sizeof(thread_args));

	while (*(t_args.cur_order_size) < t_args.order_size)
	{
		sleep(t_args.duration);
		sem_wait(&sema);
		if (*(t_args.cur_order_size) + t_args.capacity > t_args.order_size)
		{
			*(t_args.cur_order_size) += (t_args.order_size - *(t_args.cur_order_size));
			total_made+= (t_args.order_size -
				      *(t_args.cur_order_size));
		}
		else
		{
			*(t_args.cur_order_size) += t_args.capacity;
			total_made += t_args.capacity;
		}
		count++;
		sem_post(&sema);
	}
	sem_wait(&print);
	printf("Line [%d]: \n\tItems Made: %d \n\tIterations: %d\n",
		  t_args.thread_id, total_made, count);
	fflush(NULL);
	sem_post(&print);
}

void shut_down_factory_lines()
{
        printf("Factory lines shut down.\n");
}

void get_address()
{
        printf("Address received.\n");
}

void update_stats(stats status)
{
	if (status == DONE)
	{
		printf("Status is now done.\n");	
	}
	else if (status == LOST)
	{
		printf("Status is now lost.\n");
	}
	else if (status == FAIL)
	{
		printf("Status is now fail.\n");
	}
}

void charge_client()
{
	printf("Client is now being charged.\n");
}

void start_warranty()
{
	printf("Warranty has been started.\n");
}

void refund()
{
	printf("Refund has been given.\n");
}
#endif
