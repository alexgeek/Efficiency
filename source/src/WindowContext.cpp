#include "WindowContext.h"

const std::string WindowContext::kDefaultWindowTitle = "Default Window";

WindowContext::WindowContext(int window_width, int window_height, std::string title) :
  title_(title),
  window_width_(window_width),
  window_height_(window_height),
  samples_(kDefaultSamples),
  stencil_bits_(kDefaultStencilBits),
  alpha_bits_(kDefaultAlphaBits),
  swap_interval_(kDefaultSwapInterval)
{}

WindowContext::WindowContext(int window_width, int window_height) :
  WindowContext(window_width, window_height, kDefaultWindowTitle)
{}

WindowContext::WindowContext() :
  WindowContext(kDefaultWindowWidth, kDefaultWindowHeight)
{}

WindowContext::~WindowContext() {
  glfwDestroyWindow(window_);
}

/**
 * Initialises a GLFW context and GLEW.
 */
int WindowContext::Init()
{
  return init_glfw() && init_glew() && init_gl();
}

void WindowContext::PrintContextInfo() {
  // get version info
  const GLubyte* gl_renderer = glGetString (GL_RENDERER); // get renderer string
  const GLubyte* gl_version = glGetString (GL_VERSION); // version as a string
  // get number of alpha bits if supported
  int gl_alpha;
  glGetIntegerv(GL_ALPHA_BITS, &gl_alpha);
  printf ("Renderer: %s\n", gl_renderer);
  printf ("OpenGL version supported %s\n", gl_version);
  printf ("Alphabits: %d", gl_alpha);
}

int WindowContext::init_glfw()
{
  int ret = glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, kGLVersionMajor);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, kGLVersionMinor);
  glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, kGLForwardCompat);
  // to use this: http://stackoverflow.com/questions/17923782/simple-opengl-image-library-soil-uses-deprecated-functionality
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_PROFILE,	GLFW_OPENGL_COMPAT_PROFILE);
  // set number of samples for AA
  if(samples_ > 0) glfwWindowHint(GLFW_SAMPLES, samples_);
  // request a stencil buffer for object selection
  if(stencil_bits_ > 0) glfwWindowHint(GLFW_STENCIL_BITS, stencil_bits_);
  // request a buffer for transparency
  if(alpha_bits_ > 0) glfwWindowHint(GLFW_ALPHA_BITS, alpha_bits_);
  window_ = create_window();
  glfwMakeContextCurrent(window_);
  glfwSwapInterval(swap_interval_);
  return ret;
}

int WindowContext::init_glew() {
  // start GLEW extension handler
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();

  if(err == GLEW_OK) {
    GLenum glErr = glGetError();
    if (glErr == GL_NO_ERROR) {
      return 1;
    } else {
      std::cout << "Caught GLEW Init error in GL" << std::endl;
      return 0;
    }
  } else {
    std::cout << "GLEW error: " << glewGetErrorString(err) << std::endl;
    return 0;
  }
}

int WindowContext::init_gl() {
  glClearColor(0.9f, 0.9f, 0.99f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0f);
  glDepthFunc(GL_LESS);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_CULL_FACE);
  return 1;
}

GLFWwindow* WindowContext::create_window()
{
  return glfwCreateWindow(window_width_, window_height_, title_.c_str(), NULL, NULL);
}
