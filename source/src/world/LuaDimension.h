#ifndef GAME_LUADIMENSION_H
#define GAME_LUADIMENSION_H

#include "lua.hpp"
#include "lauxlib.h"
#include "../util/luawrapper.hpp"
#include "../util/luawrapperutil.hpp"
#include "Dimension.h"

int luaopen_Dimension(lua_State* L);

#endif //GAME_LUADIMENSION_H
