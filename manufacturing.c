#ifndef manufacturing_c
#define manufacturing_c

#include "manufacturing.h"
#include "hardware.h"
#include "statemodel.h" // For the other states

// Create the object of the closing state.
state_t manufacturing = {
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

state_t* closed_detected()
{
	set_motor( MOTOR_OFF );
	return &closed;
}

state_t* open_button_pressed()
{
	return &opening;
}

void entry_to()
{
	set_motor( MOTOR_CLOSING );
}

#endif
