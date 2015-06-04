#include "LuaBatchedRenderCube.h"

BatchedRenderCube* BatchedRenderCube_new(lua_State *l)
{
    int argc = lua_gettop(l);
    switch(argc)
    {
        case 1:
        {
            std::string texture = luaU_check<std::string>(l, 1);
            return new BatchedRenderCube(texture);
        }
        case 2:
        {
            std::string top, sides;
            top = luaU_check<std::string>(l, 1);
            sides = luaU_check<std::string>(l, 2);
            return new BatchedRenderCube(top, sides);
        }
    }
    return NULL;
}

int BatchedRenderCube_BufferPosition(lua_State *l)
{
    BatchedRenderCube* render = luaW_check<BatchedRenderCube>(l, 1);
    int x = luaU_check<float>(l, 2);
    int y = luaU_check<float>(l, 3);
    int z = luaU_check<float>(l, 4);
    render->BufferPosition(x,y,z);
    return 0;
}
int BatchedRenderCube_BufferSize(lua_State *L)
{
    BatchedRenderCube* render = luaW_check<BatchedRenderCube>(L, 1);
    luaU_push<unsigned int>(L, render->BufferSize());
    return 1;
}

static luaL_Reg BatchedRenderCube_table[] =
        {
                { NULL, NULL }
        };

static luaL_Reg BatchedRenderCube_metatable[] =
        {
                { "BufferPosition", BatchedRenderCube_BufferPosition},
                { "BufferSize", BatchedRenderCube_BufferSize},
                { NULL, NULL }
        };

int luaopen_BatchedRenderCube(lua_State* L)
{
    luaW_register<BatchedRenderCube>(L,
                               "BatchedRenderCube",
                               BatchedRenderCube_table,
                               BatchedRenderCube_metatable,
                               BatchedRenderCube_new
    );
    return 1;
}
