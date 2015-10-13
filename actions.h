#ifndef actions_h
#define actions_h

typedef enum
{
  DONE,
  LOST,
  FAIL,
  NUM_STATS
} stats;

typedef enum 
{
  ORDER_RECEIVED
  VALID_PAYMENT,
  REJECT_PAYMENT,
  FAILED_MANF, //All requested replicas were not manufactured
  PASS_MANF,
  DELIVERY_CONFIRMED,
  NOT_DELIVERED,
  NUM_EVENTS
} event;

void
get_payment_method();
void
dispatch_factory_lines();
void
shut_down_factory_lines();
void
get_address();
void
update_stats(stats status);
void
charge_client();
#endif
