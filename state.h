#ifndef state_h
#define state_h

// Add an alias for a type to the global name space.
typedef struct state state_t;

// Add an alias for event handlers.
typedef state_t * event_handler(void);

//Add an alias for actions.
typedef void action(void);

//Define the format of a state struct.
struct state {
	event_handler* 	order_received;
	event_handler*       valid_payment;
	event_handler*	invalid_payment;
	event_handler*	failed_manf;
	event_handler* 	pass_manf;
	event_handler*	delivery_confirmed;
	event_handler*	not_delivered;
	action*		entry_to;
	action*		exit_from;
	char*		state_name;
};

// Declare variables to hold pointers to the default event handler and
// the default action. They are extern because they are used in each
// of the individual state files but defined in state.c
extern state_t * 	default_event_handler();
extern void			default_action();
#endif
