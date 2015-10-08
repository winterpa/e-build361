#ifndef manufacturing_h
#define manufacturing_h

#include "state.h"

// Declare all of the functions performed when in the closing state.
static state_t* closed_detected();
static state_t* open_button_pressed();
static void 	entry_to();

#endif