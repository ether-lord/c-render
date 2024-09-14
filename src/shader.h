#ifndef __SHADER_H
#define __SHADER_H

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>

#include "glad.h"

typedef struct _shader {
  GLuint id;
  GLenum type;

  const char* source;
} shader_t;

shader_t* shader_create(GLenum type, const char* path_to_shader);

int shader_compile_by_id(GLuint shader_id);
void shader_delete_by_id(GLuint shader_id);


#endif  // __SHADER_H