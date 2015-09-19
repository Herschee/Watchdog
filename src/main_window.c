#include <pebble.h>
#include "main_window.h"
#include "alert_window.h"

#define NUM_MENU_SECTIONS 3
#define NUM_FIRST_MENU_ITEMS 1
#define NUM_SECOND_MENU_ITEMS 1
#define NUM_THIRD_MENU_ITEMS 1

static Window *s_main_window;
static MenuLayer *s_menu_layer;

static uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
  return NUM_MENU_SECTIONS;
}

static uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  switch (section_index) {
    case 0:
      return NUM_FIRST_MENU_ITEMS;
    case 1:
      return NUM_SECOND_MENU_ITEMS;
    case 2:
      return NUM_THIRD_MENU_ITEMS;
    default:
      return 0;
  }
}

static int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}

static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  // Determine which section we're working with
  switch (section_index) {
    case 0:
      // nothing above the watch buton
      break;
    case 1:
      // nothing above the stop button
    case 2:
      // nothing above the time button
      break;
  }
}

static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  // Determine which section we're going to draw in
  switch (cell_index->section) {
    case 0:
      // Use the row to specify which item we'll draw
      switch (cell_index->row) { //NUM_FIRST_MENU_ITEMS
        case 0:
          // draw the watch button
          menu_cell_basic_draw(ctx, cell_layer, "Watch", "Start the watchdog", NULL);
          break;
      }
      break;
    case 1:
      switch (cell_index->row) {
        case 0:
          // This is a basic menu item with a title and subtitle
          menu_cell_basic_draw(ctx, cell_layer, "Safe", "Stop the watchdog", NULL);
          break;
      }
    break;
    case 2:
      switch (cell_index->row) {
        case 0:
        
        menu_cell_basic_draw(ctx, cell_layer, "Check_In Time", "Time Until Check-In", NULL);
        break;
      }
      }
  }


static void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
  // Determine which section we're responding to
  WakeupId s_wakeup_id=0;
  switch (cell_index->section) {
    case 0:
      // Use the row to specify which item to respond to
      switch (cell_index->row) { //NUM_FIRST_MENU_ITEMS
        case 0:
          // schedule the watchdog
          if (persist_exists(PERSIST_KEY_WAKEUP_ID)) {
            s_wakeup_id = persist_read_int(PERSIST_KEY_WAKEUP_ID);
          }
          //Check the event is not already scheduled
          if (!wakeup_query(s_wakeup_id, NULL)) {
            // Current time + 30 seconds
            // TODO: alter this time? need to grab that from persistance then
            time_t future_time = calc_future_time();

            // Schedule wakeup event and keep the WakeupId
            s_wakeup_id = wakeup_schedule(future_time, WAKEUP_REASON, true);
            persist_write_int(PERSIST_KEY_WAKEUP_ID, s_wakeup_id);

          } else {
            // TODO: reschedule wakeup?
          }
          break;
      }
      break;
    case 1:
      switch (cell_index->row) {
        case 0:
          // unregister the watchdog
          if (persist_exists(PERSIST_KEY_WAKEUP_ID)) {
            s_wakeup_id = persist_read_int(PERSIST_KEY_WAKEUP_ID);
            wakeup_cancel(s_wakeup_id);
          }
          break;
      }
    case 2:
      switch (cell_index->row) {
        case 0:
        
          break;
      }
  }

}

static void main_window_load(Window *window) {

  // Now we prepare to initialize the menu layer
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  // Create the menu layer
  s_menu_layer = menu_layer_create(bounds);
  menu_layer_set_callbacks(s_menu_layer, NULL, (MenuLayerCallbacks){
    .get_num_sections = menu_get_num_sections_callback,
    .get_num_rows = menu_get_num_rows_callback,
    .get_header_height = menu_get_header_height_callback,
    .draw_header = menu_draw_header_callback,
    .draw_row = menu_draw_row_callback,
    .select_click = menu_select_callback,
  });

  // Bind the menu layer's click config provider to the window for interactivity
  menu_layer_set_click_config_onto_window(s_menu_layer, window);

  layer_add_child(window_layer, menu_layer_get_layer(s_menu_layer));
}

static void main_window_unload(Window *window) {
  // Destroy the menu layer
  menu_layer_destroy(s_menu_layer);
}

void init_main_window(){
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_stack_push(s_main_window, true);
}

void deinit_main_window(){
  window_destroy(s_main_window);
}