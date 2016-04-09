#include <pebble.h>

// "A service is a self-contained unit of functionality, 
// such as retrieving an online bank statement."
  // - Wikipedia
// The attributes seem to be more like the actual function
// within a given service that we want to execute

// We need to define what services the watch/smartstrap 
// will be providing, and the attributes. In this case,
// we want to just send data as is.

static const SmartstrapServiceId s_service_id = SMARTSTRAP_RAW_DATA_SERVICE_ID; //;0x1001
static const SmartstrapAttributeId brighten_bulb_attribute_id = SMARTSTRAP_RAW_DATA_ATTRIBUTE_ID; // ;0x1001
static const int s_buffer_length = 64;

SmartstrapAttribute *brighten_bulb_attribute;

// //handle when strap availability changes
static void strap_availability_handler(SmartstrapServiceId service_id,
                                       bool is_available){
  if (is_available){
    //do good stuff!!
    return;
  } else {
    //print to screen "Please connect your strap"
    return;
  }
}

// //handle when we have read some data. Gives us the data too!
// static void strap_read_handler(SmartstrapAttribute *attribute, 
//                                SmartstrapResult result, const uint8_t *data, 
//                                size_t length) {
//   return;
// }

// //handle when we write to strap. (Don't need data parameter because data already sent to strap.)
// static void strap_write_handler(SmartstrapAttribute *attribute, 
//                                 SmartstrapResult result) {
//   return;
// }

// //handle when the strap wants to give data to watch. Don't think this will happen though.
// static void strap_notify_handler(SmartstrapAttribute *attribute){
//   return;
// }

static void init() {
  //make attributes
  brighten_bulb_attribute = smartstrap_attribute_create(s_service_id, brighten_bulb_attribute_id, s_buffer_length);
  
  //register handlers
  SmartstrapHandlers handlers = {
    .availability_did_change = strap_availability_handler,
    //.did_read = strap_read_handler,
   // .did_write = strap_write_handler,
   // .notified = strap_notify_handler
  };
  smartstrap_subscribe(handlers);
}

static void ping_smartstrap() {
  // Pointer to the attribute buffer
  size_t buff_size;
  uint8_t *buffer;
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "buffer length is %d", s_buffer_length);
  // Begin the write request, getting the buffer and its length
  smartstrap_attribute_begin_write( brighten_bulb_attribute, &buffer, &buff_size);
  
  // Store the data to be written to this attribute
  snprintf((char*)buffer, buff_size, "1");

  // End the write request, and send the data, not expecting a response
  smartstrap_attribute_end_write(brighten_bulb_attribute, buff_size, false);
}

static void deinit() {
  //destroy attributes
  smartstrap_attribute_destroy(brighten_bulb_attribute);
}

///////////INTERACTIVE COMPONENT OF THE APP ///////
//select button handler
void select_single_click_handler(ClickRecognizerRef recognizer, void *context){
    ping_smartstrap();
}

//click handler
void config_provider(Window *window){
  window_single_click_subscribe(BUTTON_ID_SELECT, select_single_click_handler);
}


////////// UI COMPONENT OF THE APP /////
//initializes home layers

Window *g_home;
Window *g_recipe_list;
TextLayer *g_title;
TextLayer *g_subtitle;


void home_load(Window *window){
  g_title = text_layer_create(GRect(20, 0, 100, 40));
  text_layer_set_background_color(g_title, GColorClear);
  text_layer_set_text_color(g_title, GColorBlack);
  text_layer_set_text(g_title, "Remote");
  text_layer_set_font(g_title, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text_alignment(g_title, GTextAlignmentCenter);
  
  g_subtitle = text_layer_create(GRect(0, 50, 144, 20));
  text_layer_set_background_color(g_subtitle, GColorClear);
  text_layer_set_text_color(g_subtitle, GColorBlack);
  text_layer_set_text(g_subtitle, "Buttons Adjust da Bulb");
  
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(g_title));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(g_subtitle));
}
//de-initializes home layers
void home_unload(Window *window){
  text_layer_destroy(g_title);
  text_layer_destroy(g_subtitle);
}

//initializes home window
void handle_init(void) {
 g_home = window_create();
  window_set_window_handlers(g_home, (WindowHandlers) {
    .load = home_load,
    .unload = home_unload,
  });
  
  window_set_click_config_provider(g_home, (ClickConfigProvider) config_provider);
  
  window_stack_push(g_home, true);
}

//de-initializes home window
void handle_deinit(void) {
  window_destroy(g_home);
}


int main(){
    APP_LOG(APP_LOG_LEVEL_DEBUG, "got to main %d", s_buffer_length);
init();
  handle_init();
 app_event_loop();
  handle_deinit();
  
 deinit();
}