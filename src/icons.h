#pragma once
#include <pebble.h>

	
#define ICON_CART "cart"
#define ICON_DOLLAR "dollar"
#define ICON_MARKET "market"
#define ICON_MONEY "money"
	
	
void set_icon_from_id(BitmapLayer* white_layer, BitmapLayer* black_layer, char *id);