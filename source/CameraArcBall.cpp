#include "CameraArcBall.h"

const glm::vec3 CameraArcBall::up_ = glm::vec3(0, 1.0f, 0);
const float CameraArcBall::rotate_speed_ = 0.15f;
const float CameraArcBall::move_speed_ = 0.15f;

CameraArcBall::CameraArcBall(glm::vec3 position, glm::vec3 target) :
    position_(position),
    target_(target)
{
}

std::string get_name()
{
    return "CameraArcBall";
}

glm::mat4 CameraArcBall::get_projection()
{
    return default_projection();
}

glm::mat4 CameraArcBall::get_view()
{
    return glm::lookAt(position_, target_, up_);
}

// http://gamedev.stackexchange.com/questions/53333/how-to-implement-a-basic-arcball-camera-in-opengl-with-glm
void CameraArcBall::update(GLFWwindow* window)
{
    // get difference between last mouse coordinates and current
    glm::dvec2 mouse_delta = mouse_;
    glfwGetCursorPos(window, &mouse_.x, &mouse_.y);
    mouse_delta -= mouse_;

    float pitch, yaw = 0;
    
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
    {
        glm::mat4 view = get_view();
        glm::vec3 camera_right = glm::vec3(view[0][0], view[1][0], view[2][0]);
        if(mouse_delta.y != 0)
            position_ = glm::rotate(position_ - target_, rotate_speed_ * (float)mouse_delta.y, camera_right) + target_;
        glm::vec3 camera_up = glm::vec3(view[0][1], view[1][1], view[2][1]);
        if(mouse_delta.x != 0)
            position_ = glm::rotate(position_ - target_, rotate_speed_ * (float)mouse_delta.x, camera_up) + target_;
    }
    
    // forward    
    if(glfwGetKey(window, 'W'))
        position_ += move_speed_ * glm::normalize(target_ - position_);
    // back
    if(glfwGetKey(window, 'S'))
        position_ -= move_speed_ * glm::normalize(target_ - position_);
    
    // side to side
    glm::vec3 strafe = move_speed_ * glm::cross(glm::normalize(target_ - position_), up_);
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
    glm::vec3 vert = move_speed_ * up_;
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
