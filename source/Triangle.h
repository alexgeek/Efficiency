#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <glm/glm.hpp>

class Triangle
{
    public:   
        Triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2);
        double* points_;
    private:

};

#endif // Triangle_H
