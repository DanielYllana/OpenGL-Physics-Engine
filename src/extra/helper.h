#ifndef HELPER_CLASS_H
#define HELPER_CLASS_H

#include <math.h>


class Helper
{
public:
	static float randf();
	static float randf(float range, bool posOnly);
private:

	// disallow the creation of an instance
	Helper() {}
};

#endif

