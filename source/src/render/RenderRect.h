#ifndef RENDER_RECT_H
#define RENDER_RECT_H

#include "../default.h"
#include "../util.h"
#include "../util/Debug.h"
#include "Shader.h"
#include "../camera/Camera.h"

/**
 * Renders a 2D rectangle to the screen.
 * For GUIs and other overlays.
 */
class RenderRect
{
    public:
        RenderRect(std::string texture);
        RenderRect(std::string texture, std::string fragment);
        void init(std::string texture);
        void draw(Camera* camera, glm::vec2 resolution);
    protected:
        Shader shader_;
        GLuint vertex_buffer_id_;
        GLuint vertex_array_id_;
        GLuint texture_id_;
        GLuint mvp_id_;
        glm::mat4 mvp_;
    private:
};

#endif
