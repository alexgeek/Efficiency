#include "Input.h"

Input::Input(void) : 
    mouse_position_(glm::dvec2(0)),
    mouse_delta_(glm::dvec2(0))
{
}

void Input::glfw_character_callback(GLFWwindow* window, unsigned int codepoint)
{
    instance().onTextEntered(window, codepoint);
}
void Input::glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    instance().onKeyPress(window, key, scancode, action, mods);
}

void Input::onKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}

void Input::onTextEntered(GLFWwindow* window, unsigned int key)
{

}

glm::dvec2 Input::get_mouse_position()
{
    return mouse_position_;
}

glm::dvec2 Input::get_mouse_delta()
{
    return mouse_delta_;
}

void Input::update(GLFWwindow* window)
{
    // get difference between last mouse coordinates and current
    mouse_delta_ = mouse_position_;
    glfwGetCursorPos(window, &mouse_position_.x, &mouse_position_.y);
    mouse_delta_ -= mouse_position_;
}
