#ifndef RENDERCUBE_H
#define RENDERCUBE_H

#include "default.h"
#include "util.h"
#include "Debug.h"
#include "Shader.h"
#include "Camera.h"

class RenderCube
{
    public:
        RenderCube(string right, string left, string top, string bottom, string back, string front);
        RenderCube(string top, string sides);
        RenderCube(string texture);
        void init(string right, string left, string top, string bottom, string back, string front);
        void draw(Camera* camera, glm::vec3 position);
    protected:
        Shader shader_;
        GLuint vertex_buffer_id_;
        GLuint texture_id_;
        GLuint mvp_id_;
        glm::mat4 mvp_;
    private:
};

#endif // RENDERCUBE_H

