#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

int print_gl_error(char const* file, int line);
//#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define printOpenGLError() print_gl_error(__FILE__, __LINE__)
