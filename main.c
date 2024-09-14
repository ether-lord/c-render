#define GLFW_INCLUDE_NONE

#include <stdio.h>

#include "glad.h"
#include "shader.h"
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

  float vertices[] = {-0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f};

  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and
  // then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(VAO);

  shader_t* vertex_shader =
      shader_create(GL_VERTEX_SHADER, "../res/vertex.glsl");
  shader_t* fragment_shader =
      shader_create(GL_FRAGMENT_SHADER, "../res/fragment.glsl");

  shader_compile_by_id(vertex_shader->id);
  shader_compile_by_id(fragment_shader->id);

  /// TODO: implement shader program

  unsigned int shader_program;
  shader_program = glCreateProgram();

  glAttachShader(shader_program, vertex_shader->id);
  glAttachShader(shader_program, fragment_shader->id);
  glLinkProgram(shader_program);

  glUseProgram(shader_program);

  while (!glfwWindowShouldClose(window)) {
    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // render the triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
    // etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  window_close(window);

  return 0;
}