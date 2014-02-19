#include "default.h"
#include "lua.hpp"
#include "Triangle.h"
#include "CameraArcBall.h"
#include <vector>
#include <string>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "util.h"


void glfw_error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

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

static int report (lua_State *L, int status) {
  const char *msg;
  if (status) {
    msg = lua_tostring(L, -1);
    if (msg == NULL) msg = "(error with no message)";
    fprintf(stderr, "status=%d, %s\n", status, msg);
    lua_pop(L, 1);
  }
  return status;
}

int run(lua_State *l, std::string file)
{
    std::string filepath = "scripts/" + file;
    if(luaL_dofile(l, filepath.c_str()))
        std::cerr << lua_tostring(l, -1) << std::endl;
}


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

    /*glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/
    glfwWindowHint(GLFW_SAMPLES, 1); // 2x antialiasing
    int stencil_bits = 8;
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_STENCIL_BITS, 8); // request a stencil buffer for object selection
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Curve Editor", NULL, NULL);
    glfwRestoreWindow(window);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    // start GLEW extension handler
    /*glewExperimental = GL_TRUE;
    glewInit ();*/
    
    // get version info
    const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString (GL_VERSION); // version as a string
    printf ("Renderer: %s\n", renderer);
    printf ("OpenGL version supported %s\n", version);

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_STENCIL_TEST);
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
           
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glViewport(0, 0, width, height);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClearStencil(0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        
        // update input and actions
        Input::instance().update(window);
        
        // update view and projection
        camera.update(window);

        // load projection from camera
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMultMatrixf(glm::value_ptr( camera.get_projection() ));

        // load view from camera
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glMultMatrixf(glm::value_ptr( camera.get_view() ));

        if(glfwGetKey(window, 'U'))
            run(lua_state, "action.lua");
        
        run(lua_state, "update.lua");
        run(lua_state, "render.lua");
        
        if(glfwGetKey(window, 'F'))
            std::cout << "FPS: " << calcFPS(glfwGetTime()) << std::endl;
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }
    // close the Lua state
    lua_close(lua_state);
    glfwTerminate();
    return 0;
}
