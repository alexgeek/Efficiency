#ifndef GAME_LUABATCHEDRENDERCUBE_H
#define GAME_LUABATCHEDRENDERCUBE_H

#include "lua.hpp"
#include "lauxlib.h"
#include "../util/luawrapper.hpp"
#include "../util/luawrapperutil.hpp"
#include "BatchedRenderCube.h"

BatchedRenderCube* BatchedRenderCube_new(lua_State *L);
int BatchedRenderCube_BufferPosition(lua_State *L);
int BatchedRenderCube_BufferSize(lua_State *L);
int luaopen_BatchedRenderCube(lua_State* L);

#endif //GAME_LUABATCHEDRENDERCUBE_H
