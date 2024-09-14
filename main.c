#define GLFW_INCLUDE_NONE

#include <stdio.h>

#include "glad.h"
#include "window.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {
  window_glfw_init();

  GLFWwindow* window = window_create(640, 480, "crender", NULL, NULL);
  window_set_current_context(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fprintf(stderr, "Failed to initialize GLAD\n");
    return -1;
  }

  glfwSetKeyCallback(window, key_callback);

  while (!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  window_close(window);

  return 0;
}