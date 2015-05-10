#ifndef RENDER_CUBE_H
#define RENDER_CUBE_H

#include "../default.h"
#include "../util.h"
#include "../Debug.h"
#include "Shader.h"
#include "../camera/Camera.h"

class RenderCube
{
    public:
        RenderCube(std::string right, std::string left, std::string top, std::string bottom, std::string back, std::string front);
        RenderCube(std::string top, std::string sides);
        RenderCube(std::string texture);
        void init(std::string right, std::string left, std::string top, std::string bottom, std::string back, std::string front);
        void draw(Camera* camera, glm::vec3 position);
    protected:
        Shader shader_;
        GLuint vertex_buffer_id_;
        GLuint texture_id_;
        GLuint mvp_id_;
        glm::mat4 mvp_;
    private:
};

#endif

