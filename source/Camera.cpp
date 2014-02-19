#include "Camera.h"


// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
glm::mat4 Camera::default_projection()
{
//    return glm::transpose(glm::frustum(-1.0f,1.0f,-1.0f,1.0f,5.0f,150.0f));
    return (glm::perspective(
        45.0f, 4.0f / 3.0f, 1.0f, 50.0f
    ));
}
