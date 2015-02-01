#include "BatchedRenderCube.h"

static const GLfloat vertex_buffer_data[] = {
	-0.5f,-0.5f,-0.5f,
	-0.5f,-0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	 0.5f, 0.5f,-0.5f,
	-0.5f,-0.5f,-0.5f,
	-0.5f, 0.5f,-0.5f,
	 0.5f,-0.5f, 0.5f,
	-0.5f,-0.5f,-0.5f,
	 0.5f,-0.5f,-0.5f,
	 0.5f, 0.5f,-0.5f,
	 0.5f,-0.5f,-0.5f,
	-0.5f,-0.5f,-0.5f,
	-0.5f,-0.5f,-0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f,-0.5f,
	 0.5f,-0.5f, 0.5f,
	-0.5f,-0.5f, 0.5f,
	-0.5f,-0.5f,-0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f,-0.5f, 0.5f,
	 0.5f,-0.5f, 0.5f,
	 0.5f, 0.5f, 0.5f,
	 0.5f,-0.5f,-0.5f,
	 0.5f, 0.5f,-0.5f,
	 0.5f,-0.5f,-0.5f,
	 0.5f, 0.5f, 0.5f,
	 0.5f,-0.5f, 0.5f,
	 0.5f, 0.5f, 0.5f,
	 0.5f, 0.5f,-0.5f,
	-0.5f, 0.5f,-0.5f,
	 0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f,-0.5f,
	-0.5f, 0.5f, 0.5f,
	 0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	 0.5f,-0.5f, 0.5f
};

BatchedRenderCube::BatchedRenderCube(string right, string left, string top, string bottom, string back, string front) : shader_(Shader("batchcube"))
{
    init(right, left, top, bottom, back, front);
}

BatchedRenderCube::BatchedRenderCube(string top, string sides) : BatchedRenderCube(sides, sides, top, sides, sides, sides)
{
}

BatchedRenderCube::BatchedRenderCube(string texture) : BatchedRenderCube(texture, texture, texture, texture, texture, texture)
{
}

void BatchedRenderCube::init(string right, string left, string top, string bottom, string back, string front)
{
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

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

    glGenBuffers(1, &vertex_buffer_id_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, &position_buffer_id_);
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer_id_);
    glBufferData(GL_ARRAY_BUFFER, MAX_BLOCKS * sizeof(glm::vec3), NULL, GL_STREAM_DRAW);
    cout << "Finish batch init" << endl;
    printOpenGLError();
}

void BatchedRenderCube::prepare(Camera* camera)
{
    glUseProgram(shader_.id());

    mv_ = camera->get_projection() * camera->get_view();
	glUniformMatrix4fv(mv_id_, 1, GL_FALSE, &mv_[0][0]);

  	glUniform1f(glGetUniformLocation(shader_.id(), "globaltime"), glfwGetTime());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id_);

	glBindBuffer(GL_ARRAY_BUFFER, position_buffer_id_);
	glBufferData(GL_ARRAY_BUFFER, MAX_BLOCKS * sizeof(glm::vec3), NULL, GL_STREAM_DRAW); // Buffer orphaning
	glBufferSubData(GL_ARRAY_BUFFER, 0, positions_.size() * sizeof(glm::vec3), &positions_[0]);

}


void BatchedRenderCube::buffer_position(glm::vec3 position)
{
    positions_.push_back(position);
}

void BatchedRenderCube::render(Camera* camera)
{
    prepare(camera);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );

    glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer_id_);
	glVertexAttribPointer(
		1,                                // layout location
		3,                                // size : vec3
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

    glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices -> 0
		glVertexAttribDivisor(1, 1); // positions : one per quad (its center)                 -> 1

    glDrawArraysInstanced(GL_TRIANGLES, 0, 12*3, positions_.size());
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    finish();
}

void BatchedRenderCube::finish()
{
    positions_.clear();
}
