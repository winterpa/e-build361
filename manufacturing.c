#ifndef manufacturing_c
#define manufacturing_c

#include "manufacturing.h"
#include "actions.h"
#include "statemodel.h" // For the other states

// Create the object of the closing state.
state_t manufacturing = {
	default_event_handler, //order_received
	valid_payment, //valid_payment
	default_event_handler, //invalid_payment
	default_event_handler, //failed_manf
	pass_manf, //pass_manf
	default_event_handler, //delivery_confirmed
	default_event_handler, //not_delivered
	entry_to,
	exit_from
};

state_t* pass_manf()
{
	set_motor( MOTOR_OFF );
	return &closed;
}

state_t* valid_payment()
{
	return &opening;
}

void entry_to()
{
	
}

void exit_from()
{
	shut_down_factory_lines();
}

#endif
