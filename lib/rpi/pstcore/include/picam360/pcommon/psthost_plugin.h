#pragma once
#include "psthost.h"

#ifdef __cplusplus

extern "C" {

#endif

typedef void (*PFN_PSTHOST_PLUGIN)(PSTHOST_T *host, const char *self_path);
void FUNC_DEF connect_psthost_plugin(PSTHOST_T *host, const char *self_path);

#ifdef __cplusplus

}

#endif
