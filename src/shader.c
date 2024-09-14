#include "shader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

shader_t* shader_create(GLenum type, const char* path_to_shader) {
  FILE* shader_file = fopen(path_to_shader, "r");
  if (!shader_file) {
    fprintf(stderr, "Failed to open the shader file by path: %s\n",
            path_to_shader);
  }

  char* buffer = NULL;
  size_t buffer_size = 0;
  size_t bytes_read = getdelim(&buffer, &buffer_size, '\0', shader_file);

  if (bytes_read == -1)
    fprintf(stderr, "Failed to read from shader file by path:%s\n",
            path_to_shader);

  fclose(shader_file);

  GLuint shader_id = glCreateShader(type);
  shader_t* shader = (shader_t*)malloc(sizeof(shader_t));
  *shader = (shader_t){.id = shader_id, .type = type, .source = buffer};

  glShaderSource(shader->id, 1, &shader->source, NULL);

  return shader;
}

// returns -1 if compilation failed
int shader_compile_by_id(GLuint shader_id) {
  glCompileShader(shader_id);

  int compile_status;
  char infoLog[512];
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);
  return compile_status;
}

void shader_delete_by_id(GLuint shader_id) {
  glDeleteShader(shader_id);
}
