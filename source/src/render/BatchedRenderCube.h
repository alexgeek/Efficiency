#ifndef BATCHEDRENDERCUBE_H
#define BATCHEDRENDERCUBE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>         // core window handling
#include <glm/gtc/matrix_transform.hpp> // rotate etc
#include <glm/gtc/type_ptr.hpp> // replace with macro for glm to and from opengl
#include <iostream>
#include <string>
#include <vector>

#include "../util.h"
#include "../util/Debug.h"
#include "../camera/Camera.h"
#include "Shader.h"

#define MAX_BLOCKS 0xFFFF

class BatchedRenderCube {
public:
    BatchedRenderCube(std::string right,
                      std::string left,
                      std::string top,
                      std::string bottom,
                      std::string back,
                      std::string front);
    BatchedRenderCube(std::string top, std::string sides);
    BatchedRenderCube(std::string texture);
    ~BatchedRenderCube();

    void Init(std::string right,
              std::string left,
              std::string top,
              std::string bottom,
              std::string back,
              std::string front);

    void BufferPosition(glm::vec3);
    void BufferPosition(float x, float y, float z);
    void ClearBuffer();
    unsigned int BufferSize();
    void Render(Camera *camera);

protected:
    std::vector<glm::vec3> positions_;
    Shader shader_;
    GLuint vertex_array_id_;
    GLuint vertex_buffer_id_;
    GLuint position_buffer_id_;
    GLuint texture_id_;
    GLint mv_id_;
    glm::mat4 mv_;
private:
    int dirty_;
    void prepare(Camera *camera);
    void finish();
};

#endif // BATCHEDRENDERCUBE_H

