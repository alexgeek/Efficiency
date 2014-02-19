#include "utility.h"

bool restart_gl_log () {
  FILE* file = fopen (GL_LOG_FILE, "w+");
  if (!file) {
    fprintf (stderr, "ERROR: could not open %s log file for writing\n", GL_LOG_FILE);
    return false;
  }
  time_t now = time (NULL);
  char* date = ctime (&now);
  fprintf (file, "%s log. local time %s\n", GL_LOG_FILE, date);
  fclose (file);
  return true;
}

bool gl_log (const char* message, const char* filename, int line) {
  FILE* file = fopen (GL_LOG_FILE, "a+");
  if (!file) {
    fprintf (stderr, "ERROR: could not open %s for writing\n", GL_LOG_FILE);
    return false;
  }
  fprintf (file, "%s:%i %s\n", filename, line, message);
  fclose (file);
  return true;
}

void print(glm::dvec3 v)
{
    cout << v.x << ", " << v.y << ", " << v.z << endl;
}

void glfw_error_callback (int error, const char* description) {
    fputs (description, stderr);
    gl_log (description, __FILE__, __LINE__);
}

void _update_fps_counter (GLFWwindow* window) {
    static double previous_seconds = glfwGetTime ();
    static int frame_count;
    double current_seconds = glfwGetTime ();
    double elapsed_seconds = current_seconds - previous_seconds;
    if (elapsed_seconds > 0.25) {
        previous_seconds = current_seconds;
        double fps = (double)frame_count / elapsed_seconds;
        char tmp[128];
        sprintf (tmp, "opengl @ fps: %.2lf", fps);
        glfwSetWindowTitle (window, tmp);
        frame_count = 0;
    }
  frame_count++;
}
