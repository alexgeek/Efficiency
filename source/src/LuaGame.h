#ifndef GAME_LUAGAME_H
#define GAME_LUAGAME_H

#include "lua.hpp"
#include "lauxlib.h"
#include "util/luawrapper.hpp"
#include "util/luawrapperutil.hpp"
#include "render/RenderWorld.h"
#include "Game.h"

/*int Game_GetActiveCamera(lua_State *L)
{
    Game* game = luaW_check<Game>(L, 1);
    lua_pushstring(L, account->getOwnerName());
    return 1;
}*/

int Game_Render(lua_State *L);
int luaopen_Game(lua_State *L);


#endif //GAME_LUAGAME_H
