#include "CameraArcBall.h"

const glm::vec3 CameraArcBall::up_ = glm::vec3(0, 1.0f, 0);
const float CameraArcBall::rotate_speed_ = 0.15f;
const float CameraArcBall::move_speed_ = 5.0f;

CameraArcBall::CameraArcBall(glm::vec3 position, glm::vec3 target) :
    position_(position),
    target_(target)
{
}

glm::mat4 CameraArcBall::GetProjection()
{
    return default_projection();
}

glm::mat4 CameraArcBall::GetView()
{
    return glm::lookAt(position_, target_, up_);
}

// http://gamedev.stackexchange.com/questions/53333/how-to-implement-a-basic-arcball-ActiveCamera-in-opengl-with-glm
void CameraArcBall::Update(GLFWwindow *window)
{
    float now = glfwGetTime();
    float delta = now - time_;
    time_ = now;

    // get difference between last mouse coordinates and current
    glm::dvec2 mouse_delta = mouse_;
    glfwGetCursorPos(window, &mouse_.x, &mouse_.y);
    mouse_delta -= mouse_;

    float pitch, yaw = 0;

    /*if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
    {*/
        glm::mat4 view = GetView();
        glm::vec3 camera_right = glm::vec3(view[0][0], view[1][0], view[2][0]);
        if(mouse_delta.y != 0)
            position_ = glm::rotate(position_ - target_, rotate_speed_ * (float)mouse_delta.y, camera_right) + target_;
        glm::vec3 camera_up = glm::vec3(view[0][1], view[1][1], view[2][1]);
        if(mouse_delta.x != 0)
            position_ = glm::rotate(position_ - target_, rotate_speed_ * (float)mouse_delta.x, camera_up) + target_;
    //}

    glm::vec3 movef = move_speed_ * glm::normalize(target_ - position_) * delta;

    glm::vec3 pt = position_ - target_;
    // zoom in
    if(glfwGetKey(window, '='))
        position_ += movef;
    // zoom out
    if(glfwGetKey(window, '-'))
        position_ -= movef;


    // move forward
    if(glfwGetKey(window, 'W'))
    {
        position_ += movef;
        target_ += movef;
    }
    // move back
    if(glfwGetKey(window, 'S'))
    {
        position_ -= movef;
        target_ -= movef;
    }

    // side to side
    glm::vec3 strafe = move_speed_ * glm::cross(glm::normalize(target_ - position_), up_) * delta;
    if(glfwGetKey(window, 'A'))
    {
        position_ -= strafe;
        target_ -= strafe;
    }
    if(glfwGetKey(window, 'D'))
    {
        position_ += strafe;
        target_ += strafe;
    }

    // up and down
    glm::vec3 vert = move_speed_ * up_ * delta;
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
    {
        position_ -= vert;
        target_ -= vert;
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE))
    {
        position_ += vert;
        target_ += vert;
    }
}
