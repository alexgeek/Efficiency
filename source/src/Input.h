#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdio.h>
#include <iostream>

using namespace std;

class Input
{
    public:   
        static Input& Instance()
        {
            static Input instance;
            return instance;
        }
        static void glfw_character_callback(GLFWwindow*, unsigned int);
        static void glfw_key_callback(GLFWwindow*, int key, int scancode, int action, int mods);
        void onKeyPress(GLFWwindow*, int key, int scancode, int action, int mods);
        void onTextEntered(GLFWwindow*, unsigned int);
        void update(GLFWwindow* window);
        glm::dvec2 get_mouse_position();
        glm::dvec2 get_mouse_delta();
    protected:
        glm::dvec2 mouse_position_;
        glm::dvec2 mouse_delta_;
    private:
        Input(void);
        Input(Input const&); // prevent copies
        void operator=(Input const&); // prevent assignments
        ~Input() {};
};

#endif // INPUT_H
