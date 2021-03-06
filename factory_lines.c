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

#define SERVERPORT "5785"    // the port users will be connecting to

int main(int argc, char *argv[])
{
  msgBuf message;
  int rv;
  int sockfd;
  struct addrinfo addr, *servinfo, *p;

	int iterations = 0;
	uint32_t items_made = 0;
  bool flag = true;

  memset(&addr, 0, sizeof addr);
  addr.ai_family = AF_UNSPEC;
  addr.ai_socktype = SOCK_DGRAM;

  //Get server info
  if ((rv = getaddrinfo(argv[1], SERVERPORT, &addr, &servinfo)) != 0)
  {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
  }

    // loop through all the results and make a socket
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("UDPclient: socket");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "UDPclient: failed to create socket\n");
        return 2;
    }

  //Set and send message to server telling it that it is ready
  message.mtype = 01;
	message.info.isConnected = 0;

	sendto(sockfd, (const void *) &message, MSG_SIZE, 0, p->ai_addr, p->ai_addrlen);

  //Receive message to start making items
  recvfrom(sockfd, (void *) &message, MSG_SIZE, 0, (struct sockaddr *)p->ai_addr, &p->ai_addrlen);

  //Sets the information received from the server to local variables
	uint32_t factory_id = message.info.id;
	uint32_t capacity = message.info.num_items;
	uint32_t duration = message.info.iteration;
	uint32_t isConnected = message.info.isConnected;
		
  struct timespec ts;
	ts.tv_sec = duration / 1000;
  ts.tv_nsec = (duration % 1000) * 1000;

  //Continues to loop and make items until the message to finish is received
	while (flag)
	{
		message.info.isConnected = isConnected;
		message.mtype = 02;
    sendto(sockfd, (const void *) &message, MSG_SIZE, 0, p->ai_addr, p->ai_addrlen);
		recvfrom(sockfd, (void *) &message, MSG_SIZE, 0, (struct sockaddr *)p->ai_addr, &p->ai_addrlen);

		message = (msgBuf)message;

    //Makes capacity or amount left to make and adds it to the current items made for that client
		if (message.mtype == 12)
		{
			if(message.info.num_items != capacity)
				items_made += message.info.num_items;
			else
				items_made += capacity;
			iterations++;

      //Sends message to server that all items have been made
			message.mtype = 03;
			message.info.iteration = iterations;
			sendto(sockfd, (const void *) &message, MSG_SIZE, 0, p->ai_addr, p->ai_addrlen);
			nanosleep(&ts, NULL);
		}
		
		//Breaks while loop and prints data for current client
		if (message.mtype == 13)
		{
			printf("Number of iterations: %d\nItems produced: %d\nTotal duration: %d\n",
		  iterations, items_made, (iterations * duration));
			
			flag = false;
		}
	}

	printf("Line %d has completed its portion of the order.\n", factory_id);
  freeaddrinfo(servinfo);

  return 0;
}

#endif
