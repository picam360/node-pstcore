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

typedef void *PVFLDR_T;
typedef void (*PVFLDR_CALLBACK)(unsigned char *data, int size, bool is_frame, int n_frame, void *arg);

PVFLDR_T FUNC_DEF pvfldr_new(const char *url, const char *head_query, const char *get_query, PVFLDR_CALLBACK callback,
		void *arg);
void FUNC_DEF pvfldr_delete(PVFLDR_T _this);
void FUNC_DEF pvfldr_load(PVFLDR_T _this, int pitch, int yaw, int frame_cur);

float FUNC_DEF pvfldr_get_kf_latency_ave(PVFLDR_T _this);
float FUNC_DEF pvfldr_get_kf_latency_sigma(PVFLDR_T _this);

#ifdef __cplusplus

}

#endif
