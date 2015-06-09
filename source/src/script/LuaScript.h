#ifndef GAME_LUASCRIPT_H
#define GAME_LUASCRIPT_H

#include "lua.hpp"
#include "lauxlib.h"
#include "../util/luawrapper.hpp"
#include "../util/luawrapperutil.hpp"
#include "../render/RenderWorld.h"
#include "Script.h"

int luaopen_Script(lua_State *L);

#endif //GAME_LUASCRIPT_H
