#include "BatchedRenderCube.h"

static const GLfloat vertex_buffer_data[] = {
        // -x
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        // z-
        -0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        // z+
        0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, 0.5f,
        // y+
        -0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,
        //
        -0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        //
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,
        //
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        //
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        //
        -0.5f, 0.5f, 0.5f,
        0.5f, -0.5f, 0.5f
};

BatchedRenderCube::BatchedRenderCube(std::string right, std::string left, std::string top, std::string bottom,
                                     std::string back, std::string front) : shader_(Shader("batchcube")), dirty_(1) {
    Init(right, left, top, bottom, back, front);
}

BatchedRenderCube::BatchedRenderCube(std::string top, std::string sides) : BatchedRenderCube(sides, sides, top, sides,
                                                                                             sides, sides) {
}

BatchedRenderCube::BatchedRenderCube(std::string texture) : BatchedRenderCube(texture, texture, texture, texture,
                                                                              texture, texture) {
}

BatchedRenderCube::~BatchedRenderCube() {
}

void BatchedRenderCube::Init(std::string right, std::string left, std::string top, std::string bottom, std::string back,
                             std::string front) {
    texture_id_ = load_texture_cube(
            right.c_str(),
            left.c_str(),
            top.c_str(),
            bottom.c_str(),
            back.c_str(),
            front.c_str()
    );

    mv_ = glm::mat4(1.0f);
    mv_id_ = glGetUniformLocation(shader_.id(), "MV");

    glGenVertexArrays(1, &vertex_array_id_);
    glBindVertexArray(vertex_array_id_);

    glGenBuffers(1, &vertex_buffer_id_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, &position_buffer_id_);
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer_id_);
    glBufferData(GL_ARRAY_BUFFER, MAX_BLOCKS * sizeof(glm::vec3), NULL, GL_STREAM_DRAW);

    printOpenGLError();
}

void BatchedRenderCube::prepare(Camera *camera) {
    glUseProgram(shader_.id());

    mv_ = camera->GetProjection() * camera->GetView();
    glUniformMatrix4fv(mv_id_, 1, GL_FALSE, &mv_[0][0]);

    glUniform1f(glGetUniformLocation(shader_.id(), "globaltime"), glfwGetTime());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id_);

    glBindBuffer(GL_ARRAY_BUFFER, position_buffer_id_);

    if(dirty_ > 0) {
        glBufferData(GL_ARRAY_BUFFER, MAX_BLOCKS * sizeof(glm::vec3), NULL, GL_STREAM_DRAW); // Buffer orphaning
        glBufferSubData(GL_ARRAY_BUFFER, 0, positions_.size() * sizeof(glm::vec3), &positions_[0]);
        dirty_ = 0;
    }
    assert(positions_.size() < MAX_BLOCKS);
    printOpenGLError();

}


void BatchedRenderCube::BufferPosition(glm::vec3 position) {
    assert(position.y >= 0);
    assert(position.y <= 256);
    positions_.push_back(position);
    dirty_++;
}

void BatchedRenderCube::BufferPosition(float x, float y, float z) {
    BufferPosition(glm::vec3(x, y, z));
}

unsigned int BatchedRenderCube::BufferSize() {
    return positions_.size();
}

void BatchedRenderCube::Render(Camera *camera) {
    prepare(camera);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);
    glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void *) 0
    );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer_id_);
    glVertexAttribPointer(
            1,                                // layout location
            3,                                // size : vec3
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void *) 0                          // array buffer offset
    );

    glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices -> 0
    glVertexAttribDivisor(1, 1); // positions : one per quad (its center)                 -> 1

    glDrawArraysInstanced(GL_TRIANGLES, 0, 12 * 3, positions_.size());
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    finish();
}

void BatchedRenderCube::finish() {
    positions_.clear();
}

void BatchedRenderCube::ClearBuffer() {
    positions_.clear();
}
