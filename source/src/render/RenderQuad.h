#ifndef RENDER_QUAD_H
#define RENDER_QUAD_H

#include "../default.h"
#include "../util.h"
#include "../util/Debug.h"
#include "Shader.h"
#include "../camera/Camera.h"

/**
 * Renders a textured plane at a given position.
 * TODO add rotation
 */
class RenderQuad
{
    public:
        RenderQuad(std::string texture);
        RenderQuad(std::string texture, std::string fragment);
        void init(std::string texture);
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
