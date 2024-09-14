#include "shaderprogram.h"

#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "glad.h"

shader_program_t* program_create(shader_t* vertex_sh, shader_t* fragment_sh) {
  GLuint program_id = glCreateProgram();
  glAttachShader(program_id, vertex_sh->id);
  glAttachShader(program_id, fragment_sh->id);
  glLinkProgram(program_id);

  shader_program_t* shader_program =
      (shader_program_t*)malloc(sizeof(shader_program_t));
  *shader_program = (shader_program_t){.id = program_id,
                                       .vertex_shader = vertex_sh,
                                       .fragment_shader = fragment_sh};
  return shader_program;
}

void program_use(shader_program_t* program) { glUseProgram(program->id); }

void program_destroy(shader_program_t* program) {
  shader_delete_by_id(program->vertex_shader->id);
  shader_delete_by_id(program->fragment_shader->id);
  glDeleteProgram(program->id);
}
