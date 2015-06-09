#include "ScriptEngine.h"

int lua_test(lua_State *l) {
    int argc = lua_gettop(l);
    std::cout << argc << std::endl;
    int x = luaU_check<int>(l, 1);
    int y = luaU_check<int>(l, 2);
    int z = luaU_check<int>(l, 3);
    std::cout << x << "," << y << "," << z << std::endl;
    return 0;
}

const std::string ScriptEngine::kDefaultScriptDir = "scripts/";

ScriptEngine::ScriptEngine() :
        script_directory_(kDefaultScriptDir) { }

ScriptEngine::~ScriptEngine() {
    // close the Lua state
    lua_close(state_);
}

int ScriptEngine::Init() {
    state_ = luaL_newstate();
    luaL_openlibs(state_);
    luaopen_Game(state_);
    luaopen_BatchedRenderCube(state_);
    luaopen_Block(state_);
    luaopen_BlockRegistry(state_);
    luaopen_Dimension(state_);
    luaopen_Script(state_);
    return 1;
}

int ScriptEngine::RegisterFunction(lua_CFunction fn, std::string name) {
    // push the function (or static method) to lua
    lua_pushcfunction(state_, fn);
    // bind it to the given name
    lua_setglobal(state_, name.c_str());
    return 1;
}

int ScriptEngine::Exec(const std::string lua_expression) {
    int ret = luaL_dostring(state_, lua_expression.c_str());
    if(ret) printf("%s\n", lua_tostring(state_, -1));
    return ret == LUA_OK;
}

int ScriptEngine::Run(const std::string file) {
    const std::string filepath = "scripts/" + file;
    int ret = luaL_dofile(state_, filepath.c_str());
    if(ret) printf("%s\n", lua_tostring(state_, -1));
    // LUA_OK = 0 so return success (1) if ret == 0
    return ret == LUA_OK;
}


int ScriptEngine::Run(const Script *script) {
    return luaL_dostring(state_, script->Contents().c_str()) == LUA_OK;
}

std::string ScriptEngine::LoadScript(const std::string file) {
    using namespace std;
    ifstream ifs((script_directory_ + file).c_str(), ios::in | ios::binary | ios::ate);

    ifstream::pos_type fileSize = ifs.tellg();
    ifs.seekg(0, ios::beg);

    vector<char> bytes(fileSize);
    ifs.read(&bytes[0], fileSize);

    return string(&bytes[0], fileSize);
}

Script *ScriptEngine::MakeScript(std::string file) {
    const std::string file_contents = LoadScript(file);
    return new Script(file, LoadScript(file));
}
