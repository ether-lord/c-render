#ifndef __RESOURCESMANAGER_H
#define __RESOURCESMANAGER_H

#include <unistd.h>

// current working directory absolute path
static char __current_wd[512];

void resman_init(void);
// returns current working directory absolute path
const char *const resman_getdir();
char *resman_get_shader_path(const char* shader_name);

#endif  // __RESOURCESMANAGER_H
