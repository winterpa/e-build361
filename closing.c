#ifndef closing_c
#define closing_c

#include "closing.h"
#include "hardware.h"
#include "statemodel.h" // For the other states

// Create the object of the closing state.
state_t closing = {
	default_event_handler,
	closed_detected,
	open_button_pressed,
	default_event_handler,
	entry_to,
	default_action,
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
