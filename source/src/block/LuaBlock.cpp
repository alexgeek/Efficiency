#include "LuaBlock.h"

Block *Block_new(lua_State *L) {
    int argc = lua_gettop(L);
    switch (argc) {
        case 1: {
            std::string name = luaU_check<std::string>(L, 1);
            return new Block(name);
        }
    }
    return NULL;
}

int Block_GetName(lua_State *L) {
    Block *block = luaW_check<Block>(L, 1);
    lua_pushstring(L, block->GetName().c_str());
}

int Block_SetRenderer(lua_State *L) {
    Block *block = luaW_check<Block>(L, 1);
    BatchedRenderCube *render = luaW_check<BatchedRenderCube>(L, 2);
    assert(render != NULL);
    block->SetRenderer(render);
    return 0;
}

int Block_GetRenderer(lua_State *L) {
    Block *block = luaW_check<Block>(L, 1);
    luaW_push<BatchedRenderCube>(L, block->GetRenderer());
}


static luaL_Reg Block_table[] =
        {
                {NULL, NULL}
        };

static luaL_Reg Block_metatable[] =
        {
                {"GetName",     Block_GetName},
                {"SetRenderer", Block_SetRenderer},
                {"GetRenderer", Block_GetRenderer},
                {NULL, NULL}
        };

int luaopen_Block(lua_State *L) {
    luaW_register<Block>(L,
                         "Block",
                         Block_table,
                         Block_metatable,
                         Block_new
    );
    return 1;
}
