#include <pebble.h>
#include "time_window.h"
#include "alert_window.h"

#define BANNER_TEXT "Time to check in!!!"
#define CLOCK_FORMAT_STRING "%02d:%02d"
#define NOTIFY_TIME 30

static Window *s_time_window;
static TextLayer *s_time_text_layer;


static int curr_time = 0;

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  // Use a long-lived buffer
  static char s_uptime_buffer[32];
 // static char s_curr_buffer[32];

  if (persist_exists(PERSIST_KEY_WAKEUP_ID)) {
    
      WakeupId s_wakeup_id = persist_read_int(PERSIST_KEY_WAKEUP_ID);
      time_t wakeup_time;
    if(wakeup_query(s_wakeup_id, &wakeup_time))
      {
        curr_time = wakeup_time - time(NULL);
    }     
      
     int seconds = curr_time % 60;
     int minutes = (curr_time % 3600) / 60;
     int hours = curr_time / 3600;
    
    
   snprintf(s_uptime_buffer, sizeof(s_uptime_buffer), "Remaining Time: %dh %dm %ds", hours, minutes, seconds);
    text_layer_set_text(s_time_text_layer, s_uptime_buffer);
  } 
}



static void time_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);

  // Create output TextLayer
  s_time_text_layer = text_layer_create(GRect(5, 0, window_bounds.size.w - 5, window_bounds.size.h));
  text_layer_set_font(s_time_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text(s_time_text_layer, "Remaining Time: 0h 0m 30s");


  text_layer_set_overflow_mode(s_time_text_layer, GTextOverflowModeWordWrap);
  layer_add_child(window_layer, text_layer_get_layer(s_time_text_layer));
}


static void time_window_unload(Window *window) {
  // Destroy output TextLayer
  text_layer_destroy(s_time_text_layer);
}


void init_time_window(){
  s_time_window = window_create();
 // window_set_click_config_provider(s_time_window, click_config_provider);
  window_set_window_handlers(s_time_window, (WindowHandlers) {
    .load = time_window_load,
    .unload = time_window_unload,
    
  });
  tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
  window_stack_push(s_time_window, true);
}

void deinit_time_window(){
  window_destroy(s_time_window);
}

