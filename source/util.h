#ifdef __cplusplus
extern "C" {
#endif
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include "SOIL.h"

double calcFPS(double time);
void glfw_error_callback(int error, const char* description);
int load_texture();
int screenshot();

#ifdef __cplusplus
}
#endif
