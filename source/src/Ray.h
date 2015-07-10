#ifndef GAME_RAY_H
#define GAME_RAY_H

#include <glm/core/type.hpp>

class Ray
{
public:
    Ray(glm::vec3 origin, glm::vec3 direction);
private:
    glm::vec3 origin;
    glm::vec3 direction;
};

#endif //GAME_RAY_H
