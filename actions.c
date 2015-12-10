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

#define MYPORT "5785"

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
    int i; /* for loop control */
    int rv; 
	int linesActive; /* The amount of lines currently active */
	int linesWorking; /* The amount of lines currently working */
	int sockfd; /* The socket number */
    msgBuf message; /* The data structure to contain the data */
    socklen_t addr_len;
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr;
    uint32_t clientID; /* The ID of the client */
    uint32_t order_size; /* The amount of items going to be made */

    struct pro_aggreg aggregs[5]; /* The array to hold the aggregate data */

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    /* Get the client info and bind the socket*/
    if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) 
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    }

    for(p = servinfo; p != NULL; p = p->ai_next) 
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) 
        {
            perror("Server: socket");
            continue;
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) 
        {
            close(sockfd);
            perror("Server: bind");
            continue;
        }
        break;
    }

    if (p == NULL) 
    {
        fprintf(stderr, "Server: failed to bind socket\n");
    }

    /* Set default values for the aggregate data*/
	for(i = 0; i < 5; i++)
	{
		aggregs[i].num_items = 0;
		aggregs[i].iteration = 0;
	}

	/* Seed the random number generator */
    srandom(time(NULL));

    /* Create the order size */
	order_size = random() % 10001 + 10000;

	addr_len = sizeof their_addr;

	/* Initialize looping variables and client IDs */
	clientID = 1;
	linesActive = 0;
	linesWorking = 0;
	
	/* Loop to set up client connections and hold until all 5 are set up */
	while (linesActive < 5)
	{
		/* Recieve a message from the client asking for it's information */
		recvfrom(sockfd, &message, MSG_SIZE , 0, (struct sockaddr *)&their_addr, &addr_len);

		/* Cast the message */
		message = (msgBuf)message;

		/* If this is a client message asking for info and it hasn't been set up before... */
		if (message.mtype == 01 && message.info.isConnected == 0)
		{
			message.mtype = 11; /* Set the message type */
			message.info.id = clientID; /* Give the client it's ID */
			message.info.num_items = random() % 501 + 10; /* capacity for that client */
			message.info.iteration = random() % 1001 + 1000; /* duration for that client */
			message.info.isConnected = 1; /* Don't register this client again */
			clientID++; /* Set it up for the next client */
			printf("[Server]: Sending client (%d) capacity of %d and duration of %dms.\n", 
				message.info.id, message.info.num_items, message.info.iteration);
			linesActive++; /* Increment the amount of lines active and ready to work */
		}
		else
			message.mtype == 14; /* Dummy message (used for busy waiting) */

		/* Send a message to the client */
		sendto(sockfd, (const void *)&message, MSG_SIZE, 0, (const struct sockaddr*)&their_addr, addr_len); 
	}

	/* While there are active clients or clients making items */
	while (linesActive > 0 || linesWorking > 0)
	{
		/* Receive a message from the client */
		recvfrom(sockfd, &message, MSG_SIZE , 0, (struct sockaddr *)&their_addr, &addr_len);

		/* Cast the message */
		message = (msgBuf)message;

		if (message.mtype == 02) /* Client wants to make stuff */
		{
			if(order_size == 0) /* Can't make any more stuff */
			{
				message.mtype = 13; /* Stop the client from running anymore */
				linesActive--;
			}
			else 
			{
				message.mtype = 12; /* Let the client run */
				if(message.info.num_items > order_size) /* If it shouldn't make it's capacity */
				{
					message.info.num_items = order_size; /* Only make this much */
				}
				order_size -= message.info.num_items; /* Decrement the amount of items being made */
				linesWorking++; /* Let the loop know someone is making stuff */
			}
		}
		if (message.mtype == 03) /* Line finished making stuff */
		{
			/* Update the aggregate data */
			aggregs[message.info.id-1].num_items += message.info.num_items; 
			aggregs[message.info.id-1].iteration = message.info.iteration;

			linesWorking--; /* Decrement the counting variable */
		}

		/* Send the message */
		sendto(sockfd, (const void *)&message, MSG_SIZE, 0, (const struct sockaddr*)&their_addr, addr_len); 
    }

    /* Print the aggregate data */
    for(i = 0; i < 5; i++)
	{
		printf("[%d] - Number of Items: %d\n", i + 1, aggregs[i].num_items);
		printf("[%d] - Number of Iterations: %d\n", i + 1, aggregs[i].iteration);
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