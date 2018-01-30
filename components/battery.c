/* See LICENSE file for copyright and license details. */
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../util.h"

// threshold battery percentage
#define THRESHOLD 15

const char *
battery_perc(const char *bat)
{
	int perc;
	char path[PATH_MAX];

	snprintf(path, sizeof(path), "%s%s%s", "/sys/class/power_supply/", bat, "/capacity");
	return (pscanf(path, "%i", &perc) == 1) ?
	       bprintf("%d", perc) : NULL;
}

const char *
battery_power(const char *bat)
{
	int watts;
	char path[PATH_MAX];

	snprintf(path, sizeof(path), "%s%s%s", "/sys/class/power_supply/", bat, "/power_now");
	return (pscanf(path, "%i", &watts) == 1) ?
	       bprintf("%d", (watts + 500000) / 1000000) : NULL;
}

const char *
battery_state(const char *bat)
{
	struct {
		char *state;
		char *symbol;
	} map[] = {
		{ "Charging",    "CHARGING" },
		{ "Discharging", "DYING" },
		{ "Full",        "FULL OF SHIT" },
		{ "Unknown",     "YOU LOST UR BATTERY bruhhh" },
	};
	size_t i;
	char path[PATH_MAX], state[12];

	snprintf(path, sizeof(path), "%s%s%s", "/sys/class/power_supply/", bat, "/status");
	if (pscanf(path, "%12s", state) != 1) {
		return NULL;
	}

	for (i = 0; i < LEN(map); i++) {
		if (!strcmp(map[i].state, state)) {
			break;
		}
	}
	return (i == LEN(map)) ? "?" : map[i].symbol;
}

bool is_battery_low(int * how_low){
	char path[PATH_MAX];
	snprintf(path, sizeof(path), "%s%s%s", "/sys/class/power_supply/", "BAT1", "/capacity");
  pscanf(path, "%i", how_low);

  char path2[PATH_MAX], state[12];
  snprintf(path2, sizeof(path2), "%s%s%s", "/sys/class/power_supply/", "BAT1", "/status");
  pscanf(path2, "%12s", state);
  if(strcmp(state, "Discharging") == 0 && *how_low <= THRESHOLD ){
    return true;
  }
  return false;
}
