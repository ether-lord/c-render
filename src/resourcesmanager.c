#include "resourcesmanager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHADERS_EXTENTION ".glsl"
#define RES_DIR "/res"
#define SHADERS_DIR "/res/shaders/"

void rmanager_init(void) { getcwd(__current_wd, 256); }

const char *const rmanager_getdir() { return __current_wd; }

char *rmanager_get_shader_path(const char *shader_name) {
  size_t abs_path_size = (strlen(__current_wd) + strlen(shader_name) + 1 +
                          strlen(SHADERS_EXTENTION) + strlen(SHADERS_DIR)) *
                         sizeof(char);
  char *shader_abs_path = malloc(abs_path_size);
  memset(shader_abs_path, 0, abs_path_size);

  strcat(shader_abs_path, __current_wd);
  strcat(shader_abs_path, SHADERS_DIR);
  strcat(shader_abs_path, shader_name);
  strcat(shader_abs_path, SHADERS_EXTENTION);

  return shader_abs_path;
}

shader_t *rmanager_get_shader(GLenum type, const char *name) {
  char *shader_absolute_path = rmanager_get_shader_path(name);
  shader_t *shader = shader_create(type, shader_absolute_path);
  free(shader_absolute_path);
  return shader;
}
