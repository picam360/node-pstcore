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

typedef void *PSFLDR_T;
typedef void (*PSFLDR_CALLBACK)(unsigned char *data, int size, bool is_frame, int n_frame, void *arg);

void FUNC_DEF psfldr_new(PSFLDR_T *out_obj, const char *url, const char *head_query, const char *get_query, PSFLDR_CALLBACK callback,
		void *arg);
void FUNC_DEF psfldr_delete(PSFLDR_T _this);
void FUNC_DEF psfldr_poll(PSFLDR_T _this);
bool FUNC_DEF psfldr_get_pos(PSFLDR_T _this, const char *path, char *out_url, uint64_t *out_offset, uint64_t *out_length);

#ifdef __cplusplus

}

#endif
