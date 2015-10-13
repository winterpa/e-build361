#ifndef statemodel_h
#define statemodel_h

#include <stdlib.h>
#include <stdint.h>

#include "actions.h"
#include "state.h"

//Declare all of the states used in the state model.
// They are extern because they are defined (i.e., the memory is
// actually allocated) elsewhere (i.e., in the .c files for the
// individual states).

#define LIMIT 10;

extern uint8_t attempts;

extern state_t accepting;
extern state_t manufacturing;
extern state_t processing;
extern state_t shipping;

//Declare all of the functions.

void handle_event(event current_event);

#endif
