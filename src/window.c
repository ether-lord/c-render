#include "window.h"

#include <stdbool.h>
#include <stdio.h>

#include "glad.h"

GLFWwindow* window_create(int width, int height, const char* title,
                          GLFWmonitor* monitor, GLFWwindow* share) {
  GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, share);
  if (!window) {
    fprintf(stderr, "Error: failed to open the window\n");
  }

  return window;
}

void window_set_current_context(GLFWwindow* window) {
  glfwMakeContextCurrent(window);
}

void window_close(GLFWwindow* window) {
  glfwDestroyWindow(window);
  glfwTerminate();
}

void window_glfw_init(void) {
  int glfw_init_status = glfwInit();
  int glfw_init_success = glfw_init_status == GLFW_TRUE;

  if (!glfw_init_success) {
    fprintf(stderr, "Error: failed to initialize GLFW\n");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
