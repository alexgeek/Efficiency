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

#include "CameraArcBall.h"
#include "Input.h"
#include "BatchedRenderCube.h"
#include "WindowContext.h"
#include "Script.h"
#include "ScriptEngine.h"
#include "Game.h"
// c files
#include "util.h"

Game* game;

// temp globals
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
    Camera* camera = new CameraArcBall(position, target);
    game->set_camera(camera);
    std::cout << "Camera: " << argc << std::endl << glm::to_string(position) << ", " << glm::to_string(target) << std::endl;
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
        (*it)->render(game->camera());
    }
    return 0;
}

int lua_time(lua_State* l)
{
    int argc = lua_gettop(l);
    lua_pushnumber(l, glfwGetTime());
    return 1;
}

int main(void)
{
    game = new Game();
    game->Init();
    game->Start();
    delete game;
    return 0;
}
