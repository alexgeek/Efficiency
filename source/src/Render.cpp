#include "Camera.h"

glm::mat4 Camera::default_projection()
{
    return glm::transpose(glm::frustum(-1.0f,1.0f,-1.0f,1.0f,5.0f,150.0f));
}
