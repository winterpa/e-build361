#ifndef shipping_c
#define shipping_c

#include "shipping.h"
#include "hardware.h"
#include "statemodel.h" //For the other states

// Create the object of the opening state.
state_t shipping = {
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

state_t* close_button_pressed()
{
	exit_from();
	return &closing;
}

void entry_to()
{
	set_opened_indicator( LED_ON );
}

void exit_from()
{
	set_opened_indicator( LED_OFF );
}

#endif
