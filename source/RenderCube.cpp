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

RenderCube::RenderCube(string right, string left, string top, string bottom, string back, string front) : shader_(Shader("cube"))
{
    init(right, left, top, bottom, back, front);
}

RenderCube::RenderCube(string top, string sides) : RenderCube(sides, sides, top, sides, sides, sides)
{
}

RenderCube::RenderCube(string texture) : RenderCube(texture, texture, texture, texture, texture, texture)
{
}

void RenderCube::init(string right, string left, string top, string bottom, string back, string front)
{   
    texture_id_ = load_texture_cube(
        right.c_str(), 
        left.c_str(), 
        top.c_str(),
        bottom.c_str(), 
        back.c_str(), 
        front.c_str()
    );
    cout << "Texure #" << texture_id_ << endl;
    printOpenGLError();
    
  	mvp_ = glm::mat4(1.0f);
  	mvp_id_ = glGetUniformLocation(shader_.id(), "MVP");
  	
    glGenBuffers(1, &vertex_buffer_id_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertex_buffer_data), cube_vertex_buffer_data, GL_STATIC_DRAW);
}


void RenderCube::draw(Camera* camera, glm::vec3 position)
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
    glDrawArrays(GL_TRIANGLES, 0, 12*3);
    glDisableVertexAttribArray(0);
}

