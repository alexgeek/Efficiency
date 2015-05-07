#ifndef RENDERRECT_H
#define RENDERRECT_H

#include "default.h"
#include "util.h"
#include "Debug.h"
#include "Shader.h"
#include "Camera.h"

/**
 * Renders a 2D rectangle to the screen.
 * For GUIs and other overlays.
 */
class RenderRect
{
    public:
        RenderRect(string texture);
        RenderRect(string texture, string fragment);
        void init(string texture);
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

#endif // RENDERRECT_H
