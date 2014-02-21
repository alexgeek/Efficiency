#ifndef RENDERQUAD_H
#define RENDERQUAD_H

#include "default.h"
#include "util.h"
#include "Debug.h"
#include "Shader.h"
#include "Camera.h"

class RenderQuad
{
    public:
        RenderQuad(string texture);
        RenderQuad(string texture, string fragment);
        void init(string texture);
        void draw(Camera* camera, glm::vec3 position);
    protected:
        Shader shader_;
        GLuint vertex_buffer_id_;
        GLuint texture_id_;
        GLuint mvp_id_;
        glm::mat4 mvp_;
    private:
};

#endif // RENDERQUAD_H

