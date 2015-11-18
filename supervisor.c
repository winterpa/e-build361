#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <semaphore.h>
#include "message.h"
#include "shmem-ex.h"

struct pro_aggreg{
	int num_items ; /* Items made during iteration */
	int iteration ; /* Current iteration */
} ;

struct pro_aggreg aggregs[n];


int main ( int argc , char * argv[] )
{


	/* Initialize the shared memory */
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
	}
	p = (shared_data *) shmat( shmid , NULL , 0 );
	if ( p == (shared_data *) -1 ) {
	   printf ("\nFailed to attach shared memory id=%d\n" , shmid );
	   exit(-1) ;
	}*/

	int LinesActive = atoi(argv[1]);

	msgBuf msg ;
	key_t msgQueKey ;
	int queID ;
	int msgStatus ;
	int result ;
	int i = 0;

	for(i = 0; i < ActiveLines; i++)
	{
		aggregs[i].num_items = msg.info.num_items;
		aggregs[i].iteration = msg.info.iteration;
	}
	

	/* Create / Find the message queues */
	msgQueKey = BASE_MAILBOX_NAME ;
	queID = msgget( msgQueKey , IPC_CREAT | 0600 ) ; /*rw. ... ...*/
	
	/* Now, wait for a message to arrive from the User process */

	sem_wait(&print);

	while (LinesActive > 0)
	{
		msgStatus = msgrcv( queID , &msg , MSG_INFO_SIZE , 1 , 0 );
		
		if ( msg.info.type == 1 )
		{
			//update production aggregates (num-items-built, num-iterations)
			aggregs[msg.info.sender].num_items += msg.info.num_items;
			aggregs[msg.info.sender].iteration++;
		}
		else if ( msg.info.type == 2 )
		{
			LinesActive --;
		}
		else
		{
			//discard this unsupported message
		}
	}

	sem_post(&sema);

	sem_wait(&print);

	//Print production aggregates
	for(i = 0; i < ActiveLines; i++)
	{
		printf("Number of Items: %d\n", aggregs[i].num_items);
		printf("Number of iterations: %d\n", aggregs[i].iteration);
	} 

	sem_post(&print);
	

	return 0 ;
}

/*--------------------------------------------------------------------
Print a message buffer
----------------------------------------------------------------------*/
/*void printMsg( msgBuf *m )
{
printf( "{ type=%ld , { sender pid=%ld, %3d %c %3d , result=%6d } }\n"
	, m->mtype, (long) m->info.sender
	, m->info.num_items, m->info.iteration) ;
}*/
