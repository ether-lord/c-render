#include "shader.h"

#include <stdio.h>
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

  GLuint shader_id = glCreateShader(type);
  shader_t* shader = (shader_t*)malloc(sizeof(shader_t));
  *shader = (shader_t){
      .id = shader_id, .type = type, .path = path_to_shader, .source = buffer};

  return shader;
}
