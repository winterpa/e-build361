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
        printf("Please enter a payment method.\n");
}

void dispatch_factory_lines()
{
	int shmid ;
   	key_t shmkey;
   	int shmflg ;
   	shared_data *p;

	shmkey = SHMEM_KEY ;
	shmflg = IPC_CREAT | S_IRUSR | S_IWUSR ;

	shmid = shmget( shmkey , SHMEM_SIZE , shmflg ) ;

	if ( shmid != -1 ) {
	   printf("\nShared memory segment '0x%X' %s" , shmkey  ,
		  "successfully created/found with id=%d\n" , shmid ) ;
	}
	else {
	   printf("\nFailed to create/find shared memory '0x%X'.\n", shmkey );
	   perror("Reason: ");
	   exit(-1) ;    
	}
	p = (shared_data *) shmat( shmid , NULL , 0 );
	if ( p == (shared_data *) -1 ) {
	   printf ("\nFailed to attach shared memory id=%d\n" , shmid );
	   exit(-1) ;
	}

	printf("Factory lines dispatched.\n");

	sema_init(&p->super_sema, 0, 1);
	sema_init(&p->factory_sema, 0, 1);

	pid_t superID = fork();
	if (superID == 0)
		if(execlp("gnome-terminal", "SuperVterm", "-x", "bin/bash", "-c", "./supervisor 5", NULL) < 0)
		{
			perror("execlp Supervisor Failed");
			exit(-1);
		}

	pid_t factory_line_ID;

	int ii;
	factory_line_ID = fork();
	if()
	if(factory_line_ID == 0)
	{
		int count = 0;
		int total_made = 0;
		thread_args t_args;
		memcpy(&t_args,args,sizeof(thread_args));

		while (p->order_size > 0)
		{
			sem_wait(&sema);
			p->order_size--;
			sem_post(&sema);
			sleep(t_args.duration);

		}
	}
	sem_wait(&print);
	printf("Line [%d]: \n\tItems Made: %d \n\tIterations: %d\n",
		  t_args.thread_id, total_made, count);
	fflush(NULL);
	sem_post(&print);

	printf("Order size: %d\n", order_size);
	int i;

	printf("Items Made: %d\n", cur_order_size);
	
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
