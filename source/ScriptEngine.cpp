#include "ScriptEngine.h"

const std::string ScriptEngine::kDefaultScriptDir = "scripts/";

ScriptEngine::ScriptEngine() :
  script_dir_(kDefaultScriptDir)
{}

ScriptEngine::~ScriptEngine()
{
  // close the Lua state
  lua_close(state_);
}

int ScriptEngine::Init() {
  state_ = luaL_newstate();
  luaL_openlibs(state_);
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
  return luaL_dostring(state_, lua_expression.c_str()) == LUA_OK;
}

int ScriptEngine::Run(const std::string file) {
  const std::string filepath = "scripts/" + file;
  int ret = luaL_dofile(state_, filepath.c_str());
  if(ret) std::cerr << lua_tostring(state_, -1) << std::endl;
  // LUA_OK = 0 so return success (1) if ret == 0
  return ret == LUA_OK;
}


int ScriptEngine::Run(const Script* script) {
  return luaL_dostring(state_, script->contents().c_str()) == LUA_OK;
}

std::string ScriptEngine::LoadScript(const std::string file) {
    using namespace std;
    ifstream ifs((script_dir_ + file).c_str(), ios::in | ios::binary | ios::ate);

    ifstream::pos_type fileSize = ifs.tellg();
    ifs.seekg(0, ios::beg);

    vector<char> bytes(fileSize);
    ifs.read(&bytes[0], fileSize);

    return string(&bytes[0], fileSize);
}

Script* ScriptEngine::MakeScript(std::string file) {
  const std::string file_contents = LoadScript(file);
  return new Script(file, LoadScript(file));
}