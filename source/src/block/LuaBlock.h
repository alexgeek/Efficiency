#ifndef GAME_LUABLOCK_H
#define GAME_LUABLOCK_H

#include <assert.h>
#include "lua.hpp"
#include "lauxlib.h"
#include "../util/luawrapper.hpp"
#include "../util/luawrapperutil.hpp"
#include "Block.h"

int luaopen_Block(lua_State* L);


#endif //GAME_LUABLOCK_H
