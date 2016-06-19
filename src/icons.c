#include <pebble.h>
#include <string.h>
#include "icons.h"
	
	
void set_icon_resource(BitmapLayer* white_layer, BitmapLayer* black_layer, int white_resource, int black_resource) {
	GBitmap* icon_white = gbitmap_create_with_resource(white_resource);
	GBitmap* icon_black = gbitmap_create_with_resource(black_resource);
	bitmap_layer_set_bitmap(white_layer, icon_white);
	bitmap_layer_set_bitmap(black_layer, icon_black);
	bitmap_layer_set_background_color(white_layer, GColorClear);
	bitmap_layer_set_background_color(black_layer, GColorClear);
	bitmap_layer_set_compositing_mode(white_layer, GCompOpOr);
	bitmap_layer_set_compositing_mode(black_layer, GCompOpClear);
}


void set_icon_from_id(BitmapLayer* white_layer, BitmapLayer* black_layer, char *id) {
	if (strcmp(id, ICON_CART) == 0) {
		set_icon_resource(white_layer, black_layer, RESOURCE_ID_ICON_CART_WHITE, RESOURCE_ID_ICON_CART_BLACK);
	} else if (strcmp(id, ICON_DOLLAR) == 0) {
		set_icon_resource(white_layer, black_layer, RESOURCE_ID_ICON_DOLLAR_WHITE, RESOURCE_ID_ICON_DOLLAR_BLACK);
	} else if (strcmp(id, ICON_MARKET) == 0) {
		set_icon_resource(white_layer, black_layer, RESOURCE_ID_ICON_MARKET_WHITE, RESOURCE_ID_ICON_MARKET_BLACK);
	} else if (strcmp(id, ICON_MONEY) == 0) {
		set_icon_resource(white_layer, black_layer, RESOURCE_ID_ICON_MONEY_WHITE, RESOURCE_ID_ICON_MONEY_BLACK);
	}
}