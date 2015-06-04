#ifndef GAME_LUARENDERWORLD_H
#define GAME_LUARENDERWORLD_H

#include "lua.hpp"
#include "lauxlib.h"
#include "../util/luawrapper.hpp"
#include "../util/luawrapperutil.hpp"
#include "RenderWorld.h"

int luaopen_RenderWorld(lua_State* L);

#endif //GAME_LUARENDERWORLD_H
