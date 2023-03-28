#pragma once

#ifdef __cplusplus

extern "C" {

#endif

#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include "reference.h"

typedef struct MEMBUFF_T {
	REFERENCE_H *ref;

	unsigned char uuid[16];
	char mem_type[5]; //"PROC"|"KERN"|"DMAB"|"EGL"|"CUDA"

	unsigned int size;
	unsigned char *data;
} MEMBUFF_T;

#ifdef __cplusplus

}

#endif
