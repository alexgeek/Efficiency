#include "LuaDimension.h"

int Dimension_SetBlock(lua_State *L) {
    Dimension* dim = luaW_check<Dimension>(L, 1);
    int x = luaU_check<int>(L, 2);
    int y = luaU_check<int>(L, 3);
    int z = luaU_check<int>(L, 4);
    int blockID = luaU_check<int>(L, 5);
    lua_pushnumber(L, dim->SetBlock(x, y, z, blockID));
    return 1;
}

int Dimension_GetBlock(lua_State *L) {
    Dimension* dim = luaW_check<Dimension>(L, 1);
    int x = luaU_check<int>(L, 2);
    int y = luaU_check<int>(L, 3);
    int z = luaU_check<int>(L, 4);
    lua_pushnumber(L, dim->GetBlock(x, y, z));
    return 1;
}

int Dimension_ClearBlock(lua_State *L) {
    Dimension* dim = luaW_check<Dimension>(L, 1);
    int x = luaU_check<int>(L, 2);
    int y = luaU_check<int>(L, 3);
    int z = luaU_check<int>(L, 4);
    lua_pushnumber(L, dim->ClearBlock(x, y, z));
    return 1;
}

static luaL_Reg Dimension_table[] =
        {
                {NULL, NULL}
        };

static luaL_Reg Dimension_metatable[] =
        {
                {"SetBlock", Dimension_SetBlock},
                {"GetBlock", Dimension_GetBlock},
                {"ClearBlock", Dimension_ClearBlock},
                {NULL, NULL}
        };

int luaopen_Dimension(lua_State *L) {
    luaW_register<Dimension>(L,
                                 "Dimension",
                                 Dimension_table,
                                 Dimension_metatable,
                                 NULL, NULL
    );
    return 1;
}