#ifndef factorylines_c
#define factorylines_c

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

#include "message.h"
#include "shmem-ex.h"

int
main(int argc, char ** argv)
{	
	int factory_id = atoi(argv[1]);
	int capacity = atoi(argv[2]);
	int duration = atoi(argv[3]);
	int items_made = 0;
	int iterations = 0;

	int shmid ;
   	key_t shmkey;
   	int shmflg ;
   	shared_data *p;

	shmkey = SHMEM_KEY ;
	shmflg = IPC_CREAT | S_IRUSR | S_IWUSR ;

	shmid = shmget( shmkey , SHMEM_SIZE , shmflg ) ;

	p = (shared_data *) shmat( shmid , NULL , 0 );

	msgBuf msg ;
	key_t msgQueKey ;
	int queID ;
	int msgStatus ;
	int result ;

	/* Create / Find the message queues */
	msgQueKey = BASE_MAILBOX_NAME ;
	queID = msgget( msgQueKey , IPC_CREAT | 0600 ) ; /*rw. ... ...*/

	while (1)
	{
		sleep(duration);
		sem_wait(&p->factory_sema);
		if(p->order_size > 0)
		{
			p->order_size -= capacity;
			msg.mtype = 1;
		}
		else
		{
			msg.mtype = 2;
			break;
		}
		items_made += capacity;
		iterations++;
		msg.info.sender = factory_id;
		msg.info.num_items = items_made;
		msg.info.iteration = iterations;
		sem_post(&p->factory_sema);
		msgsnd( queID , &msg , MSG_INFO_SIZE , 0 );
	}
}

#endif