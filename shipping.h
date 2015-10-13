#ifndef shipping_h
#define shipping_h

#include "state.h"

//Declare all of the functions performed when in the opening state.
static state_t* delivery_confirmed();
static state_t* not_delivered();
static void 	entry_to();

#endif
