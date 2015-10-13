#ifndef actions_c
#define actions_c

#include <stdlib.h>
#include <stdio.h>

#include "actions.h"

void get_payment_method()
{
        printf("Payment method received.\n");
}

void dispatch_factory_lines()
{
	printf("Factory lines dispatched.\n");
}


void shut_down_factory_lines()
{
        printf("Factory lines shut down.\n");
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
