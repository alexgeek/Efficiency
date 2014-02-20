#include "default.h"
int printOglError(char const* file, int line);
#define printOpenGLError() printOglError(__FILE__, __LINE__)
