#include "LuaGame.h"

int Game_Render(lua_State *L) {
    Game *game = luaW_check<Game>(L, 1);
    luaW_push<RenderWorld>(L, game->Render());
    return 1;
}

int Game_Version(lua_State *L) {
    lua_pushstring(L, Game::Version.c_str());
    return 1;
}

int Game_GetDimension(lua_State *L) {
    Game *game = luaW_check<Game>(L, 1);
    int id = luaU_check<int>(L, 2);
    luaW_push<Dimension>(L, game->GetDimension(id));
    return 1;
}

static luaL_Reg Game_table[] =
        {
                {"Version", Game_Version},
                {NULL, NULL}
        };

static luaL_Reg Game_metatable[] =
        {
                {"Render", Game_Render},
                {"GetDimension", Game_GetDimension},
                {NULL, NULL}
        };

int luaopen_Game(lua_State *L) {
    luaW_register<Game>(L,
                        "Game",
                        Game_table,
                        Game_metatable,
                        NULL
    );
    return 1;
}