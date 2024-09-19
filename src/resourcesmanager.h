#ifndef __RESOURCESMANAGER_H
#define __RESOURCESMANAGER_H

#include <unistd.h>

#include "shader.h"

/// TODO: resources preloading

// current working directory absolute path
static char __current_wd[512];

void rmanager_init(void);
// returns current working directory absolute path
const char *const rmanager_getdir();
char *rmanager_get_shader_path(const char* shader_name);

shader_t* rmanager_get_shader(GLenum type, const char* name);


#endif  // __RESOURCESMANAGER_H
