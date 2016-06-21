#include <pebble.h>
#include <string.h>
#include "icons.h"
	
	
void set_icon_resource(BitmapLayer* layer, int resource) {
	GBitmap* bitmap = gbitmap_create_with_resource(resource);
	bitmap_layer_set_bitmap(layer, bitmap);
	bitmap_layer_set_compositing_mode(layer, GCompOpSet);
}

void set_icon_from_id(BitmapLayer* layer, char *id) {
	if (strcmp(id, ICON_ANDROID) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_ANDROID);
	} else if (strcmp(id, ICON_CART) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_CART);
	} else if (strcmp(id, ICON_COMMENT) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_COMMENT);
	} else if (strcmp(id, ICON_DATABASE) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_DATABASE);
	} else if (strcmp(id, ICON_DELIVERY) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_DELIVERY);
	} else if (strcmp(id, ICON_DISLIKE) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_DISLIKE);
	} else if (strcmp(id, ICON_DOLLAR) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_DOLLAR);
	} else if (strcmp(id, ICON_DOWNLOAD) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_DOWNLOAD);
	} else if (strcmp(id, ICON_FACEBOOK) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_FACEBOOK);
	} else if (strcmp(id, ICON_FAV) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_FAV);
	} else if (strcmp(id, ICON_FUNNEL) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_FUNNEL);
	} else if (strcmp(id, ICON_GOOGLEPLUS) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_GOOGLEPLUS);
	} else if (strcmp(id, ICON_INSTAGRAM) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_INSTAGRAM);
	} else if (strcmp(id, ICON_INSTALL) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_INSTALL);
	} else if (strcmp(id, ICON_IOS) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_IOS);
	} else if (strcmp(id, ICON_LIKE) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_LIKE);
	} else if (strcmp(id, ICON_LOCATION) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_LOCATION);
	} else if (strcmp(id, ICON_MEMORY) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_MEMORY);
	} else if (strcmp(id, ICON_MONEY) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_MONEY);
	} else if (strcmp(id, ICON_PERCENTAGE) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_PERCENTAGE);
	} else if (strcmp(id, ICON_PERFORMANCE) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_PERFORMANCE);
	} else if (strcmp(id, ICON_SERVER) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_SERVER);
	} else if (strcmp(id, ICON_SHARE) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_SHARE);
	} else if (strcmp(id, ICON_SHOP) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_SHOP);
	} else if (strcmp(id, ICON_STAR) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_STAR);
	} else if (strcmp(id, ICON_TIME) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_TIME);
	} else if (strcmp(id, ICON_TWITTER) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_TWITTER);
	} else if (strcmp(id, ICON_UPLOAD) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_UPLOAD);
	} else if (strcmp(id, ICON_USER) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_USER);
	} else if (strcmp(id, ICON_YOUTUBE) == 0) {
		set_icon_resource(layer, RESOURCE_ID_ICON_YOUTUBE);
	}
}