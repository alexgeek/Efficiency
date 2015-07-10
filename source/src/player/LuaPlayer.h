#ifndef GAME_LUAPLAYER_H
#define GAME_LUAPLAYER_H

#include <assert.h>
#include "lua.hpp"
#include "lauxlib.h"
#include "../util/luawrapper.hpp"
#include "../util/luawrapperutil.hpp"
#include "Player.h"

int luaopen_Player(lua_State* L);


#endif //GAME_LUAPLAYER_H
