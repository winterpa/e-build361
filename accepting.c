#ifndef accepted_c
#define accepted_c

#include "accepted.h"
#include "hardware.h"
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

state_t* close_button_pressed()
{
	return &closing;
}

state_t* opened_detected()
{
	set_motor( MOTOR_OFF );
	return &opened;
}

void entry_to()
{
	set_motor( MOTOR_OPENING );
}

#endif
