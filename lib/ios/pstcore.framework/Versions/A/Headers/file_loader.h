#pragma once

#if defined(__EMSCRIPTEN__)
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/threading.h>
#endif

#ifdef __cplusplus

extern "C" {

#endif

#if defined(__EMSCRIPTEN__)
#define FUNC_DEF EMSCRIPTEN_KEEPALIVE
#else
#define FUNC_DEF
#endif

typedef void *FILELDR_T;
typedef void *FILELDR_REQ_T;
typedef void (*FILELDR_CALLBACK)(unsigned char *data, int size, void *arg);

void FUNC_DEF fileldr_new(FILELDR_T *out_obj, const char *url, uint64_t offset, int length, const char *head_query, const char *get_query, FILELDR_CALLBACK callback, void *arg);
void FUNC_DEF fileldr_delete(FILELDR_T _this);
void FUNC_DEF fileldr_poll(FILELDR_T _this);
bool FUNC_DEF fileldr_get_active(FILELDR_T _this, FILELDR_REQ_T req);
FILELDR_REQ_T FUNC_DEF fileldr_load(FILELDR_T _this, uint64_t offset, int length);

#ifdef __cplusplus

}

#endif
