#ifndef state_c
#define state_c

#include <stdlib.h>
#include <stdio.h>
#include "state.h"

// Define the default event handler and default action

state_t * default_event_handler()
{
	printf("Not a valid event from the current state\n");
	return NULL;
}

void default_action()
{	
}

#endif
