#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include "message.h"
#include "shmem-ex.h"

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

	int num_lines = atoi(argv[1]);

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

	/* Now, wait for a message to arrive from the User process */
	printf ("\nI am now waiting to receive request ...\n" );
	msgStatus = msgrcv( queID , &msg , MSG_INFO_SIZE , 1 , 0 );
	if ( msgStatus < 0 )
	{
		printf("Failed to receive message from User process on queuID %d. Error code=%d\n", queID , errno ) ;
		exit(-2) ;
	}
	else
	{
		printf("Calculator received the following message from the User:\n" );
		printMsg( & msg );
		printf("\n");
	}

	/* prepare the result to send back to the User process */	
	msg.info.type

	msg.info.sender = getpid() ;

	/* Send the result message to the User process */
	msgStatus = msgsnd( queID , &msg , MSG_INFO_SIZE , 0 ) ; /* the msg flag is set to 0 */
	if ( msgStatus < 0 )
	{
		printf("Failed to send message to User process on queuID %d. Error code=%d\n", queID , errno ) ;
		exit(-2) ;
	}
	else
	{
		printf("Calculator sent the following message to the User:\n" );
		printMsg( & msg );
		printf("\n" );
	}

	printf("\n" );

	return 0 ;
}

/*--------------------------------------------------------------------
Print a message buffer
----------------------------------------------------------------------*/
void printMsg( msgBuf *m )
{
printf( "{ type=%ld , { sender pid=%ld, %3d %c %3d , result=%6d } }\n"
	, m->mtype, (long) m->info.sender
	, m->info.num_items, m->info.iteration) ;
}
