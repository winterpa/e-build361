#ifndef processing_c
#define processing_c

#include "processing.h"
#include "actions.h"
#include "statemodel.h" //For the other states

// Create the object of the opening state.
state_t processing = {
	default_event_handler, //order_received
	valid_payment, //valid_payment
	invalid_payment, //invalid_payment
	default_event_handler, //failed_manf
	default_event_handler, //pass_manf
	default_event_handler, //delivery_confirmed
	default_event_handler, //not_delivered
	entry_to,
	deafult_action
};

state_t* valid_payment()
{
  return &manufacturing;
}

state_t* invalid_payment()
{
  
}

void entry_to()
{
  get_payment_method();
}
#endif
