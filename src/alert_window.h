#pragma once
#include <pebble.h>

#define WAKEUP_REASON 0
#define PERSIST_KEY_WAKEUP_ID 42

#define PERSIST_KEY_INTERVAL_TIME 2
// TODO increase
#define DEFAULT_INTERVAL_TIME 5

#define PERSIST_KEY_BUZZ_TIME 3
// TODO increase
#define DEFAULT_BUZZ_TIME 5
  
#define PERSIST_KEY_NAME 1
#define PERSIST_KEY_PHONE_NUMBER 0
  
void wakeup_handler(WakeupId id, int32_t reason);
time_t calc_future_time();
