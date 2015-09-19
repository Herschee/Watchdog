#include "pebble.h"
  
#include "main_window.h"
#include "alert_window.h"
#include "splash_window.h"

static void init() {
  // Subscribe to Wakeup API
  wakeup_service_subscribe(wakeup_handler);
  
  // Launch the splash page
  init_splash_window();
  
  // Was this a wakeup launch?
  if (launch_reason() == APP_LAUNCH_WAKEUP) {
    // The app was started by a wakeup
    WakeupId id = 0;
    int32_t reason = 0;

    // Get details and handle the wakeup
    wakeup_get_launch_event(&id, &reason);
    wakeup_handler(id, reason);
  } else {
    init_main_window();
  }
}

static void deinit() {
  deinit_splash_window();
  deinit_main_window();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
