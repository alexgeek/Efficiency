#ifndef WINDOW_H
#define WINDOW_H
#include <GLFW/glfw3.h>
#include <string>

#define DEFAULT_WINDOW_WIDTH 1024
#define DEFAULT_WINDOW_HEIGHT 768
#define DEFAULT_TITLE "GLFW3 Window"

class Window
{
public:
    Window();
    Window(int window_width, int window_height);
    Window(int window_width, int window_height, std::string title);
    void set_title(std::string title);
    std::string get_title();
    static bool init();
    GLFWwindow* create_window();
protected:
    static bool initialised_;
    GLFWwindow* window_;
    int window_width_;
    int window_height_;
    std::string title_;
private:
};

#endif
