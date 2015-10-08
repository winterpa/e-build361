#ifndef hardware_h
#define hardware_h
// Payment
// Events.
typedef enum
  {
    ORDER_RECEIVED
    VALID_PAYMENT,
    REJECT_PAYMENT,
    FAILED_MANF, //All requested replicas were not manufactured
    PASS_MANF,
    DELIVERY_CONFIRMED,
    NOT_DELIVERED
  } event;

void
get_payment_method();
void
dispatch_factory_lines();
void
shut_down_factory_lines();
void
get_address();
#endif
