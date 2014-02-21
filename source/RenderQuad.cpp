#include "RenderQuad.h"

static const GLfloat quad_vertex_buffer_data[] = { 
	+0.5f,+0.5f, 0,
	-0.5f,+0.5f, 0,
	+0.5f,-0.5f, 0,
	-0.5f,+0.5f, 0,
	-0.5f,-0.5f, 0,
	+0.5f,-0.5f, 0,
};

RenderQuad::RenderQuad(string texture, string fragment) : shader_(Shader("quad", fragment))
{
    init(texture);
}

RenderQuad::RenderQuad(string texture) : RenderQuad(texture, "quad")
{
}

void RenderQuad::init(string texture)
{   
    texture_id_ = load_texture(texture.c_str());
    cout << "Texure #" << texture_id_ << endl;
    printOpenGLError();
    
  	mvp_ = glm::mat4(1.0f);
  	mvp_id_ = glGetUniformLocation(shader_.id(), "MVP");
  	
    glGenBuffers(1, &vertex_buffer_id_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertex_buffer_data), quad_vertex_buffer_data, GL_STATIC_DRAW);
}


void RenderQuad::draw(Camera* camera, glm::vec3 position)
{
    glUseProgram(shader_.id());
    
    mvp_ = camera->get_projection() * camera->get_view() * glm::translate(glm::mat4(1.0f), position);
	glUniformMatrix4fv(glGetUniformLocation(shader_.id(), "MVP"), 1, GL_FALSE, &mvp_[0][0]);
	
  	glUniform1f(glGetUniformLocation(shader_.id(), "globaltime"), glfwGetTime());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id_);

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
    glDrawArrays(GL_TRIANGLES, 0, 2*3);
    glDisableVertexAttribArray(0);
}

