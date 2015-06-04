#include "LuaRenderWorld.h"

static luaL_Reg RenderWorld_table[] =
        {
                {NULL, NULL}
        };

static luaL_Reg RenderWorld_metatable[] =
        {
                {NULL, NULL}
        };

int luaopen_RenderWorld(lua_State *L) {
    luaW_register<RenderWorld>(L,
                        "RenderWorld",
                        RenderWorld_table,
                        RenderWorld_metatable,
                        NULL
    );
    return 1;
}