#ifndef accepting_c
#define accepting_c

#include "accepting.h"
#include "actions.h"
#include "statemodel.h" //For the other states

// Create the object of the opening state.
state_t accepted = {
	default_event_handler, //order_received
	default_event_handler, //valid_payment
	default_event_handler, //invalid_payment
	default_event_handler, //failed_manf
	default_event_handler, //pass_manf
	default_event_handler, //delivery_confirmed
	default_event_handler, //not_delivered
	entry_to,
	exit_from
};

state_t* order_rcvd()
{
	attempts = 0;
	return &processing;
}
static state_t* order_rcvd();


#end
