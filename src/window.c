#include "window.h"

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad.h>

#include <stdbool.h>
#include <stdio.h>

void window_init(void) {
  int glfw_init_status = glfwInit();
  int glfw_init_success = glfw_init_status == GLFW_TRUE;

  if (!glfw_init_success) {
    fprintf(stderr, "Error: failed to initialize GLFW");
  }
}