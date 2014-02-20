#include "RenderCube.h"

static const GLfloat cube_vertex_buffer_data[] = { 
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

RenderCube::RenderCube(string texture) : shader_(Shader("cube"))
{
    init(texture);
}

void RenderCube::init(string texture)
{   
    texture_id_ = load_texture_cube("assets/textures/dirt.jpg");
    printOpenGLError();
    
  	mvp_ = glm::mat4(1.0f);
  	mvp_id_ = glGetUniformLocation(shader_.id(), "MVP");

    glGenBuffers(1, &vertex_buffer_id_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertex_buffer_data), cube_vertex_buffer_data, GL_STATIC_DRAW);
}

void RenderCube::draw(Camera* camera, glm::vec3 position)
{
    mvp_ = camera->get_projection() * camera->get_view() * glm::translate(glm::mat4(1.0f), position);
	glUniformMatrix4fv(mvp_id_, 1, GL_FALSE, &mvp_[0][0]);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id_);

    glUseProgram(shader_.id());
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
    glDrawArrays(GL_TRIANGLES, 0, 12*3);
    glDisableVertexAttribArray(0);
}

