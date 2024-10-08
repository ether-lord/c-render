#define STB_IMAGE_IMPLEMENTATION
#define GLFW_INCLUDE_NONE

#include <math.h>
#include <stdio.h>

#include "cglm/cglm.h"
#include "glad.h"
#include "resourcesmanager.h"
#include "shader.h"
#include "shaderprogram.h"
#include "stb_image.h"
#include "window.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {
  window_glfw_init();
  rmanager_init();

  GLFWwindow* window = window_create(1024, 640, "crender", NULL, NULL);
  window_set_current_context(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fprintf(stderr, "Failed to initialize GLAD\n");
    return -1;
  }

  glfwSetKeyCallback(window, key_callback);

  float vertices[] = {
      // positions                  // texture coords
      0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // top right
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // bottom left
      -0.5f, 0.5f,  0.0f, 0.0f, 1.0f   // top left
  };

  unsigned int indices[] = {
      0, 1, 3,  // first triangle
      1, 2, 3   // second triangle
  };

  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  shader_t* vertex_shader = rmanager_load_shader(GL_VERTEX_SHADER, "vertex");
  shader_t* fragment_shader =
      rmanager_load_shader(GL_FRAGMENT_SHADER, "fragment");

  shader_compile_by_id(vertex_shader->id);
  shader_compile_by_id(fragment_shader->id);

  shader_program_t* program = program_create(vertex_shader, fragment_shader);
  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  // set the texture wrapping/filtering options (on the currently bound texture
  // object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // load and generate the texture
  stbi_set_flip_vertically_on_load(1);
  int width, height, nrChannels;
  unsigned char* data =
      stbi_load("/home/ether/workspace/c-render/res/textures/container.jpg",
                &width, &height, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    printf("%s\n", "Failed to load the texture");
  }
  stbi_image_free(data);

  program_use(program);

  mat4 transform = GLM_MAT4_IDENTITY_INIT;

  unsigned int transformLoc = glGetUniformLocation(program->id, "transform");

  while (!glfwWindowShouldClose(window)) {
    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // render the triangle
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glm_mat4_identity(transform);
    glm_translate(transform, (vec3){0.5f, -0.5f, 0.0f});
    glm_rotate(transform, (float)glfwGetTime(), (vec3){0.0f, 0.0f, 1.0f});

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, transform[0]);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
    // etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  program_destroy(program);
  window_close(window);
  
  return 0;
}