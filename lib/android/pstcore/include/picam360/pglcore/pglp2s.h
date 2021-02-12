#pragma once

#include "pglcore_common.h"

#ifdef __cplusplus

extern "C" {

#endif

void FUNC_DEF pglp2s_init(GLuint width, GLuint height);
void FUNC_DEF pglp2s_set_texture(
		GLubyte **data_ary, GLuint *width_ary, GLuint *stride_ary, GLuint *height_ary,
		GLfloat *rot_quat, GLfloat fov, GLfloat edge_r, GLfloat gain_theta);
void FUNC_DEF pglp2s_set_rot_quat(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
void FUNC_DEF pglp2s_set_fov(GLfloat fov);
void FUNC_DEF pglp2s_set_stereo(GLboolean stereo);
void FUNC_DEF pglp2s_set_view_rot_quat(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
void FUNC_DEF pglp2s_set_view_fov(GLfloat fov);
void FUNC_DEF pglp2s_set_view_stereo(GLboolean stereo);
void FUNC_DEF pglp2s_set_view_size(GLuint width, GLuint height);
void FUNC_DEF pglp2s_set_mode(GLuint mode);
void FUNC_DEF pglp2s_set_target_fps(GLfloat fps);
void FUNC_DEF pglp2s_set_lens_params(float *k, float *f);
void FUNC_DEF pglp2s_render();
void FUNC_DEF pglp2s_deinit();

#ifdef __cplusplus

}

#endif
