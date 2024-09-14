#ifndef __WINDOW_H
#define __WINDOW_H

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>

void window_glfw_init(void);

// monitor and share can be NULL
GLFWwindow* window_create(int width, int height, const char* title,
                          GLFWmonitor* monitor, GLFWwindow* share);

void window_set_current_context(GLFWwindow* window);

void window_close(GLFWwindow* window);

#endif  // __WINDOW_H