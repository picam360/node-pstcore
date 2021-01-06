#pragma once

//---
#if defined(__EMSCRIPTEN__)

#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/threading.h>

//-----
#if WEBGL_VERSION == 2
#define GLFW_INCLUDE_ES3
#else
#define GLFW_INCLUDE_ES2
#endif
//-----

#include <GLFW/glfw3.h>
#include <GLES3/gl3.h>

#else//end of #if defined(__EMSCRIPTEN__)

//-----
//#if !defined(DGLFW)
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
//#else
//typedef struct GLFWwindow GLFWwindow;
//typedef struct GLFWmonitor GLFWmonitor;
//#endif
//-----

//-----
#if defined(USE_GLEW)
#include <GL/glew.h>
//end of #elif !defined(DGLFW)
#elif defined(ANDROID)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#else
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#endif
//-----

#endif

#if defined(__EMSCRIPTEN__)
#define FUNC_DEF EMSCRIPTEN_KEEPALIVE
#else
#define FUNC_DEF
#endif

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifdef __cplusplus

extern "C" {

#endif

#define PGLCORE_EVENT_BEFORE_DRAW_EVENTS_CALLED 1
#define PGLCORE_EVENT_DRAW_EVENTS_CALLED 2
#define PGLCORE_EVENT_AFTER_DRAW_EVENTS_CALLED 3
typedef void (*PGLCORE_EVENT_CALLBACK)(void *arg);

void FUNC_DEF pglcore_init(GLuint width, GLuint height);
void FUNC_DEF pglcore_swap_buffer();
GLFWwindow* FUNC_DEF pglcore_get_current_window();
void FUNC_DEF pglcore_set_window_size(GLuint width, GLuint height);
void FUNC_DEF pglcore_set_event_callback(int event,
        PGLCORE_EVENT_CALLBACK callback, void *arg);
void FUNC_DEF pglcore_draw();
void FUNC_DEF pglcore_fullscreen(GLFWwindow* window);

void FUNC_DEF pglcore_lock();
void FUNC_DEF pglcore_unlock();

#ifdef __cplusplus

}

#endif
