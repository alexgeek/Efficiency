#include "default.h"
// lua
#include "lua.hpp"
// c++
#include <vector>
#include <stack>
// glm
#include <glm/gtx/string_cast.hpp>
// me

#include "camera/CameraArcBall.h"
#include "render/BatchedRenderCube.h"
#include "util/luawrapper.hpp"
#include "util/luawrapperutil.hpp"
#include "Game.h"
// c files

/**
 * Global reference to the game for lua scripting.
 */
Game* game;

// temp globals
vector<BatchedRenderCube*> renderer;

int lua_load_renderer(lua_State *l)
{
    stack<string> textures;
    int argc = lua_gettop(l);
    for(int i = 0; i < argc; i++)
    {
        textures.push(lua_tostring(l, lua_gettop(l)));
        lua_pop(l, 1);
    }
    unsigned int blockID = (unsigned int)lua_tonumber(l, lua_gettop(l));
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

    renderer[renderer_id]->BufferPosition(position);

    return 0;
}

int lua_drawbatch(lua_State* l)
{
    int argc = lua_gettop(l);
    for(std::vector<BatchedRenderCube*>::iterator it = renderer.begin(); it != renderer.end(); ++it) {
        (*it)->Render(game->ActiveCamera());
    }
    return 0;
}

int lua_time(lua_State* l)
{
    int argc = lua_gettop(l);
    lua_pushnumber(l, glfwGetTime());
    return 1;
}

int lua_get_block(lua_State* l)
{
    int blockID = luaL_checkint(l, 1);
    lua_pushlightuserdata(l, BlockRegistry::Instance().GetBlock(blockID));
    return 1;
}

int lua_get_block_by_name(lua_State* l)
{
    std::string blockName = luaU_check<std::string>(l, 1);
    lua_pushlightuserdata(l, BlockRegistry::Instance().GetBlock(blockName));
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
