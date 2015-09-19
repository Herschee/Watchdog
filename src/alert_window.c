#include <pebble.h>
#include "alert_window.h"

#define BANNER_TEXT "Time to check in!!!"
#define CLOCK_FORMAT_STRING "%02d:%02d"
#define NOTIFY_TIME 30

static Window *s_alert_window;
static TextLayer *s_alert_text_layer;

static int alert_time = 0;

static const uint32_t segments[] = { 200, 100, 400 };
VibePattern pat = {
  .durations = segments,
  .num_segments = ARRAY_LENGTH(segments),
};

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  static char s_uptime_buffer[32];
  vibes_short_pulse();
  alert_time++;
  if(alert_time > NOTIFY_TIME ){
    //TODO: write notification code
    tick_timer_service_unsubscribe();
    vibes_cancel();
    //do we want to pop this??
    window_stack_pop(true);
  } else {
    snprintf(s_uptime_buffer, sizeof(s_uptime_buffer), BANNER_TEXT "\n" CLOCK_FORMAT_STRING, 
             alert_time/60, alert_time%60);
    text_layer_set_text(s_alert_text_layer, s_uptime_buffer);
  }
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  time_t future_time = time(NULL) + 5;
  // Schedule wakeup event and keep the WakeupId
  WakeupId s_wakeup_id = wakeup_schedule(future_time, WAKEUP_REASON, true);
  alert_time = 0;
  persist_write_int(PERSIST_KEY_WAKEUP_ID, s_wakeup_id);
  window_stack_pop_all(true);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  //window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  //window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void alert_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);

  // Create output TextLayer
  s_alert_text_layer = text_layer_create(GRect(5, 0, window_bounds.size.w - 5, window_bounds.size.h));
  text_layer_set_font(s_alert_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text(s_alert_text_layer, "Time to check in!!");
  text_layer_set_overflow_mode(s_alert_text_layer, GTextOverflowModeWordWrap);
  layer_add_child(window_layer, text_layer_get_layer(s_alert_text_layer));
}

static void alert_window_unload(Window *window) {
  // Destroy output TextLayer
  vibes_cancel();
  text_layer_destroy(s_alert_text_layer);
}

void wakeup_handler(WakeupId id, int32_t reason) {
  // The app has woken!
  // Subscribe to TickTimerService
  tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
  
  // Create alert window
  s_alert_window = window_create();
  window_set_click_config_provider(s_alert_window, click_config_provider);
  window_set_window_handlers(s_alert_window, (WindowHandlers) {
    .load = alert_window_load,
    .unload = alert_window_unload
  });
  window_stack_push(s_alert_window, true);

  // Delete the ID
  persist_delete(PERSIST_KEY_WAKEUP_ID);
}