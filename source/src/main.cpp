#include "default.h"
// lua
#include "lua.hpp"
#include "Game.h"

int lua_time(lua_State* l)
{
    int argc = lua_gettop(l);
    lua_pushnumber(l, glfwGetTime());
    return 1;
}

int main(void)
{
    Game* game = new Game();
    game->Init();
    game->Start();
    delete game;
    return 0;
}
