#ifndef driver
#define driver

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "statemodel.h"

int main()
{
  char user_input[1];
  char* cur_state;
  char* valid_event;

  cur_state = " ";
  scanf("%s", &user_input[0]);

  while (strcmp(user_input,"x")!=0)
  {
  	if (strcmp(user_input,"O") == 0)
  	{
  		handle_event(OPENED_DETECTED);
  	}
  	else if (strcmp(user_input,"C") == 0)
  	{
  		handle_event(CLOSED_DETECTED);
  	}
  	else if (strcmp(user_input,"o") == 0)
  	{
  		handle_event(OPEN_BUTTON_PRESSED);
  	}
  	else if (strcmp(user_input,"c") == 0)
  	{
  		handle_event(CLOSE_BUTTON_PRESSED);
  	}
	else
	{
		
	}
  	scanf("%s", user_input);
  }
}
#endif
