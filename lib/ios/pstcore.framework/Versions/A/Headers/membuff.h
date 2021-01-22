#pragma once

#ifdef __cplusplus

extern "C" {

#endif

#include <pthread.h>
#include <stdbool.h>
#include <uuid/uuid.h>
#include "reference.h"

typedef struct MEMBUFF_T {
	REFERENCE_H *ref;

	uuid_t uuid;
	char mem_type[5]; //"PROC"|"KERN"|"DMAB"|"EGL"|"CUDA"
	struct timeval timestamp;

	unsigned int size;
	unsigned char *data;
} MEMBUFF_T;

#ifdef __cplusplus

}

#endif
