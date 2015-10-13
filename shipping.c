#ifndef shipping_c
#define shipping_c

#include "shipping.h"
#include "actions.h"
#include "statemodel.h" //For the other states

// Create the object of the opening state.
state_t shipping = {
	default_event_handler, //order_received
	default_event_handler, //valid_payment
	default_event_handler, //invalid_payment
	default_event_handler, //failed_manf
	default_event_handler, //pass_manf
	delivery_confirmed, //delivery_confirmed
	not_delivered, //not_delivered
	entry_to,
	default_action
};

state_t* delivery_confirmed()
{
  start_warranty();
  update_stats(DONE);
  return &accepting;
}

state_t* not_delivered()
{
  refund();
  update_stats(LOST);
  return &accepting;
}

void entry_to()
{
  get_address();
}

#endif
