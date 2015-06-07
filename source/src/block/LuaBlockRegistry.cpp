#include "LuaBlockRegistry.h"


int BlockRegistry_GetBlock(lua_State *L) {
    BlockRegistry* reg = luaW_check<BlockRegistry>(L, 1);
    if (lua_isnumber(L, 2)) {
        unsigned int id = lua_tonumber(L, 2);
        luaW_push<Block>(L, reg->GetBlock(id));
    } else {
        std::string name = luaU_check<std::string>(L,2);
        luaW_push<Block>(L, reg->GetBlock(name));
    }
    return 1;
}

int BlockRegistry_GetBlockID(lua_State *L) {
    BlockRegistry* reg = luaW_check<BlockRegistry>(L, 1);
    std::string name = luaU_check<std::string>(L,2);
    lua_pushnumber(L, reg->GetBlockID(name));
    return 1;
}

int BlockRegistry_Size(lua_State *L) {
    BlockRegistry* reg = luaW_check<BlockRegistry>(L, 1);
    lua_pushnumber(L, reg->Size());
    return 1;
}

int BlockRegistry_RegisterBlock(lua_State *L) {
    BlockRegistry* reg = luaW_check<BlockRegistry>(L, 1);
    Block* block = luaW_check<Block>(L, 2);
    lua_pushnumber(L, reg->RegisterBlock(block));
    return 0;
}

static luaL_Reg BlockRegistry_table[] =
        {
                {NULL, NULL}
        };

static luaL_Reg BlockRegistry_metatable[] =
        {
                {"GetBlock", BlockRegistry_GetBlock},
                {"GetBlockID", BlockRegistry_GetBlockID},
                {"Size", BlockRegistry_Size},
                {"RegisterBlock", BlockRegistry_RegisterBlock},
                {NULL, NULL}
        };

int luaopen_BlockRegistry(lua_State *L) {
    luaW_register<BlockRegistry>(L,
                        "BlockRegistry",
                        BlockRegistry_table,
                        BlockRegistry_metatable,
                        NULL, NULL
    );
    return 1;
}