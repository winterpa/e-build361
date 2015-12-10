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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <sys/uio.h>

#define SERVERPORT "4950"    // the port users will be connecting to

int main(int argc, char *argv[])
{
    int sockfd;
    struct addrinfo addr, *servinfo, *p;
    int rv;
    int numbytes;
	int iterations = 0;
	msgBuf message;
    socklen_t addr_len;
    struct sockaddr_storage their_addr;

    
    struct timespec ts;
	ts.tv_sec = 0;
    ts.tv_nsec = duration * 1000000;

    memset(&addr, 0, sizeof addr);
    addr.ai_family = AF_UNSPEC;
    addr.ai_socktype = SOCK_DGRAM;
    
	bool flag = true;
	
	message.mtype = 01
	
	
    
    //start new here
    /*sockfd = socket(p->ai_family, p->ai_socktype,p->ai_protocol);
    bind(fd,p->ai_addr,p->ai_addrlen);*/

    if ((rv = getaddrinfo(argv[1], SERVERPORT, &addr, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and make a socket
    if ((sockfd = socket(p->ai_family, p->ai_socktype,
        p->ai_protocol)) == -1)
    {
        perror("UDPclient: socket");
        continue;
    }


    if (p == NULL) {
        fprintf(stderr, "UDPclient: failed to create socket\n");
        return 2;
    }

    if (bind(fd,p->ai_addr,p->ai_addrlen)==-1)
	{
        close(sockfd);
        perror("UDPserver: bind");
        continue;
    }
	
	sendto(sockfd, argv[2], strlen(argv[2]), 0, p->ai_addr, p->ai_addrlen)) == -1);
	
    recvfrom(sockfd, &message, MSG_SIZE, 0, p->ai_addr/*THIS NEEDS TO BE STRUCT SOCKADDR* FROM*/, p->ai_addrlen)) == -1);
	
	if (message.mtype == 11)
	{
		int factory_id = message.info.id;
		int capacity = message.info.num_items;
		int duration = message.info.iteration;
		int order_size; 
		
		message.mtype = 01;
	}
	while (flag)
	{
		recvfrom(sockfd, &message, MSG_SIZE, 0, p->ai_addr/*THIS NEEDS TO BE STRUCT SOCKADDR* FROM*/, p->ai_addrlen)) == -1);
	
		if (message.mtype == 12)
		{
			nanosleep(&ts, NULL);
			//printf("Factory Line %d -- MAKING STUFF\n", factory_id);
			if(p->order_size > 0)
			{
				p->order_size -= capacity;
				//printf("order_size is now %d\n", p->order_size);
				
			}
			msg.mtype = 02;
			//sendto(sockfd, argv[2], strlen(argv[2]), 0, p->ai_addr, p->ai_addrlen)) == -1);
		}
		else if (message.mtype == 13)
		{
			printf("Number of iterations: %d\n Items produced: %d\n, Total duration: %d\n",
				iterations, capacity /*this isnt correct*/, (iterations * duration));
			
			msg.mtype = 03;
			flag = false;
		}
		iterations++;
		msgsnd( queID , &msg , MSG_INFO_SIZE , 0);
	}

    sendto(sockfd, argv[2], strlen(argv[2]), 0, p->ai_addr, p->ai_addrlen)) == -1);
   
    freeaddrinfo(servinfo);

    return 0;
}

#endif