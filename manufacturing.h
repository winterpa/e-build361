#ifndef manufacturing_h
#define manufacturing_h

#include "state.h"

// Declare all of the functions performed when in the closing state.
static state_t* failed_manf();
static state_t* pass_manf();
static void 	entry_to();
static void	exit_from();
#endif
