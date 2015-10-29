#ifndef actions_c
#define actions_c

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include <assert.h>
#include <pthread.h>

#include "actions.h"

int cur_order_size;
sema_t sema;

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
	thread_args t_args;
	t_args = malloc(sizeof(thread_args));
	sema_init(&sema, 0, 1);

	/* Assign a random number between 1000 and 2000 (inclusive)*/
	order_size = (rand() % 1001) + 1000;
	cur_order_size = 0;

	pthread_t threads[5];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	int i;
	for(i = 0; i < 5; i++)
	{
	  /* Assign a random number between 10 and 50 (inclusive) */
	  t_args.capacity = (rand() % 41) + 10;
	  t_args.duration = (rand() % 5) + 1;
	  t_args.order_size = order_size;
	  t_args.cur_order_size = &cur_order_size;

	  rc = pthread_create(&threads[i], &attr, (void *)manufacture, (void *) (&t_args));
	
	  assert(rc == 0);

	}
	
}

void manufacture(void* args)
{
	struct t_args=(thread_args)args;
	sema_wait(&sema);

	while (*(t_args.cur_order_size) < t_args.order_size)
	{
		if (*(t_args.cur_order_size) + t_args.capacity > t_args.order_size)
		{
			*(t_args.cur_order_size) += (t_args.ordersize - *(t_args.cur_order_size));
		}
		else
		{
			*(t_args.cur_order_size) += t_args.capacity;
		}
		sleep(t_args.duration);
	}
	sema_post(&sema);
	
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
