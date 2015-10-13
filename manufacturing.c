#ifndef manufacturing_c
#define manufacturing_c

#include "manufacturing.h"
#include "actions.h"
#include "statemodel.h" // For the other states

// Create the object of the closing state.
state_t manufacturing = {
	"Manufacturing",
	default_event_handler, //order_received
	default_event_handler, //valid_payment
	default_event_handler, //invalid_payment
	failed_manf, //failed_manf
	pass_manf, //pass_manf
	default_event_handler, //delivery_confirmed
	default_event_handler, //not_delivered
	entry_to,
	exit_from
};

state_t* pass_manf()
{
  exit_from();
  charge_client();
  return &shipping;
}

state_t* failed_manf()
{
  exit_from();
  update_stats(FAIL);
  return &accepting;
}

void entry_to()
{
  dispatch_factory_lines();  
}

void exit_from()
{
  shut_down_factory_lines();
}

#endif
