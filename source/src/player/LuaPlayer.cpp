#include "LuaPlayer.h"

Player *Player_new(lua_State *L) {
    int argc = lua_gettop(L);
    switch (argc) {
        case 1: {
            std::string name = luaU_check<std::string>(L, 1);
            return new Player(name);
        }
    }
    return NULL;
}

int Player_GetName(lua_State *L) {
    Player *player = luaW_check<Player>(L, 1);
    lua_pushstring(L, player->GetName().c_str());
    return 1;
}

int Player_SetName(lua_State *L) {
    Player *player = luaW_check<Player>(L, 1);
    std::string name = luaU_check<std::string>(L, 1);
    player->SetName(name);
    return 0;
}

static luaL_Reg Player_table[] =
        {
                {NULL, NULL}
        };

static luaL_Reg Player_metatable[] =
        {
                {"GetName",     Player_GetName},
                {"SetName", Player_SetName},
                {NULL, NULL}
        };

int luaopen_Player(lua_State *L) {
    luaW_register<Player>(L,
                         "Player",
                         Player_table,
                         Player_metatable,
                         Player_new
    );
    return 1;
}
