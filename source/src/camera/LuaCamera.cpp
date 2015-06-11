#include "LuaCamera.h"

int Script_Contents(lua_State *L) {
    Script *render = luaW_check<Script>(L, 1);
    lua_pushstring(L, render->Contents().c_str());
    return 1;
}

int Script_Name(lua_State *L) {
    Script *render = luaW_check<Script>(L, 1);
    lua_pushstring(L, render->Name().c_str());
    return 1;
}

static luaL_Reg Script_table[] =
        {
                {NULL, NULL}
        };

static luaL_Reg Script_metatable[] =
        {
                {"Contents", Script_Contents},
                {"Name",     Script_Name},
                {NULL, NULL}
        };

int luaopen_Script(lua_State *L) {
    luaW_register<Script>(L,
                          "Script",
                          Script_table,
                          Script_metatable,
                          Script_new
    );
    return 1;
}
