#pragma once

#include "pglcore_common.h"

#include <stdbool.h>

#ifdef __cplusplus

class GLProgram {
public:
	GLProgram(const char *common, const char *vertex, const char *fragment);
	virtual ~GLProgram();

	GLuint GetId();
	operator GLuint() {
		return m_program_id;
	}
	;
private:
	GLuint m_vertex_id, m_fragment_id, m_program_id;
	const char *m_common;

	GLuint LoadShader(GLenum shader_type, const char *source);
};

extern "C" {

#endif

void *GLProgram_new(const char *common, const char *vertex, const char *fragment);
GLuint GLProgram_GetId(const void *_this);
void GLProgram_delete(const void *_this);

#ifdef __cplusplus
}
#endif
