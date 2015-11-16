#ifndef factorylines_c
#define factorylines_c

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>
#include <semaphore.h>
#include <pthread.h>

#include "actions.h"
#include "message.h"

int
main(int argc, char ** argv)
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

	msgBuf msg ;
	key_t msgQueKey ;
	int queID ;
	int msgStatus ;
	int result ;

	/* Create / Find the message queues */
	msgQueKey = BASE_MAILBOX_NAME ;
	queID = msgget( msgQueKey , IPC_CREAT | 0600 ) ; /*rw. ... ...*/
	if ( queID < 0 ) {
		printf("Failed to create mailbox %X. Error code=%d\n", msgQueKey , errno ) ;
		exit(-2) ;
	}
	else
	printf( "The Calculator process created/found mailbox %X with qid=%d\n", msgQueKey , queID ) ;

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
	sem_wait(&print);
	printf("Line [%d]: \n\tItems Made: %d \n\tIterations: %d\n",
		  t_args.thread_id, total_made, count);
	fflush(NULL);
	sem_post(&print);
}

#endif