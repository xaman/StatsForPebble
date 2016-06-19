#include <pebble.h>
#include <string.h>
#include <icons.h>
#include <vibration.h>
#include "main.h"
	
// GUI
static Window *main_window;
// Layers
static TextLayer *time_layer;
static Layer *header_background_layer;
static BitmapLayer *icons[MAX_STATS];
static TextLayer *texts[MAX_STATS];
static TextLayer *loading_text;
// Fonts
static GFont time_font;
static GFont text_font;

/*
*
* Function to update the time layer value using the local time
*
*/
static void update_time() {
	// Get a tm structure
	time_t temp = time(NULL); 
	struct tm *tick_time = localtime(&temp);
	// Create a long-lived buffer
	static char buffer[] = "00:00";
	// Write the current hours and minutes into the buffer
	if (clock_is_24h_style() == true) {
		strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
	} else {
		strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
	}
	// Display this time on the TextLayer
	text_layer_set_text(time_layer, buffer);
}


static void initialize_main_window() {
	main_window = window_create();
}

static void set_background_color(Window *window, unsigned int color) {
    GColor col = (GColor){.argb = color};
	#ifdef PBL_COLOR
		window_set_background_color(main_window, col);
	#else
		// Force black and white for Aplite Pebbles
		if (color != GColorBlack.argb) {
			col = GColorWhite;
		}
		window_set_background_color(main_window, col);
	#endif
}

static void load_custom_fonts() {
	time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_MONKIRTA_40));
	text_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_MONKIRTA_20));
}

static void update_header_background(Layer *layer, GContext *ctx) {
	graphics_context_set_fill_color(ctx, GColorBlack);
	graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
}

static void initialize_header_background_layer(Layer *window_layer) {
	header_background_layer = layer_create(GRect(0, 0, SCREEN_WIDTH, HEADER_BACKGROUND_HEIGHT));
	layer_set_update_proc(header_background_layer, update_header_background);
	// Add to parent layer
	layer_add_child(window_layer, header_background_layer);
}

static void initialize_time_layer(Layer *window_layer) {
	time_layer = text_layer_create(GRect(0, TIME_LAYER_TOP_MARGIN, SCREEN_WIDTH, TIME_LAYER_HEIGHT));
	text_layer_set_font(time_layer, time_font);
	text_layer_set_background_color(time_layer, GColorClear);
	text_layer_set_text_color(time_layer, GColorWhite);
	text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);
	// Add to parent layer
	layer_add_child(window_layer, text_layer_get_layer(time_layer));
}

static void initialize_loading(Layer *window_layer) {
	loading_text = text_layer_create(GRect(0, 80, SCREEN_WIDTH, LOADING_TEXT_HEIGHT));
	text_layer_set_font(loading_text, text_font);
	text_layer_set_text_color(loading_text, GColorWhite);
	text_layer_set_background_color(loading_text, GColorClear);
	text_layer_set_text_alignment(loading_text, GTextAlignmentCenter);
	text_layer_set_text(loading_text, LOADING_TEXT);
	// Add to parent layer
	layer_add_child(window_layer, text_layer_get_layer(loading_text));
}

static void hide_loading() {
	layer_set_hidden((Layer *) loading_text, true);
}

static BitmapLayer * get_icon_layer(int x, int y, int size) {
	return bitmap_layer_create(GRect(x, y, size, size));
}

static void initialize_icon(Layer *window_layer, int x, int y, int position) {
	icons[position] = get_icon_layer(x, y, ICON_SIZE);
	layer_add_child(window_layer, bitmap_layer_get_layer(icons[position]));
}

static void initialize_icons(Layer *window_layer) {
	initialize_icon(window_layer, 18, 45, 0);
	initialize_icon(window_layer, 18, 108, 1);
	initialize_icon(window_layer, 90, 45, 2);
	initialize_icon(window_layer, 90, 108, 3);
}

static void initialize_text(Layer *window_layer, int x, int y, int position) {
	texts[position] = text_layer_create(GRect(x, y, SCREEN_WIDTH / 2, TEXT_HEIGHT));
	text_layer_set_font(texts[position], text_font);
	text_layer_set_background_color(texts[position], GColorClear);
	text_layer_set_text_alignment(texts[position], GTextAlignmentCenter);
	layer_add_child(window_layer, text_layer_get_layer(texts[position]));
}

/*
*	https://www.google.es/url?sa=t&rct=j&q=&esrc=s&source=web&cd=2&cad=rja&uact=8&ved=0CCgQFjABahUKEwjgjru54-fHAhWhaNsKHXdqA-I&url=http%3A%2F%2Fforums.getpebble.com%2Fdiscussion%2F21166%2Fcstring-to-hex-not-working-as-expected&usg=AFQjCNEWu2xFWuS8YvHYL44u2jyzP6CgCw&sig2=AXdf8PQ3I7GR5_MLEUiCyg
*/
static void set_text_color(TextLayer *layer, unsigned int color) {
	#ifdef PBL_COLOR
		GColor col;
		col.argb = color;
		text_layer_set_text_color(layer, col);	
	#else
		text_layer_set_text_color(layer, GColorBlack);
	#endif
}

static void set_text_value(TextLayer *layer, char *text) {
	text_layer_set_text(layer, text);
}

static void initialize_texts(Layer *window_layer) {
	initialize_text(window_layer, 0, 81, 0);
	initialize_text(window_layer, 0, 144, 1);
	initialize_text(window_layer, 72, 81, 2);
	initialize_text(window_layer, 72, 144, 3);
}

/*
*
* Function called when the main window starts
*
*/
static void main_window_load(Window *window) {
	Layer *window_layer = window_get_root_layer(window);
	load_custom_fonts();
	initialize_header_background_layer(window_layer);
	initialize_time_layer(window_layer);
	// Set black background while loading
	set_background_color(main_window, COLOR_BLACK);
	initialize_loading(window_layer);
	initialize_icons(window_layer);
	initialize_texts(window_layer);
	update_time();
}

/*
*
* Function called when the main window ends
* It is the right place to free the memory
*
*/
static void main_window_unload(Window *window) {
	text_layer_destroy(time_layer);
}

/*
*
* Function to register callbacks to capture main window load and unload events
*
*/
static void register_window_handlers() {
	window_set_window_handlers(main_window, (WindowHandlers) {
		.load = main_window_load,
		.unload = main_window_unload
	});
}

/*
*
* Function called one time per minute to handle the time change
*
*/
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
	update_time();
	// Update every 30 minutes
	if(tick_time->tm_min % HALF_HOUR == 0) {
		
	}
}

static char* find_string(DictionaryIterator *iterator, const uint32_t key) {
	return dict_find(iterator, key)->value->cstring;
}

static unsigned int find_int(DictionaryIterator *iterator, const uint32_t key) {
	return dict_find(iterator, key)->value->uint8;
}

/*
*
* Function that handles the messages from the JS script
*
*/
static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
	// Set icons
	set_icon_from_id(icons[0], find_string(iterator, FIRST_ICON));
	set_icon_from_id(icons[1], find_string(iterator, SECOND_ICON));
	set_icon_from_id(icons[2], find_string(iterator, THIRD_ICON));
	set_icon_from_id(icons[3], find_string(iterator, FOURTH_ICON));
	// Set text colors
	set_text_color(texts[0], find_int(iterator, FIRST_COLOR));
	set_text_color(texts[1], find_int(iterator, SECOND_COLOR));
	set_text_color(texts[2], find_int(iterator, THIRD_COLOR));
	set_text_color(texts[3], find_int(iterator, FOURTH_COLOR));
	// Set values
	set_text_value(texts[0], find_string(iterator, FIRST_VALUE));
	set_text_value(texts[1], find_string(iterator, SECOND_VALUE));
	set_text_value(texts[2], find_string(iterator, THIRD_VALUE));
	set_text_value(texts[3], find_string(iterator, FOURTH_VALUE));
	// Set background color
	set_background_color(main_window, find_int(iterator, BACKGROUND_COLOR));
	// Check vibration
	check_vibration(find_string(iterator, VIBRATION));
	// Hide loading
	hide_loading();
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
	APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
	APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
	APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

/*
*
* Function to register callbacks to handle messages
*
*/
static void register_message_callbacks() {
	app_message_register_inbox_received(inbox_received_callback);
	app_message_register_inbox_dropped(inbox_dropped_callback);
	app_message_register_outbox_failed(outbox_failed_callback);
	app_message_register_outbox_sent(outbox_sent_callback);
}

/*
*
* Function called when the watchface is launched
*
*/
static void init() {
	initialize_main_window();
	// Set handlers to manage the elements inside the Window
	register_window_handlers();
	// Show the Window on the watch, with animated=true
	window_stack_push(main_window, true);
	// Register with TickTimerService
	tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
	// Register callbacks
	register_message_callbacks();
	// Open AppMessage
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

static void deinit() {
	window_destroy(main_window);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}