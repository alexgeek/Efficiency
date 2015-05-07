#ifndef WINDOW_CONTEXT_H
#define WINDOW_CONTEXT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class WindowContext
{
public:
    const static int kGLVersionMajor = 4;
    const static int kGLVersionMinor = 0;
    const static int kGLForwardCompat = GL_TRUE;
    const static int kDefaultWindowWidth = 1024;
    const static int kDefaultWindowHeight = 768;
    const static std::string kDefaultWindowTitle;
    const static int kDefaultSamples = 4;
    const static int kDefaultAlphaBits = 8;
    const static int kDefaultStencilBits = 0;
    const static int kDefaultSwapInterval = 0;

    WindowContext();
    WindowContext(int window_width, int window_height);
    WindowContext(int window_width, int window_height, std::string title);
    ~WindowContext();
    int Init();
    void PrintContextInfo();

    /** accessors & mutators **/
    std::string title() const { return title_; }
    void set_title(std::string title) { title_ = title; }
    int samples() const { return samples_; }
    void set_samples(int samples) { samples_ = samples; }
    int alpha_bits() const { return alpha_bits_; }
    void set_alpha_bits(int bits) { alpha_bits_ = bits; }
    int stencil_bits() const { return stencil_bits_; }
    void set_stencil_bits(int bits) { stencil_bits_ = bits; }
    int swap_interval() const { return swap_interval_; }
    void set_swap_interval(int interval) { swap_interval_ = interval; }
    GLFWwindow* window() const { return window_; }

protected:
private:
    GLFWwindow* window_;
    int window_width_;
    int window_height_;
    std::string title_;
    int samples_;
    int alpha_bits_;
    int stencil_bits_;
    int swap_interval_;

    int init_glfw();
    int init_glew();
    int init_gl();
    GLFWwindow* create_window();

};

#endif
