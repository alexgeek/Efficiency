#include "RenderRect.h"

static const GLfloat rect_vertex_buffer_data[] = { 
	+1.0f,+1.0f, 0,
	-1.0f,+1.0f, 0,
	+1.0f,-1.0f, 0,
	-1.0f,+1.0f, 0,
	-1.0f,-1.0f, 0,
	+1.0f,-1.0f, 0,
};

RenderRect::RenderRect(string texture, string fragment) : shader_(Shader("rect", fragment))
{
    init(texture);
}

RenderRect::RenderRect(string texture) : RenderRect(texture, "rect")
{
}

void RenderRect::init(string texture)
{   
    texture_id_ = load_texture(texture.c_str());
    cout << "Texure #" << texture_id_ << endl;
    printOpenGLError();
    
  	mvp_ = glm::mat4(1.0f);
  	mvp_id_ = glGetUniformLocation(shader_.id(), "MVP");
  	
    glGenBuffers(1, &vertex_buffer_id_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_vertex_buffer_data), rect_vertex_buffer_data, GL_STATIC_DRAW);
    
      	cout << "[@]" << endl;
    printOpenGLError();
}


void RenderRect::draw(Camera* camera, glm::vec2 resolution)
{
  	cout << "[@1]" << endl;
    printOpenGLError();

    glUseProgram(shader_.id());
    
  	cout << "[@2]" << endl;
    printOpenGLError();
    
    mvp_ = camera->get_projection() * camera->get_view() * glm::translate(glm::mat4(1.0f), glm::vec3(0, 1.0f, 0));
	glUniformMatrix4fv(glGetUniformLocation(shader_.id(), "MVP"), 1, GL_FALSE, &mvp_[0][0]);
  	glUniform3f(glGetUniformLocation(shader_.id(), "iResolution"), resolution.x, resolution.y, 1.0f);	
  	glUniform1f(glGetUniformLocation(shader_.id(), "iGlobalTime"), glfwGetTime());
  	
  	cout << "[@3]" << endl;
    printOpenGLError();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id_);
	
  	cout << "[@4]" << endl;
    printOpenGLError();

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
    
	cout << "[@5]" << endl;
    printOpenGLError();
}

