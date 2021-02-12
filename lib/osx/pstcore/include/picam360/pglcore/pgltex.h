#pragma once

#include "pglcore_common.h"

#ifdef __cplusplus

extern "C" {

#endif

typedef void* PGLTEX;

void FUNC_DEF pgltex_create(PGLTEX *obj);
void FUNC_DEF pgltex_render(PGLTEX obj, TextureParams *tpo, GLfloat *quat);
void FUNC_DEF pgltex_delete(PGLTEX obj);

#ifdef __cplusplus

}

#endif
