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
  printf("Input character to change state.\n");
  scanf("%s", &user_input[0]);

  while (strcmp(user_input,"X")!=0)
  {
  	if (strcmp(user_input,"O") == 0)
  	{
  		handle_event(ORDER_RECEIVED);
  	}
  	else if (strcmp(user_input,"V") == 0)
  	{
  		handle_event(VALID_PAYMENT);
  	}
  	else if (strcmp(user_input,"I") == 0)
  	{
  		handle_event(REJECT_PAYMENT);
  	}
  	else if (strcmp(user_input,"F") == 0)
  	{
  		handle_event(FAILED_MANF);
  	}
	else if (strcmp(user_input,"C") == 0)
  	{
  		handle_event(PASS_MANF);
  	}
  	else if (strcmp(user_input,"R") == 0)
  	{
  		handle_event(DELIVERY_CONFIRMED);
  	}
  	else if (strcmp(user_input,"L") == 0)
  	{
  		handle_event(NOT_DELIVERED);
  	}
  	else
  	{
  		
  	}
  	scanf("%s", user_input);
  }
}
#endif
