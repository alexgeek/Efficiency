#ifndef DEFAULT_H
#define DEFAULT_H
#define DEBUG
#include <GL/glew.h>
#include <GLFW/glfw3.h>         // core window handling
#include <glm/gtc/matrix_transform.hpp> // rotate etc
#include <glm/gtc/type_ptr.hpp> // replace with macro for glm to and from opengl                    
#include <iostream>             // want cout, endl everywhere
#include "Input.h"
using namespace std;

extern "C"
{
    #include "utility.h"
}

void CheckOpenGLError(const char* stmt, const char* fname, int line)
{
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        printf("OpenGL error %08x, at %s:%i - for %s\n", err, fname, line, stmt);
        abort();
    }
}

#ifdef DEBUG
    #define GL_CHECK(stmt) do { \
            stmt; \
            CheckOpenGLError(#stmt, __FILE__, __LINE__); \
        } while (0)
#else
    #define GL_CHECK(stmt) stmt
#endif

#endif
