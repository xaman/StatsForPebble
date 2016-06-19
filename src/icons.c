#include <pebble.h>
#include <string.h>
#include "icons.h"
	
	
void set_icon_resource(BitmapLayer* layer, int resource) {
	GBitmap* bitmap = gbitmap_create_with_resource(resource);
	bitmap_layer_set_bitmap(layer, bitmap);
	bitmap_layer_set_compositing_mode(layer, GCompOpSet);
}

void set_icon_from_id(BitmapLayer* layer, char *id) {
	if (strcmp(id, ICON_CART) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_CART);
	} else if (strcmp(id, ICON_DELIVERY) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_DELIVERY);
	} else if (strcmp(id, ICON_MONEY) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_MONEY);
	} else if (strcmp(id, ICON_DOLLAR) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_DOLLAR);
	}
}