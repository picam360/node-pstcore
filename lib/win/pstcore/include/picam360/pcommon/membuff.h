#pragma once

#ifdef __cplusplus

extern "C" {

#endif

//#include <pthread.h>
#include <stdbool.h>
//#include <uuid/uuid.h>
//#include <sys/time.h>
#include "reference.h"
	
#ifndef timeval
struct timeval{
	long tv_sec;
	long tv_usec;
};
#endif
	
typedef struct MEMBUFF_T {
	REFERENCE_H *ref;

	char uuid[16];
	char mem_type[5]; //"PROC"|"KERN"|"DMAB"|"EGL"|"CUDA"
	struct timeval timestamp;

	unsigned int size;
	unsigned char *data;
} MEMBUFF_T;

#ifdef __cplusplus

}

#endif
