#pragma once

#include "pglcore_common.h"

#ifdef __cplusplus

extern "C" {

#endif

void FUNC_DEF pglf2p_init(GLuint width, GLuint height,
                          const char *lens_params,
                          GLfloat fov, GLfloat edge_r, GLfloat gain_theta);
void FUNC_DEF pglf2p_set_rot_quat(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
void FUNC_DEF pglf2p_set_fov(GLfloat fov);
void FUNC_DEF pglf2p_set_view_size(GLuint width, GLuint height);
void FUNC_DEF pglf2p_set_target_fps(GLfloat fps);
void FUNC_DEF pglf2p_set_lens_params(const char *lens_params);
void FUNC_DEF pglf2p_render(TextureParams *tpo, GLfloat *quat);

#ifdef __cplusplus

}

#endif
