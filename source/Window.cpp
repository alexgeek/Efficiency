#include "Window.h"

bool Window::initialised_ = false;

Window::Window(int window_width, int window_height, std::string title) :
    title_(title),
    window_width_(window_width),
    window_height_(window_height)
{
}

Window::Window(int window_width, int window_height) :
    Window(window_width, window_height, DEFAULT_TITLE)
{}

Window::Window() :
    Window(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_WIDTH)
{}

bool Window::init()
{
    return glfwInit();
}

GLFWwindow* Window::create_window()
{
    if(!Window::initialised_)
        Window::init();
    if(Window::initialised_)
    {
        window_ = glfwCreateWindow(window_width_, window_height_, title_.c_str(), NULL, NULL);
        glfwMakeContextCurrent(window_);
    }
    else
    {
        glfwTerminate();
    }
    return window_;
}

/* Accessors */

void Window::set_title(std::string title)
{
    title_ = title;
}

std::string Window::get_title()
{
    return title_;
}
