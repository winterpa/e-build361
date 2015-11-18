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
#include <stdbool.h>

#include "message.h"
#include "shmem-ex.h"

int
main(int argc, char ** argv)
{	
	int factory_id = atoi(argv[1]);
	int capacity = atoi(argv[2]);
	int duration = atoi(argv[3]);
	int iterations = 0;
	bool flag = true;

	int shmid ;
   	key_t shmkey;
   	int shmflg ;
   	shared_data *p;

	shmkey = SHMEM_KEY ;
	shmflg = IPC_CREAT | S_IRUSR | S_IWUSR ;

	shmid = shmget( shmkey , SHMEM_SIZE , shmflg ) ;

	p = (shared_data *) shmat( shmid , NULL , 0 );

	struct timespec ts;
	ts.tv_sec = 0;
    ts.tv_nsec = duration * 1000000;

	msgBuf msg ;
	key_t msgQueKey ;
	int queID ;

	/* Create / Find the message queues */
	msgQueKey = BASE_MAILBOX_NAME ;
	queID = msgget( msgQueKey , IPC_CREAT | 0600 ) ; /*rw. ... ...*/

	while (flag)
	{
		nanosleep(&ts, NULL);
		sem_wait(&(p->factory_sema));
		//printf("Factory Line %d -- MAKING STUFF\n", factory_id);
		if(p->order_size > 0)
		{
			p->order_size -= capacity;
			//printf("order_size is now %d\n", p->order_size);
			msg.mtype = 1;
		}
		else
		{
			msg.mtype = 2;
			flag = false;
		}
		sem_post(&p->factory_sema);
		iterations++;
		msg.info.sender = factory_id;
		msg.info.num_items = capacity;
		msg.info.iteration = iterations;
		msgsnd( queID , &msg , MSG_INFO_SIZE , 0);
	}

	shmdt(p);
}

#endif