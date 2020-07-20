#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>

#include "../output/DARK.h"

#define DARK_LITTLE_ENDIAN 1
#define DARK_BIG_ENDIAN    2

#ifndef DARK_ENDIAN
	#define DARK_ENDIAN DARK_LITTLE_ENDIAN
#endif
