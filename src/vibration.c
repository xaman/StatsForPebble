#include <pebble.h>
#include <string.h>
#include "vibration.h"


void check_vibration(char *mode) {
	if (strcmp(mode, MODE_LONG) == 0) {
		vibes_long_pulse();
	} else if (strcmp(mode, MODE_SHORT) == 0) {
		vibes_short_pulse();
	}
}