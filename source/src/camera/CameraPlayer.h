#ifndef GAME_CAMERAPLAYER_H
#define GAME_CAMERAPLAYER_H

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Camera.h"

class CameraPlayer : public  Camera
{
public:
    CameraPlayer(glm::vec3 position);
    virtual glm::mat4 get_projection();
    virtual glm::mat4 get_view();
    virtual void update(GLFWwindow*);
private:
    glm::vec3 position_;
};

#endif //GAME_CAMERAPLAYER_H
