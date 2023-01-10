#pragma once

//
//this is a interface for library caller (especially javascript via emscripten)
//this should not be included from plugins in order to avoid complexity
//

#include "psthost.h"

#ifdef __cplusplus

extern "C" {

#endif

#define PSTCORE_LOG_DEBUG -1
#define PSTCORE_LOG_INFO 0
#define PSTCORE_LOG_WARN 1
#define PSTCORE_LOG_ERROR 2

void FUNC_DEF pstcore_init(const char *config_json);
void FUNC_DEF pstcore_deinit();
PSTHOST_T* FUNC_DEF pstcore_get_psthost();
PSTREAMER_T* FUNC_DEF pstcore_build_pstreamer(const char *def);
void FUNC_DEF pstcore_poll_events();

void FUNC_DEF pstcore_set_view_quat(PSTREAMER_T *pst, float x, float y, float z,
		float w);
void FUNC_DEF pstcore_set_param(PSTREAMER_T *pst, const char *pst_name,
		const char *param, const char *value);
void FUNC_DEF pstcore_get_param(PSTREAMER_T *pst, const char *pst_name,
		const char *param, char *value, int size);

void FUNC_DEF pstcore_add_set_param_done_callback(PSTREAMER_T *pst,
		PSTHOST_SET_PARAM_DONE_CALLBACK callback, void *arg);
void FUNC_DEF pstcore_remove_set_param_done_callback(PSTREAMER_T *pst,
		PSTHOST_SET_PARAM_DONE_CALLBACK callback, void *arg);

void FUNC_DEF pstcore_start_pstreamer(PSTREAMER_T *pst);
void FUNC_DEF pstcore_stop_pstreamer(PSTREAMER_T *pst);
void FUNC_DEF pstcore_enqueue(PSTREAMER_T *pst, unsigned char *buff, int size);
void FUNC_DEF pstcore_dequeue(PSTREAMER_T *pst, unsigned char **out_buff,
		int *out_size);
void FUNC_DEF pstcore_set_fill_buffer_done_callback(PSTREAMER_T *pst,
		FILL_BUFFER_DONE_CALLBACK callback, void *arg);
void FUNC_DEF pstcore_destroy_pstreamer(PSTREAMER_T *pst);

void FUNC_DEF pstcore_add_log_callback(PSTHOST_LOG_CALLBACK callback, void *arg);
void FUNC_DEF pstcore_remove_log_callback(PSTHOST_LOG_CALLBACK callback, void *arg);
void FUNC_DEF pstcore_log(int level, const char* tag, const char* msg);
void FUNC_DEF pstcore_logf(int level, const char* tag, const char* format, ...);

#ifdef __cplusplus

}

#endif
