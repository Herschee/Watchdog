#include <pebble.h>
#include "splash_window.h"

// Amount of time, in milliseconds, to flash splash window
#define SPLASH_TIME 1000

// Defining a Window object
static Window *s_splash_window;

// Bitmap pointer and layer for the png image
static GBitmap *s_splash_bitmap;
static BitmapLayer *s_splash_bitmap_layer;

// When called, remove the Window from the stack
void timer_callback(void *data) {
  window_stack_pop(true);
}

// Window load handler
static void splash_window_load(Window *window) {
  app_timer_register(SPLASH_TIME, (AppTimerCallback) timer_callback, NULL);
  Layer *window_layer = window_get_root_layer(s_splash_window);
  s_splash_bitmap = gbitmap_create_with_resource(RESOURCE_ID_LOGO_144PX);
  s_splash_bitmap_layer = bitmap_layer_create(GRect(0, 0, 144, 144));
  bitmap_layer_set_bitmap(s_splash_bitmap_layer, s_splash_bitmap);
  layer_add_child(window_get_root_layer(s_splash_window), bitmap_layer_get_layer(s_splash_bitmap_layer));
}

// Window unload handler
static void splash_window_unload(Window *window) {
  gbitmap_destroy(s_splash_bitmap);
  bitmap_layer_destroy(s_splash_bitmap_layer);
}

// Initialize Window
void init_splash_window() {
  // Create main Window element and assign to pointer
  s_splash_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_splash_window, (WindowHandlers) {
    .load = splash_window_load,
    .unload = splash_window_unload,
  });
  
  // Show the Window on the watch
  window_stack_push(s_splash_window, true);
}

// Destroy Window
void deinit_splash_window() {
  window_destroy(s_splash_window);
}