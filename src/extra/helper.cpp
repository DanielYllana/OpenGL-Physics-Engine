#include "helper.h"
#include <cstdlib>

// (-1, 1)
float Helper::randf()
{
	return -1.0f + (rand() / (RAND_MAX / 2.0f));
}


float Helper::randf(float range, bool posOnly)
{
	if (posOnly) {
		return rand() / (RAND_MAX / range);
	}
	else {
		return (range * -1.0f) + (rand() / (RAND_MAX / 2 * range));
	}
}