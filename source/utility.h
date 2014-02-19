#ifndef UTILITY_H
#define UTILITY_H
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <time.h>
#define GL_LOG_FILE "gl.log"

using namespace std;

bool restart_gl_log ();
bool gl_log (const char* message, const char* filename, int line);
void print(glm::dvec3 v);
void glfw_error_callback (int error, const char* description);
void _update_fps_counter (GLFWwindow* window);

#endif
