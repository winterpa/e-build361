#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <semaphore.h>
#include "message.h"
#include "shmem-ex.h"

struct pro_aggreg{
	int num_items; /* Items made during iteration */
	int iteration; /* Current iteration */
};

int main ( int argc , char * argv[] )
{
	printf("SUPERVISOR\n");
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
	}*/
	p = (shared_data *) shmat( shmid , NULL , 0 );
	/*if ( p == (shared_data *) -1 ) {
	   printf ("\nFailed to attach shared memory id=%d\n" , shmid );
	   exit(-1) ;
	}*/

	int totalLines = atoi(argv[1]);

	struct pro_aggreg aggregs[totalLines];

	int i = 0;
	/* Set default values */
	for(i = 0; i < totalLines; i++)
	{
		aggregs[i].num_items = 0;
		aggregs[i].iteration = 0;
	}

	msgBuf msg ;
	key_t msgQueKey ;
	int queID ;
	int msgStatus ;
	int result ;
	i = 0;	

	/* Create / Find the message queues */
	msgQueKey = BASE_MAILBOX_NAME ;
	queID = msgget( msgQueKey , IPC_CREAT | 0600 ) ; /*rw. ... ...*/
	
	/* Now, wait for a message to arrive from the User process */

	int LinesActive = totalLines;
	while (LinesActive > 0)
	{
		msgStatus = msgrcv( queID , &msg , MSG_INFO_SIZE , 0 , 0 );
		
		if ( msg.mtype == 1 )
		{
			//update production aggregates (num-items-built, num-iterations)
			aggregs[msg.info.sender].num_items += msg.info.num_items;
			aggregs[msg.info.sender].iteration++;
		}
		else if ( msg.mtype == 2 )
		{
			LinesActive--;
		}
		else
		{
			//do nothing
		}
	}

	sem_post(&p->super_sema);

	sem_wait(&p->print_sema);

	//Print production aggregates
	for(i = 0; i < totalLines; i++)
	{
		printf("Number of Items: %d\n", aggregs[i].num_items);
		printf("Number of iterations: %d\n", aggregs[i].iteration);
	}	

	sem_post(&p->super_sema);
	shmdt(p);

	return 0 ;
}