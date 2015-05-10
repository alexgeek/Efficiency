#ifndef CAMERAARCBALL_H
#define CAMERAARCBALL_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Camera.h"

class CameraArcBall : public Camera
{
    public:
        CameraArcBall(glm::vec3 position, glm::vec3 target);
        std::string get_name();
        glm::mat4 get_projection();
        glm::mat4 get_view();
        void update(GLFWwindow*);
    protected:
        glm::vec3 position_;
        glm::vec3 target_;
        const static glm::vec3 up_;
        const static float rotate_speed_;
        const static float move_speed_;
    private:
        glm::dvec2 mouse_;
        float time_;
};

#endif // CAMERAARCBALL_H

