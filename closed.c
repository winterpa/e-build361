#ifndef closed_c
#define closed_c

#include "closed.h"
#include "hardware.h"
#include "statemodel.h" //For the other states

// Create the object of the opening state.
state_t closed = {
	default_event_handler,
	default_event_handler,
	open_button_pressed,
	default_event_handler,
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
