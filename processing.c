#ifndef processing_c
#define processing_c

#include "processing.h"
#include "hardware.h"
#include "statemodel.h" //For the other states

// Create the object of the opening state.
state_t processing = {
	default_event_handler, //received
	default_event_handler, //order_received
	default_event_handler, //manuf_completed
	default_event_handler, //manuf_failed
	default_event_handler, //invalid_payment
	default_event_handler, //valid_payment
	default_event_handler, //lost_package
	entry_to,
	exit_from
};

state_t* open_button_pressed()
{
	exit_from();
	return &opening;
}

void entry_to()
{
	set_closed_indicator( LED_ON );
}

void exit_from()
{
	set_closed_indicator( LED_OFF );
}

#endif
