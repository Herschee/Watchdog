#include <pebble.h>
#include "time_window.h"

#define BANNER_TEXT "Time to check in!!!"
#define CLOCK_FORMAT_STRING "%02d:%02d"
#define NOTIFY_TIME 30

static Window *s_time_window;
static TextLayer *s_time_text_layer;


static void time_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);

  // Create output TextLayer
  s_time_text_layer = text_layer_create(GRect(5, 0, window_bounds.size.w - 5, window_bounds.size.h));
  text_layer_set_font(s_time_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text(s_time_text_layer, "This works!!");
  text_layer_set_overflow_mode(s_time_text_layer, GTextOverflowModeWordWrap);
  layer_add_child(window_layer, text_layer_get_layer(s_time_text_layer));
}

static void time_window_unload(Window *window) {
  // Destroy output TextLayer
  //vibes_cancel();
  //tick_timer_service_unsubscribe();
  text_layer_destroy(s_time_text_layer);
}

// // Create alert window
//   s_time_window = window_create();
//   window_set_click_config_provider(s_time_window, click_config_provider);
//   window_set_window_handlers(s_time_window, (WindowHandlers) {
//     .load = time_window_load,
//     .unload = time_window_unload
//   });
//   window_stack_push(s_time_window, true);



void init_time_window(){
  s_time_window = window_create();
  window_set_window_handlers(s_time_window, (WindowHandlers) {
    .load = time_window_load,
    .unload = time_window_unload,
  });
  window_stack_push(s_time_window, true);
}

void deinit_time_window(){
  window_destroy(s_time_window);
}