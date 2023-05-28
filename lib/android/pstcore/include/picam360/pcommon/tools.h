#pragma once
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>


#ifdef __cplusplus

extern "C" {

#endif

int inputAvailable();

int stat_mkdir(const char *filepath, mode_t mode);

int mkdir_path(const char *filepath, mode_t mode);

void strchg(char *buf, const char *str1, const char *str2);

int strcasecmpr(const char *str1, const char *str2);

void encodeHTML(char *str);
void decodeHTML(char *str);

void copyfile(const char *from, const char *to);

char *base64_encode(const unsigned char *data,
	size_t input_length,
	size_t *output_length);
unsigned char *base64_decode(const char *data,
	size_t input_length,
	size_t *output_length);

#ifdef __cplusplus

}

#endif
