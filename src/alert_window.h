#pragma once

#define WAKEUP_REASON 0
#define PERSIST_KEY_WAKEUP_ID 42
  
  
void wakeup_handler(WakeupId id, int32_t reason);