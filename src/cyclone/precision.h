
#ifndef CYCLONE_PRECISION_H
#define CYCLONE_PRECISION_H

#include <float.h>

namespace cyclone {

	/*
		Defines a real number precision. Cyclone can be compiled in single or double precision
	*/

	typedef float real;

	#define DOUBLE_PRECISION
	#define REAL_MAX DBL_MAX
	#define real_sqrt sqrt
		/** Defines the precision of the power operator. */
	#define real_pow powf
	/** Defines the precision of the absolute magnitude operator. */
	#define real_abs fabsf
	/** Defines the precision of the sine operator. */
	#define real_sin sinf
	/** Defines the precision of the cosine operator. */
	#define real_cos cosf
	/** Defines the precision of the exponent operator. */
	#define real_exp expf

	#define real_fmod fmod
	#define R_PI 3.14159265358979
}


#endif // CYCLONE_PRECISION_H