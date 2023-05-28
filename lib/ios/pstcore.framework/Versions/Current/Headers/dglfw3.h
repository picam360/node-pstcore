
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#define DGLFW_DISPLAY_ID                0x00120001
#define DGLFW_PST                       0x00120002

#define DGLFW_SUBMODULE_GLFW            0
#define DGLFW_SUBMODULE_EMS             1
#define DGLFW_SUBMODULE_UNITY           2
#define DGLFW_SUBMODULE_ANDROID         3
#define DGLFW_SUBMODULE_IOS             4
#define DGLFW_N_SUBMODULES              5


#ifdef __cplusplus
extern "C" {
#endif

void dglfwSetSubmodule(int value);
int dglfwGetSubmodule();

int dglfwInit(void);
void dglfwTerminate(void);
void dglfwWindowHint(int hint, int value);
void dglfwWindowHintString(int hint, const char *value);
void dglfwPollEvents(void);
GLFWmonitor* dglfwGetPrimaryMonitor();
GLFWwindow *dglfwGetCurrentContext();

GLFWwindow* dglfwCreateWindow(int width, int height, const char *title,
		GLFWmonitor *monitor, GLFWwindow *share);
void dglfwDestroyWindow (GLFWwindow *_window);
void dglfwMakeContextCurrent(GLFWwindow *_window);
void dglfwSetWindowUserPointer(GLFWwindow *_window, void *user_data);
void* dglfwGetWindowUserPointer(GLFWwindow *_window);
void dglfwSwapBuffers(GLFWwindow *_window);
GLFWwindowsizefun dglfwSetWindowSizeCallback(GLFWwindow *_window, GLFWwindowsizefun callback);
const GLFWvidmode* dglfwGetVideoMode(GLFWmonitor *monitor);
void dglfwGetWindowSize(GLFWwindow *_window, int *width, int *height);
void dglfwSetWindowPos(GLFWwindow *window, int xpos, int ypos);
void dglfwSetWindowSize(GLFWwindow *_window, int width, int height);

void dglfwGetCursorPos(GLFWwindow* window, double* xpos, double* ypos);
void dglfwSetWindowAttrib(GLFWwindow* window, int attrib, int value);
int dglfwGetWindowAttrib(GLFWwindow* window, int attrib);
void dglfwFocusWindow(GLFWwindow* window);
void dglfwGetWindowContentScale(GLFWwindow* window, float* xscale, float* yscale);
GLFWcursorposfun dglfwSetCursorPosCallback(GLFWwindow* window, GLFWcursorposfun callback);
GLFWmousebuttonfun dglfwSetMouseButtonCallback(GLFWwindow* window, GLFWmousebuttonfun callback);
GLFWscrollfun dglfwSetScrollCallback(GLFWwindow* window, GLFWscrollfun callback);
GLFWkeyfun dglfwSetKeyCallback(GLFWwindow* window, GLFWkeyfun callback);

//extension start
void dglfwSetQuat(GLFWwindow *_window, float x, float y, float z, float w);
void dglfwGetCurrentQuat(GLFWwindow *_window, float *out_x, float *out_y, float *out_z, float *out_w);
void dglfwGetCurrentTex(GLFWwindow *_window, int *out_tex);
void dglfwViewport(GLFWwindow *_window, bool stereo, int eye_idx, int x, int y, int w, int h, bool from_right, bool from_top);
//extension end

#ifdef __cplusplus
}
#endif