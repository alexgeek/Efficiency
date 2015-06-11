#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
    public:
        virtual glm::mat4 GetProjection() = 0;
        virtual glm::mat4 GetView() = 0;
        virtual void Update(GLFWwindow *) = 0;
    protected:
        glm::mat4 default_projection();
    private:
};

#endif // CAMERA_H

