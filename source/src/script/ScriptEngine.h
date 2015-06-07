#ifndef SCRIPT_ENGINE_H
#define SCRIPT_ENGINE_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <lua.hpp>
#include "../util/luawrapper.hpp"
#include "../util/luawrapperutil.hpp"
#include "../render/LuaBatchedRenderCube.h"
#include "../LuaGame.h"
#include "../block/LuaBlock.h"
#include "../block/LuaBlockRegistry.h"
#include "../world/LuaDimension.h"
#include "Script.h"

int lua_time(lua_State *l);

int lua_drawbatch(lua_State *l);

int lua_drawcube(lua_State *l);

int lua_load_renderer(lua_State *l);

int lua_set_camera(lua_State *l);

int lua_get_block(lua_State *l);

int lua_get_block_by_name(lua_State *l);

int lua_test(lua_State *l);


class ScriptEngine {
public:
    const static std::string kDefaultScriptDir;

    ScriptEngine();

    ~ScriptEngine();

    /**
     * Initialises the script engine.
     * A lua state is created and default libraries are loaded.
     */
    int Init();

    /**
     * Register a C style function to a global lua name.
     *
     * @param c function to bind
     * @param global lua name of function
     */
    int RegisterFunction(lua_CFunction fn, std::string name);

    /**
     * Execute a string of lua code.
     *
     * @param lua string
     * @return 1 if succesful.
     */
    int Exec(const std::string lua_expression);

    /**
     * Run the script named file in the script folder.
     *
     * @param filename of script.
     * @return 1 if succesful
     */
    int Run(const std::string file);

    /**
     * Run the contents of the given script.
     *
     * @param A loaded script
     * @return 1 if successful
     */
    int Run(const Script *script);

    template <typename T>
    int Set(std::string name, T* ptr) {
        luaW_push<T>(state_, ptr);
        lua_setglobal(state_, name.c_str());
    }

    /**
     * Read a script from the script folder into a string.
     *
     * @param filename of script.
     */
    std::string LoadScript(const std::string file);

    /**
     * Make a script from given file.
     * Use for scripts that are frequently run.
     *
     * @param filename of script.
     * @return Script object that holds the script name and contents.
     */
    Script *MakeScript(std::string file);


    /** Accessors & mutators **/

    std::string script_dir() const { return script_dir_; }

    void set_script_dir(std::string dir) { script_dir_ = dir; };

protected:
private:
    lua_State *state_;
    std::string script_dir_;

};

#endif
