#ifndef __SHADERPROGRAM_H
#define __SHADERPROGRAM_H

#include "shader.h"

typedef struct shader_program {
  GLuint id;

  shader_t* vertex_shader;
  shader_t* fragment_shader;
} shader_program_t;

shader_program_t* program_create(shader_t* vertex_sh, shader_t* fragment_sh);
void program_use(shader_program_t* program);
void program_destroy(shader_program_t* program);

#endif  // __SHADERPROGRAM_H
