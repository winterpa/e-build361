#ifndef statemodel_c
#define statemodel_c

#include <stdlib.h>

#include "statemodel.h"

//Define the initial state.
static state_t* current_state = &accepting;

void handle_event( event current_event)
{
	state_t* next_state;

	next_state = NULL;
	switch(current_event) //exit current_state and have the appropriate effect
	{
		case ORDER_RECEIVED:
			next_state = current_state->order_received();
			break;
		case VALID_PAYMENT:
			next_state = current_state->valid_payment();
			break;
		case REJECT_PAYMENT:
			next_state = current_state->reject_payment();
			break;
		case FAILED_MANF:
			next_state = current_state->failed_manf();
			break;
		case PASS_MANF:
			next_state = current_state->pass_manf();
			break;
		case DELIVERY_CONFIRMED:
			next_state = current_state->delivery_confirmed();
			break;
		case NOT_DELIVERED:
			next_state = current_state->not_delivered();
			break;
	}

	if (next_state != NULL)
	{
		current_state = next_state;	// Changes states
		current_state->entry_to();	// enter the new state
	}
}

#endif