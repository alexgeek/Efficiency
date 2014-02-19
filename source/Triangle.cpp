#include "Triangle.h"

Triangle::Triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2)
{
    points_ = (double*)malloc(9*sizeof(double));
    points_[0] = v0.x;
    points_[1] = v0.y;
    points_[2] = v0.z;
    points_[3] = v0.x;
    points_[4] = v0.y;
    points_[5] = v0.z;
    points_[6] = v0.x;
    points_[7] = v0.y;
    points_[8] = v0.z;
}
