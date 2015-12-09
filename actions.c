#ifndef actions_c
#define actions_c

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "actions.h"
#include "shmem-ex.h"
#include "message.h"

#define MYPORT "5445"

struct pro_aggreg{
	int num_items; /* Items made during iteration */
	int iteration; /* Current iteration */
};

void get_payment_method()
{
        printf("Please enter a payment method.\n");
}

void dispatch_factory_lines()
{
    char s[INET6_ADDRSTRLEN];
    int i;
    int rv;
	int linesActive;
    int numbytes;
	int sockfd;
    msgBuf message;
    socklen_t addr_len;
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr;
    uint32_t clientID;
    uint32_t order_size;

    struct pro_aggreg aggregs[5];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) 
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    }

    for(p = servinfo; p != NULL; p = p->ai_next) 
    {
        printf("in loop \n");
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) 
        {
            perror("UDPserver: socket");
            continue;
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) 
        {
            close(sockfd);
            perror("UDPserver: bind");
            continue;
        }

        break;
    }

    if (p == NULL) 
    {
        fprintf(stderr, "UDPserver: failed to bind socket\n");
    }

    /* Set default values */
	for(i = 0; i < 5; i++)
	{
		aggregs[i].num_items = 0;
		aggregs[i].iteration = 0;
	}

    srandom(time(NULL));

	order_size = random() % 40001 + 10000;

	addr_len = sizeof their_addr;

	clientID = 1;
	linesActive = 5;

	while (linesActive > 0)
	{
		recvfrom(sockfd, &message, MSG_SIZE , 0, (struct sockaddr *)&their_addr, &addr_len);

		if (message.mtype == 01)
		{
			message.mtype = 11;
			message.info.id = clientID;
			message.info.num_items = random() % 41 + 10; /* capacity for that client */
			message.info.iteration = random() % 5 + 1; /* duration for that client */
			clientID++;
		}
		if (message.mtype == 02)
		{
			if(order_size == 0)
			{
				message.mtype = 13; /* Stop the client from running anymore */
				linesActive--;
			}
			else 
			{
				message.mtype = 12; /* Let the client run */
				if(message.info.num_items > order_size) /* If it shouldn't make it's capacity */
				{
					message.info.num_items = order_size;
				}
				order_size -= message.info.num_items;
			}
		}
		if (message.mtype == 03)
		{
			aggregs[message.info.id].num_items += message.info.num_items;
			aggregs[message.info.id].iteration = message.info.iteration;
		}
		/* Send the message */
		sendto(sockfd, (const void *)&message, MSG_SIZE, 0, (const struct sockaddr*)&their_addr, addr_len); 
    }
}

void shut_down_factory_lines()
{

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
