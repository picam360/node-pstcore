#pragma once

#include "pglcore_common.h"

#ifdef __cplusplus

extern "C" {

#endif

void FUNC_DEF pglf2s_init(GLuint width, GLuint height,
                          const char *lens_params,
                          GLfloat fov, GLfloat edge_r, GLfloat gain_theta);
void FUNC_DEF pglf2s_set_rot_quat(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
void FUNC_DEF pglf2s_set_fov(GLfloat fov);
void FUNC_DEF pglf2s_set_view_size(GLuint width, GLuint height);
void FUNC_DEF pglf2s_set_target_fps(GLfloat fps);
void FUNC_DEF pglf2s_set_lens_params(const char *lens_params, bool update_mesh);
void FUNC_DEF pglf2s_render(TextureParams *tpo, GLfloat *quat);

void FUNC_DEF f2s_reproject_point(float fov, float *view_quat, //
                         float x, float y, float *out_x, float *out_y, bool);
#ifdef __cplusplus

}

#endif
