#pragma once

//
//this is a interface for pplugins
//

#if defined(__EMSCRIPTEN__)
#include <emscripten/emscripten.h>
#define FUNC_DEF EMSCRIPTEN_KEEPALIVE
#else
#define FUNC_DEF
#endif

#include "pstreamer.h"

#ifdef __cplusplus

extern "C" {

#endif

#define PSTHOST_EVENT_POLL_EVENTS_CALLED 1
typedef void (*PSTHOST_EVENT_CALLBACK)(void *arg);
typedef struct _PSTHOST_T PSTHOST_T;
typedef void (*PSTHOST_SET_PARAM_DONE_CALLBACK)(const char *pst_name,
		const char *param, const char *value, void *arg);
struct _PSTHOST_T {
	PSTREAMER_T* (*build_pstreamer)(PSTHOST_T *obj, uint8_t *uuid,
			const char *_buff);
	PSTREAMER_T* (*get_streamer)(PSTHOST_T *obj, PSTREAMER_T *pst, int idx);
	bool (*destroy_pstreamer)(PSTHOST_T *obj, PSTREAMER_T *pst);
	void (*add_pstreamer_factory)(PSTHOST_T *obj, PSTREAMER_FACTORY_T *factory);

	void (*add_event_callback)(PSTHOST_T *obj, int event,
			PSTHOST_EVENT_CALLBACK callback, void *arg);
    void (*remove_event_callback)(PSTHOST_T *obj, int event,
            PSTHOST_EVENT_CALLBACK callback, void *arg);
	void (*poll_events)(PSTHOST_T *obj);

	bool (*start_pstreamer)(PSTHOST_T *obj, PSTREAMER_T *st);
	bool (*stop_pstreamer)(PSTHOST_T *obj, PSTREAMER_T *st);

	bool (*set_param)(PSTHOST_T *obj, PSTREAMER_T *st, const char *pst_name,
			const char *param, const char *value);
	bool (*get_param)(PSTHOST_T *obj, PSTREAMER_T *st, const char *pst_name,
			const char *param, char *value, int size);
	void (*add_set_param_done_callback)(PSTHOST_T *obj,
			PSTHOST_SET_PARAM_DONE_CALLBACK callback, void *arg);
    void (*remove_set_param_done_callback)(PSTHOST_T *obj,
            PSTHOST_SET_PARAM_DONE_CALLBACK callback, void *arg);
};

PSTHOST_T* build_pstreamer_host();
void destory_pstreamer_host(PSTHOST_T *obj);

#ifdef __cplusplus

}

#endif
