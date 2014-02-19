#include "default.h"
// lua
#include "lua.hpp"
// c++
#include <vector>
#include <string>
// glm
#include <glm/gtx/string_cast.hpp>
// me
#include "Triangle.h"
#include "CameraArcBall.h"
#include "Input.h"
#include "Shader.h"
// c files
#include "util.h"

Triangle tri(
    glm::vec3(0.0, 0.5, 0.0), 
    glm::vec3(0.5, -0.5, 0.0),
    glm::vec3(-0.5, -0.5, 0.0));
    
int lua_triangle(lua_State *l)
{
    int argc = lua_gettop(l);
    //if(argc != 9) return;
    glm::vec3 v1, v2, v3;
    v1 = glm::vec3(0);
    for(int i = 0; i < 3; i++)
    {
        v1[i] = lua_tonumber(l, lua_gettop(l));
        lua_pop(l, 1);
    }
    v2 = glm::vec3(0);
    for(int i = 0; i < 3; i++)
    {
        v2[i] = lua_tonumber(l, lua_gettop(l));
        lua_pop(l, 1);
    }
    v3 = glm::vec3(0);
    for(int i = 0; i < 3; i++)
    {
        v3[i] = lua_tonumber(l, lua_gettop(l));
        lua_pop(l, 1);
    }
    tri = Triangle(v1, v2, v3);
    
    return 0;
}

CameraArcBall camera(glm::vec3(5,5,5), glm::vec3(0,0,0));

int lua_set_camera(lua_State *l)
{
    int argc = lua_gettop(l);
    glm::vec3 position, target;
    
    target = glm::vec3(0);
    for(int i = 0; i < 3; i++)
    {
        target[2-i] = lua_tonumber(l, lua_gettop(l));
        lua_pop(l, 1);
    }
    position = glm::vec3(0);
    for(int i = 0; i < 3; i++)
    {
        position[2-i] = lua_tonumber(l, lua_gettop(l));
        lua_pop(l, 1);
    }
    
    camera = CameraArcBall(position, target);
    //std::cout << "Camera: " << argc << std::endl << glm::to_string(position) << ", " << glm::to_string(target) << std::endl;
    return 0;
}

int lua_drawcube(lua_State *l)
{
    int argc = lua_gettop(l);
    glm::vec3 position = glm::vec3(0);
    for(int i = 0; i < 3; i++)
    {
        position[2-i] = lua_tonumber(l, lua_gettop(l));
        lua_pop(l, 1);        
    }
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslated(position.x, position.y, position.z);
    
    const float s = 0.5f;

    glBegin(GL_QUADS);

    // top
    glColor3d(0.6, 0.4, 0.3);
    glVertex3f(-s, s, -s);
    glVertex3f(-s, s, s);
    glVertex3f(s, s, s);
    glVertex3f(s, s, -s);
    
    // bottom
    glColor3d(0.1, 0.2, 0.2);
    glVertex3f(-s, -s, -s);
    glVertex3f(s, -s, -s);
    glVertex3f(s, -s, s);
    glVertex3f(-s, -s, s);
    
    // front
    glColor3d(0.75, 0, 0);
    glVertex3f(-s, -s, s);
    glVertex3f(s, -s, s);
    glVertex3f(s, s, s);
    glVertex3f(-s, s, s);
    
    // back
    glColor3d(0, 0.75, 0);
    glVertex3f(-s, s, -s);
    glVertex3f(s, s, -s);
    glVertex3f(s, -s, -s);
    glVertex3f(-s, -s, -s);
    
    // right
    glVertex3f(s, -s, s);
    glVertex3f(s, -s, -s);
    glVertex3f(s, s, -s);
    glVertex3f(s, s, s);
    
    // left
    glVertex3f(-s, s, s);
    glVertex3f(-s, s, -s);
    glVertex3f(-s, -s, -s);
    glVertex3f(-s, -s, s);

    glEnd();
    glPopMatrix();
    //std::cout << "Cube: " << argc << std::endl << glm::to_string(position) <<std::endl;
    
    return 0;
}

float angle = 0;
int lua_draw(lua_State *l)
{
    int argc = lua_gettop(l);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(angle, 0, 1.0f, 0);
    angle += 1.0f;
    glBegin(GL_TRIANGLES);
    glColor3f(0.1, 0.2, 0.3);
    for(int i = 0; i < 9; i++)
    glVertex3d(tri.points_[i],tri.points_[i+1],tri.points_[i+2]);
    glEnd();
    glPopMatrix();
    
    return 0;
}

int run(lua_State *l, string file)
{
    string filepath = "scripts/" + file;
    if(luaL_dofile(l, filepath.c_str()))
        std::cerr << lua_tostring(l, -1) << std::endl;
}

static const GLfloat g_vertex_buffer_data[] = { 
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	 1.0f, 1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	 1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	 1.0f,-1.0f,-1.0f,
	 1.0f, 1.0f,-1.0f,
	 1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	 1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	 1.0f,-1.0f, 1.0f,
	 1.0f, 1.0f, 1.0f,
	 1.0f,-1.0f,-1.0f,
	 1.0f, 1.0f,-1.0f,
	 1.0f,-1.0f,-1.0f,
	 1.0f, 1.0f, 1.0f,
	 1.0f,-1.0f, 1.0f,
	 1.0f, 1.0f, 1.0f,
	 1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	 1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	 1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	 1.0f,-1.0f, 1.0f
};

static const GLfloat g_uv_buffer_data[] = { 
	0.000059f, 1.0f-0.000004f, 
	0.000103f, 1.0f-0.336048f, 
	0.335973f, 1.0f-0.335903f, 
	1.000023f, 1.0f-0.000013f, 
	0.667979f, 1.0f-0.335851f, 
	0.999958f, 1.0f-0.336064f, 
	0.667979f, 1.0f-0.335851f, 
	0.336024f, 1.0f-0.671877f, 
	0.667969f, 1.0f-0.671889f, 
	1.000023f, 1.0f-0.000013f, 
	0.668104f, 1.0f-0.000013f, 
	0.667979f, 1.0f-0.335851f, 
	0.000059f, 1.0f-0.000004f, 
	0.335973f, 1.0f-0.335903f, 
	0.336098f, 1.0f-0.000071f, 
	0.667979f, 1.0f-0.335851f, 
	0.335973f, 1.0f-0.335903f, 
	0.336024f, 1.0f-0.671877f, 
	1.000004f, 1.0f-0.671847f, 
	0.999958f, 1.0f-0.336064f, 
	0.667979f, 1.0f-0.335851f, 
	0.668104f, 1.0f-0.000013f, 
	0.335973f, 1.0f-0.335903f, 
	0.667979f, 1.0f-0.335851f, 
	0.335973f, 1.0f-0.335903f, 
	0.668104f, 1.0f-0.000013f, 
	0.336098f, 1.0f-0.000071f, 
	0.000103f, 1.0f-0.336048f, 
	0.000004f, 1.0f-0.671870f, 
	0.336024f, 1.0f-0.671877f, 
	0.000103f, 1.0f-0.336048f, 
	0.336024f, 1.0f-0.671877f, 
	0.335973f, 1.0f-0.335903f, 
	0.667969f, 1.0f-0.671889f, 
	1.000004f, 1.0f-0.671847f, 
	0.667979f, 1.0f-0.335851f
};

int printOglError(char const* file, int line)
{

    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s\n",
			     file, line, gluErrorString(glErr));
        retCode = 1;
    }
    return retCode;
}

#define printOpenGLError() printOglError(__FILE__, __LINE__)

int main(void)
{
    GLFWwindow* window;


    int width = 1024;
    int height = 768;

    glfwSetErrorCallback (glfw_error_callback);
    if(!glfwInit ()) {
        fprintf (stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }

//	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // to use this: http://stackoverflow.com/questions/17923782/simple-opengl-image-library-soil-uses-deprecated-functionality
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
	glfwWindowHint(GLFW_OPENGL_PROFILE,	GLFW_OPENGL_COMPAT_PROFILE);

    /*glfwWindowHint(GLFW_SAMPLES, 1); // 2x antialiasing
    int stencil_bits = 8;
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_STENCIL_BITS, 8); // request a stencil buffer for object selection*/
    
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Game", NULL, NULL);
    glfwRestoreWindow(window);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
  
    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    
    GLenum err = glewInit();
    if(err != GLEW_OK)
    {
        cout << "GLEW error: " << glewGetErrorString(err);
        exit(1); // or handle the error in a nicer way
    }
    GLenum glErr = glGetError();
    if (glErr != GL_NO_ERROR)
    {
        cout << "Caught GLEW init error in GL" << endl;
    }

    printOpenGLError();
            
    // get version info
    const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString (GL_VERSION); // version as a string
    printf ("Renderer: %s\n", renderer);
    printf ("OpenGL version supported %s\n", version);
    
    printOpenGLError();
    cout << "Setting GL" << endl;
        
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);
    //glEnable(GL_CULL_FACE);

    glfwSetCharCallback(window, &Input::glfw_character_callback);
    glfwSetKeyCallback(window, &Input::glfw_key_callback);
    
    // create new Lua state
    lua_State *lua_state;
    lua_state = luaL_newstate();
    luaL_openlibs(lua_state);
 
    // load Lua libraries
    /*static const luaL_Reg lualibs[] =
    {
        { "base", luaopen_base },
        { "io", luaopen_io },
        { "string", luaopen_string },
        { NULL, NULL}
    };
 
    const luaL_Reg *lib = lualibs;
    for(; lib->func != NULL; lib++)
    {
        lib->func(lua_state);
        lua_settop(lua_state, 0);
    }*/
        
    lua_pushcfunction(lua_state, lua_triangle);
    lua_setglobal(lua_state, "triangle");
    
    lua_pushcfunction(lua_state, lua_set_camera);
    lua_setglobal(lua_state, "camera");
    
    lua_pushcfunction(lua_state, lua_draw);
    lua_setglobal(lua_state, "draw");
    
    lua_pushcfunction(lua_state, lua_drawcube);
    lua_setglobal(lua_state, "drawblock");
    
    run(lua_state, "class.lua");
    run(lua_state, "entity.lua");
    run(lua_state, "world.lua");
    run(lua_state, "component.lua");
    run(lua_state, "block.lua");
    run(lua_state, "load.lua");
    
    printOpenGLError();
    cout << "Shader Loading" << endl;
    Shader shader("simple");
    cout << "Shader loaded." << endl;
    printOpenGLError();
    
    GLuint texture = load_texture();
	GLuint TextureID  = glGetUniformLocation(shader.id(), "myTextureSampler");
    
  	GLuint mvpId = glGetUniformLocation(shader.id(), "MVP"); 	
    glm::mat4 mvp = camera.get_projection() * camera.get_view();
    
    printOpenGLError();
    cout << "Lets do the buffers" << endl;
    // first arrays
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
    // vert buffer
  	GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    // uv buffer
	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
    cout << "Did the buffers" << endl;
    
    cout << "Starting main loop" << endl;
    
    float angle = 0;
               
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glViewport(0, 0, width, height);

        //glClearStencil(0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT /*| GL_STENCIL_BUFFER_BIT*/);
        
        // update input and actions
        Input::instance().update(window);
        
        // update view and projection
        camera.update(window);

        /* OLD WAY 
        // load projection from camera
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMultMatrixf(glm::value_ptr( camera.get_projection() ));

        // load view from camera
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glMultMatrixf(glm::value_ptr( camera.get_view() ));
        /* OLD WAY */
        
        /* NEW WAY */
        angle += 0.1f;
        glm::mat4 model = glm::rotate(
            glm::mat4(1.0f),
            angle,
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        mvp = camera.get_projection() * camera.get_view() * model;
   		glUniformMatrix4fv(mvpId, 1, GL_FALSE, &mvp[0][0]);
   		
		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID, 0);
   		
        glUseProgram(shader.id());
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
        );
        
		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

        glDrawArrays(GL_TRIANGLES, 0, 12*3);
        glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
        /* NEW WAY */
        

        if(glfwGetKey(window, 'U'))
            run(lua_state, "action.lua");
        
        run(lua_state, "update.lua");
        run(lua_state, "render.lua");
        
        if(glfwGetKey(window, 'F'))
            std::cout << "FPS: " << calcFPS(glfwGetTime()) << std::endl;
        if(glfwGetKey(window, 'S'))
            screenshot();
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }
	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteProgram(shader.id());
	glDeleteVertexArrays(1, &VertexArrayID);
    
    // close the Lua state
    lua_close(lua_state);
    glfwTerminate();
    return 0;
}
