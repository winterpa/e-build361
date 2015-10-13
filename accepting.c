#ifndef accepting_c
#define accepting_c

#include "accepting.h"
#include "actions.h"
#include "statemodel.h" //For the other states

// Create the object of the opening state.
state_t accepting = {
	order_received, //order_received
	default_event_handler, //valid_payment
	default_event_handler, //invalid_payment
	default_event_handler, //failed_manf
	default_event_handler, //pass_manf
	default_event_handler, //delivery_confirmed
	default_event_handler, //not_delivered
	default_action,
	default_action
};

state_t* order_received()
{
	attempts = 0;
	return &processing;
}


#endif
