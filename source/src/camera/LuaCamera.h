#ifndef GAME_LUACAMERA_H
#define GAME_LUACAMERA_H

#include "lua.hpp"
#include "lauxlib.h"
#include "../util/luawrapper.hpp"
#include "../util/luawrapperutil.hpp"
#include "../render/RenderWorld.h"
#include "Camera.h"

int luaopen_Camera(lua_State *L);

#endif //GAME_LUACAMERA_H
