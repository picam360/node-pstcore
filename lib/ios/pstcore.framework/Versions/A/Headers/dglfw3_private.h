#include "dglfw3.h"

typedef struct DGLFWSubmodule{
    int (*dglfwInit)(void);
    void (*dglfwTerminate)(void);
    void (*dglfwWindowHint)(int hint, int value);
    void (*dglfwWindowHintString)(int hint, const char *value);
    void (*dglfwPollEvents)(void);
    GLFWmonitor* (*dglfwGetPrimaryMonitor)();
    GLFWwindow* (*dglfwGetCurrentContext)();

    GLFWwindow* (*dglfwCreateWindow)(int width, int height, const char *title,
            GLFWmonitor *monitor, GLFWwindow *share);
    void (*dglfwDestroyWindow)(GLFWwindow *_window);
    void (*dglfwMakeContextCurrent)(GLFWwindow *_window);
    void (*dglfwSetWindowUserPointer)(GLFWwindow *_window, void *user_data);
    void* (*dglfwGetWindowUserPointer)(GLFWwindow *_window);
    void (*dglfwSwapBuffers)(GLFWwindow *_window);
    GLFWwindowsizefun (*dglfwSetWindowSizeCallback)(GLFWwindow *_window, GLFWwindowsizefun callback);
    const GLFWvidmode* (*dglfwGetVideoMode)(GLFWmonitor *monitor);
    void (*dglfwGetWindowSize)(GLFWwindow *_window, int *width, int *height);
    void (*dglfwSetWindowPos)(GLFWwindow *window, int xpos, int ypos);
    void (*dglfwSetWindowSize)(GLFWwindow *_window, int width, int height);

    void (*dglfwGetCursorPos)(GLFWwindow* window, double* xpos, double* ypos);
    void (*dglfwSetWindowAttrib)(GLFWwindow* window, int attrib, int value);
    int (*dglfwGetWindowAttrib)(GLFWwindow* window, int attrib);
    void (*dglfwFocusWindow)(GLFWwindow* window);
    void (*dglfwGetWindowContentScale)(GLFWwindow* window, float* xscale, float* yscale);
    GLFWcursorposfun (*dglfwSetCursorPosCallback)(GLFWwindow* window, GLFWcursorposfun callback);
    GLFWmousebuttonfun (*dglfwSetMouseButtonCallback)(GLFWwindow* window, GLFWmousebuttonfun callback);
    GLFWscrollfun (*dglfwSetScrollCallback)(GLFWwindow* window, GLFWscrollfun callback);
    GLFWkeyfun (*dglfwSetKeyCallback)(GLFWwindow* window, GLFWkeyfun callback);

    void (*dglfwSetQuat)(GLFWwindow *_window, float x, float y, float z, float w);
    void (*dglfwGetCurrentQuat)(GLFWwindow *_window, float *out_x, float *out_y, float *out_z, float *out_w);
    void (*dglfwGetCurrentTex)(GLFWwindow *_window, int *out_tex);
}DGLFWSubmodule;

#define SET_SUBMODULE_FUNC(obj, sbname) {\
    (obj)->dglfwInit = dglfwInit_ ## sbname;\
    (obj)->dglfwTerminate = dglfwTerminate_ ## sbname;\
    (obj)->dglfwWindowHint = dglfwWindowHint_ ## sbname;\
    (obj)->dglfwWindowHintString = dglfwWindowHintString_ ## sbname;\
    (obj)->dglfwPollEvents = dglfwPollEvents_ ## sbname;\
    (obj)->dglfwGetPrimaryMonitor = dglfwGetPrimaryMonitor_ ## sbname;\
    (obj)->dglfwGetCurrentContext = dglfwGetCurrentContext_ ## sbname;\
    /**/\
    (obj)->dglfwCreateWindow = dglfwCreateWindow_ ## sbname;\
    (obj)->dglfwDestroyWindow = dglfwDestroyWindow_ ## sbname;\
    (obj)->dglfwMakeContextCurrent = dglfwMakeContextCurrent_ ## sbname;\
    (obj)->dglfwSetWindowUserPointer = dglfwSetWindowUserPointer_ ## sbname;\
    (obj)->dglfwGetWindowUserPointer = dglfwGetWindowUserPointer_ ## sbname;\
    (obj)->dglfwSwapBuffers = dglfwSwapBuffers_ ## sbname;\
    (obj)->dglfwSetWindowSizeCallback = dglfwSetWindowSizeCallback_ ## sbname;\
    (obj)->dglfwGetVideoMode = dglfwGetVideoMode_ ## sbname;\
    (obj)->dglfwGetWindowSize = dglfwGetWindowSize_ ## sbname;\
    (obj)->dglfwSetWindowPos = dglfwSetWindowPos_ ## sbname;\
    (obj)->dglfwSetWindowSize = dglfwSetWindowSize_ ## sbname;\
    /**/\
    (obj)->dglfwGetCursorPos = dglfwGetCursorPos_ ## sbname;\
    (obj)->dglfwSetWindowAttrib = dglfwSetWindowAttrib_ ## sbname;\
    (obj)->dglfwGetWindowAttrib = dglfwGetWindowAttrib_ ## sbname;\
    (obj)->dglfwFocusWindow = dglfwFocusWindow_ ## sbname;\
    (obj)->dglfwGetWindowContentScale = dglfwGetWindowContentScale_ ## sbname;\
    (obj)->dglfwSetCursorPosCallback = dglfwSetCursorPosCallback_ ## sbname;\
    (obj)->dglfwSetMouseButtonCallback = dglfwSetMouseButtonCallback_ ## sbname;\
    (obj)->dglfwSetScrollCallback = dglfwSetScrollCallback_ ## sbname;\
    (obj)->dglfwSetKeyCallback = dglfwSetKeyCallback_ ## sbname;\
    /**/\
    (obj)->dglfwSetQuat = dglfwSetQuat_ ## sbname;\
    (obj)->dglfwGetCurrentQuat = dglfwGetCurrentQuat_ ## sbname;\
    (obj)->dglfwGetCurrentTex = dglfwGetCurrentTex_ ## sbname;\
}
