#include "CameraPlayer.h"

CameraPlayer::CameraPlayer(glm::vec3 position) :
    position_(position)
{ }

glm::mat4 CameraPlayer::get_projection() {
    return detail::tmat4x4<glm::mediump_float>();
}

glm::mat4 CameraPlayer::get_view() {
    return detail::tmat4x4<glm::mediump_float>();
}

void CameraPlayer::update(GLFWwindow *) {
}