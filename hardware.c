#ifndef hardware_c
#define hardware_c

#include <stdlib.h>
#include <stdio.h>

#include "hardware.h"

// Functions for controlling the LED Indicators.
void
set_closed_indicator(led_setting value)
{
  if (value == LED_OFF)
  {
    printf("The closed LED is now off.\n");
  }
  else if (value == LED_ON)
  {
    printf("The closed LED is now on.\n");
  }
}
void
set_opened_indicator(led_setting value)
{
  if (value == LED_OFF)
  { 
    printf("The opened LED is now off.\n");
  }
  else if (value == LED_ON)
  {
    printf("The opened LED is now on.\n");
  }
}
// Functions for controlling the Motor.
void
set_motor(motor_setting value)
{
  if (value == MOTOR_CLOSING)
  {
    printf("The motor is now closing the door.\n");
  }
  else if (value == MOTOR_OFF)
  {
    printf("The motor is now off.\n");
  }
  else if (value == MOTOR_OPENING)
  {
    printf("The motor is now opening the door.\n");
  }
}
#endif
