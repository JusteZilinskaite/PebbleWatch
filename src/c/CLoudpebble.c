#include <pebble.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Window *s_window;
static TextLayer *s_text_layer;
static BitmapLayer *s_bt_icon_layer;
static GBitmap *s_bt_icon_bitmap;
static char s_activity[12] = "Running";
 
//-------------------------------------------------------------------------------------
void progress_float_to_string(char *new_string, float prog, int prog_resolution)
{
  if(prog==1)
  {
    strcat(new_string, "Well done!\n");
  }
  else
  {
    strcat(new_string, "[");
    int number_plus = (int) (prog_resolution * prog);
  
    for(int i=0; i< number_plus; i++)
      strcat(new_string, "+");
  
    for(int i=0; i< prog_resolution - number_plus; i++)
      strcat(new_string, "-");
  
    strcat(new_string, "]");
    strcat(new_string, "\n");
    
  }
  char perc_string[4] = "";
  int percentage = (int) (prog*100);
  snprintf(perc_string, 4, "%d", percentage);
  strcat(perc_string, "%");
  strcat(new_string, perc_string);
}
//--------------------------------------------------------------------------------------

static void init(void) {
  // Create a window and get information about the window
  s_window = window_create();
  Layer *window_layer = window_get_root_layer(s_window);
  GRect bounds = layer_get_bounds(window_layer);
  char final_string[100] = "";
  char progress_string[50] = "";
  
  //ACTIVITY
  // Create a text layer and set the text
  s_text_layer = text_layer_create(bounds);
  float prog = 1;
  int prog_resolution = 12;
  
  strcat(final_string, s_activity);
  strcat(final_string, "\n\n\n\n");
  
  progress_float_to_string(progress_string, prog, prog_resolution);
  strcat(final_string, progress_string);
  
 text_layer_set_text(s_text_layer, final_string);
  
  // Set the font and text alignment
  text_layer_set_font(s_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);

  // Add the text layer to the window
  layer_add_child(window_get_root_layer(s_window), text_layer_get_layer(s_text_layer));
  
  // Enable text flow and paging on the text layer, with a slight inset of 10, for round screens
  text_layer_enable_screen_text_flow_and_paging(s_text_layer, 10);
  if(prog >=0.8 && prog!=1)
  {
    // Create the icon GBitmap
    s_bt_icon_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BT_ICON);
  
    // Create the BitmapLayer to display the GBitmap
    s_bt_icon_layer = bitmap_layer_create(GRect(50, 70, 50, 50));
    bitmap_layer_set_bitmap(s_bt_icon_layer, s_bt_icon_bitmap);
    layer_add_child(window_get_root_layer(s_window), bitmap_layer_get_layer(s_bt_icon_layer));  
  }
  else if(prog!=1)
  {
     // Create the icon GBitmap
    s_bt_icon_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BT_ICON2);
  
    // Create the BitmapLayer to display the GBitmap
    s_bt_icon_layer = bitmap_layer_create(GRect(50, 70, 50, 50));
    bitmap_layer_set_bitmap(s_bt_icon_layer, s_bt_icon_bitmap);
    layer_add_child(window_get_root_layer(s_window), bitmap_layer_get_layer(s_bt_icon_layer));
  }

 
  
  // Push the window, setting the window animation to 'true'
  window_stack_push(s_window, true);
  
  // App Logging!
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");
}
//-----------------------------------------------------------------------------------------------
static void deinit(void) {
  // Destroy the text layer
  text_layer_destroy(s_text_layer);
  
  // Destroy the window
  window_destroy(s_window);
  
}
//-----------------------------------------------------------------------------------------------
int main(void) {
  init();
  app_event_loop();
  deinit();
}