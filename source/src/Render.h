#ifndef RENDER_H
#define RENDER_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Render
{
    public:
        virtual void draw(Camera* camera, glm::vec3 position) = 0;
    protected:
    private:
};

#endif // RENDER_H
