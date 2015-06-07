#ifndef GAME_LUABLOCKREGISTRY_H
#define GAME_LUABLOCKREGISTRY_H

#include <assert.h>
#include "lua.hpp"
#include "lauxlib.h"
#include "../util/luawrapper.hpp"
#include "../util/luawrapperutil.hpp"
#include "BlockRegistry.h"

int luaopen_BlockRegistry(lua_State* L);

#endif //GAME_LUABLOCKREGISTRY_H
