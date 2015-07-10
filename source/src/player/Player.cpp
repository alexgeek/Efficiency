#include "Player.h"

Player::Player(std::string name, glm::vec3 position) :
    name_(name),
    position_(position)
{
}

Player::Player(std::string name) :
        name_(name),
        position_(glm::vec3(0.0f, 0.0f, 0.0f))
{
}
