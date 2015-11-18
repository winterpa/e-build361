#ifndef actions_c
#define actions_c

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <assert.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#include "actions.h"
#include "shmem-ex.h"
#include "message.h"

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

	/*if ( shmid != -1 ) {
	   printf("\nShared memory segment '0x%X' %s" , shmkey  ,
		  "successfully created/found with id=%d\n" , shmid ) ;
	}
	else {
	   printf("\nFailed to create/find shared memory '0x%X'.\n", shmkey );
	   perror("Reason: ");
	   exit(-1) ;    
	}*/
	p = (shared_data *) shmat( shmid , NULL , 0 );
	/*if ( p == (shared_data *) -1 ) {
	   printf ("\nFailed to attach shared memory id=%d\n" , shmid );
	   exit(-1) ;
	}*/

	msgBuf msg ;
	key_t msgQueKey ;
	int queID ;

	/* Create / Find the message queues */
	msgQueKey = BASE_MAILBOX_NAME ;
	queID = msgget( msgQueKey , IPC_CREAT | 0600 ) ; /*rw. ... ...*/

	printf("Factory lines dispatched.\n");

	sem_init(&p->super_sema, 1, 0);
	sem_init(&p->factory_sema, 1, 0);
	sem_init(&p->print_sema, 1, 0);

	srandom(time(NULL));

	p->order_size = random() % 1001 + 1000;

	int ii;
	int capacity;
	int duration;
	char* argv0 = "factory_lines";
	char argv1[5];
	char argv2[5];
	char argv3[5];
	pid_t childID;

pid_t superID = fork();
if (superID == 0)
		if(execlp("gnome-terminal", "SuperVterm", "-x", "/bin/bash", "-c", "./supervisor 5", NULL) < 0)
		{
			perror("execlp Supervisor Failed");
			exit(-1);
		}
	for(ii = 0; ii < 5; ii++)
	{
		capacity = random() % 41 + 10;
		duration = random() % 5 + 1;
		childID = fork();
		if(childID == 0)
		{
			snprintf(argv1, 5, "%d", ii);
			snprintf(argv2, 5, "%d", capacity);
			snprintf(argv3, 5, "%d", duration);
			printf("Dispatched line %d with capacity-%d and duration-%d\n", ii, capacity, duration);
			execl("./factory_lines", argv0, argv1, argv2, argv3, (char * )NULL);
		}
	}

	
	

	printf("Waiting for supervisor to signal\n");
	sem_post(&(p->factory_sema));
	sem_wait(&(p->super_sema));
	


}

void shut_down_factory_lines()
{
	int shmid ;
   	key_t shmkey;
   	int shmflg ;
   	shared_data *p;

	shmkey = SHMEM_KEY ;
	shmflg = IPC_CREAT | S_IRUSR | S_IWUSR ;

	shmid = shmget( shmkey , SHMEM_SIZE , shmflg ) ;

	/*if ( shmid != -1 ) {
	   printf("\nShared memory segment '0x%X' %s" , shmkey  ,
		  "successfully created/found with id=%d\n" , shmid ) ;
	}
	else {
	   printf("\nFailed to create/find shared memory '0x%X'.\n", shmkey );
	   perror("Reason: ");
	   exit(-1) ;    
	}*/
	p = (shared_data *) shmat( shmid , NULL , 0 );
	/*if ( p == (shared_data *) -1 ) {
	   printf ("\nFailed to attach shared memory id=%d\n" , shmid );
	   exit(-1) ;
	}*/

	msgBuf msg ;
	key_t msgQueKey ;
	int queID ;

	/* Create / Find the message queues */
	msgQueKey = BASE_MAILBOX_NAME ;
	queID = msgget( msgQueKey , IPC_CREAT | 0600 ) ; /*rw. ... ...*/

	sem_post(&(p->print_sema));

	sem_wait(&(p->super_sema));

	shmdt(p);
	shmctl( shmid , IPC_RMID , NULL );
	msgctl( queID, IPC_RMID, NULL);
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
