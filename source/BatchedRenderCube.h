#ifndef BATCHEDRENDERCUBE_H
#define BATCHEDRENDERCUBE_H

#include "default.h"
#include "util.h"
#include <vector>
#include "Debug.h"
#include "Shader.h"
#include "Camera.h"

#define MAX_BLOCKS 20000

class BatchedRenderCube
{
    public:
        BatchedRenderCube(std::string right, std::string left, std::string top, std::string bottom, std::string back, std::string front);
        BatchedRenderCube(std::string top, std::string sides);
        BatchedRenderCube(std::string texture);
        void init(std::string right, std::string left, std::string top, std::string bottom, std::string back, std::string front);
        // in order of use:
        void buffer_position(glm::vec3);
        void render(Camera* camera);
    protected:
        std::vector<glm::vec3> positions_;
        Shader shader_;
        GLuint vertex_array_id_;
        GLuint vertex_buffer_id_;
        GLuint position_buffer_id_;
        GLuint texture_id_;
        GLuint mv_id_;
        glm::mat4 mv_;
    private:
        void prepare(Camera* camera);
        void finish();
};

#endif // BATCHEDRENDERCUBE_H

