#include "default.h"
// lua
#include "lua.hpp"
// c++
#include <vector>
#include <stack>
#include <string>
// glm
#include <glm/gtx/string_cast.hpp>
// me
#include "Triangle.h"
#include "CameraArcBall.h"
#include "Input.h"
#include "Shader.h"
#include "RenderCube.h"
#include "BatchedRenderCube.h"
#include "RenderQuad.h"
#include "RenderRect.h"
// c files
#include "util.h"

// temp globals
Camera* camera;
vector<BatchedRenderCube*> renderer;

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
    delete camera;
    camera = new CameraArcBall(position, target);
    //std::cout << "Camera: " << argc << std::endl << glm::to_string(position) << ", " << glm::to_string(target) << std::endl;
    return 0;
}

int lua_load_renderer(lua_State *l)
{
    stack<string> textures;
    int argc = lua_gettop(l);
    for(int i = 0; i < argc; i++)
    {
        textures.push(lua_tostring(l, lua_gettop(l)));
        lua_pop(l, 1);
    }
    switch(argc)
    {
        case 1:
        {
            string texture = textures.top();
            renderer.push_back(new BatchedRenderCube(texture));
            lua_pushnumber(l, renderer.size()-1);
            return 1;
        }
        case 2:      
        {
            string top, sides;      
            sides = textures.top();
            textures.pop();
            top = textures.top();
            textures.pop();
            BatchedRenderCube* rc = new BatchedRenderCube(top, sides);
            renderer.push_back(rc);
            lua_pushnumber(l, renderer.size()-1);
            return 1;
        }
        break;
    }
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
    
    int renderer_id = lua_tointeger(l, lua_gettop(l));
    lua_pop(l, 1);    
    
    renderer[renderer_id]->buffer_position(position);
    
    return 0;
}

int lua_drawbatch(lua_State* l)
{
    int argc = lua_gettop(l);
    for(std::vector<BatchedRenderCube*>::iterator it = renderer.begin(); it != renderer.end(); ++it) {
        (*it)->render(camera);
    }
    return 0;
}

int run(lua_State *l, string file)
{
    string filepath = "scripts/" + file;
    if(luaL_dofile(l, filepath.c_str()))
        std::cerr << lua_tostring(l, -1) << std::endl;
}

static const GLfloat g_vertex_buffer_data[] = { 
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

int lua_time(lua_State* l)
{
    int argc = lua_gettop(l);
    lua_pushnumber(l, glfwGetTime());
    return 1;    
}

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

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // to use this: http://stackoverflow.com/questions/17923782/simple-opengl-image-library-soil-uses-deprecated-functionality
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
	glfwWindowHint(GLFW_OPENGL_PROFILE,	GLFW_OPENGL_COMPAT_PROFILE);

    /*glfwWindowHint(GLFW_SAMPLES, 1); // 2x antialiasing
    int stencil_bits = 8;

    glfwWindowHint(GLFW_STENCIL_BITS, 8); // request a stencil buffer for object selection*/
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    
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
    const GLubyte* gl_renderer = glGetString (GL_RENDERER); // get renderer string
    const GLubyte* gl_version = glGetString (GL_VERSION); // version as a string
    int gl_alpha;
    glGetIntegerv(GL_ALPHA_BITS, &gl_alpha);
    printf ("Renderer: %s\n", gl_renderer);
    printf ("OpenGL version supported %s\n", gl_version);
    printf ("Alphabits: %d", gl_alpha);
    
    glfwSwapInterval(1);
    
    printOpenGLError();
    cout << "Setting GL" << endl;
        
    //glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClearColor(0.9f, 0.9f, 0.99f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);
    glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);

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
    
    lua_pushcfunction(lua_state, lua_set_camera);
    lua_setglobal(lua_state, "camera");
        
    lua_pushcfunction(lua_state, lua_drawcube);
    lua_setglobal(lua_state, "drawblock");
    
    lua_pushcfunction(lua_state, lua_load_renderer);
    lua_setglobal(lua_state, "load_renderer");
    
    lua_pushcfunction(lua_state, lua_drawbatch);
    lua_setglobal(lua_state, "drawbatch");
    
    lua_pushcfunction(lua_state, lua_time);
    lua_setglobal(lua_state, "time");
    
    run(lua_state, "class.lua");
    run(lua_state, "entity.lua");
    run(lua_state, "world.lua");
    run(lua_state, "component.lua");
    run(lua_state, "block.lua");
    run(lua_state, "physics.lua");
    run(lua_state, "load.lua");
    
    //camera = new CameraArcBall(glm::vec3(5,5,5), glm::vec3(0,0,0));
    
    //renderer.push_back(new RenderCube("assets/textures/grass.jpg", "assets/textures/dirt.jpg")); // default renderer?
        
    cout << "Starting main loop:" << endl;
    
    glm::vec3 size = glm::vec3(2);
    
    RenderQuad quad("assets/textures/jap.png", "inversion");
    RenderRect rect("assets/textures/tex16.png", "inversion2");
    
    BatchedRenderCube batch("assets/textures/dirt.jpg");
    
    cout << "[initmain]" << endl;
    printOpenGLError();
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        glfwGetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);
        
        //glClearStencil(0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT /*| GL_STENCIL_BUFFER_BIT*/);
        
        // update input and actions
        Input::instance().update(window);
        
        // update view and projection
        camera->update(window);
        
        if(glfwGetKey(window, 'U'))
            run(lua_state, "action.lua");
        
        run(lua_state, "update.lua");
        run(lua_state, "render.lua");
        
        if(glfwGetKey(window, 'F'))
            std::cout << "FPS: " << calcFPS(glfwGetTime()) << std::endl;
        if(glfwGetKey(window, 'Q'))
            screenshot();
            
        quad.draw(camera, glm::vec3(0, 0, 0));
        
        if(glfwGetKey(window, GLFW_KEY_ENTER))
            rect.draw(camera, glm::vec2(width, height));
            
        printOpenGLError();
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }
	// Cleanup VBO and shader
	//glDeleteBuffers(1, &vertexbuffer);
	//glDeleteProgram(shader.id());
    
    // close the Lua state
    lua_close(lua_state);
    glfwTerminate();
    return 0;
}
