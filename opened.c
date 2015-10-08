#ifndef opened_c
#define opened_c

#include "opened.h"
#include "hardware.h"
#include "statemodel.h" //For the other states

// Create the object of the opening state.
state_t opened = {
	close_button_pressed,
	default_event_handler,
	default_event_handler,
	default_event_handler,
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
