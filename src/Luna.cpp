#include "Luna.h"
#include <iostream>

Luna::Script::Script() {
    luaState = lua_open();
    luaL_openlibs(luaState);
}

Luna::Script::Script(std::string luaFile) {
    Luna::Script();
    Luna::Script::loadLuaScript(luaFile);
}

bool Luna::Script::loadLuaScript(std::string filename) {
    bool result = false;
    try {
       	luaL_loadfile(luaState, "player.lua");
    } catch (...) {
        result = false;
    }
    result = true;

    return result;
}

bool Luna::Script::luaFunctionExists(std::string functionName) {
    lua_getglobal(luaState, functionName.c_str());

    bool result = !lua_isnil(luaState, -1);

    lua_pop(luaState, 1);

    return result;
}

int Luna::Script::executeLuaFunction(std::string functionName,
                                          int parameterNumber,
                                          int returnNumber) {
    int errorHandler = 0;
    int result = 0;

    // Error handling
    lua_getglobal(luaState, "debug");
    lua_getfield(luaState, -1, "traceback");
    errorHandler = lua_gettop(luaState);

    lua_getglobal(luaState, functionName.c_str());
    result = lua_pcall(luaState, parameterNumber, returnNumber, errorHandler);


    if (result != 0) {
        // error calling function
        std::cout << "Function call failed " <<
                     resultCodeToString(result) <<
                     " " << lua_tostring(luaState, -1);
    }

    // cleanup
    lua_pop(luaState, 1);

    return result;
}

std::string Luna::Script::getString(std::string globalVariableName) {
    std::string result = "";
    lua_getglobal(luaState, globalVariableName.c_str());
    result = lua_tostring(luaState, -1);
    lua_pop(luaState, 1);

    return result;
}

void Luna::Script::setString(std::string globalVariableName,
                                                  std::string value) {
    lua_pushstring(luaState, value.c_str());
    lua_setglobal(luaState, globalVariableName.c_str());
}

void Luna::Script::setInteger(std::string globalVariableName,
                                            int integerValue) {
    lua_pushinteger(luaState, integerValue);
    lua_setglobal(luaState, globalVariableName.c_str());
}

int Luna::Script::getInteger(std::string globalVariableName) {
    int value = 0;
    lua_getglobal(luaState, globalVariableName.c_str());
    value = lua_tonumber(luaState, -1);
    lua_pop(luaState, 1);
    return value;
}


std::string Luna::Script::resultCodeToString(int resultCode) {
    std::string resultString;
    switch(resultCode) {
    case 0:
        resultString = "LUNA :: Success";
        break;
    case LUA_ERRRUN:
        resultString = "LUNA :: Runtime error.";
        break;
    case LUA_ERRSYNTAX:
        resultString = "LUNA :: Syntax error";
        break;
    case LUA_ERRFILE:
        resultString = "LUNA :: Can't read file!";
        break;
    default:
        resultString = "Unknown error";
        break;
    }

    return resultString;
}


Luna::Script::~Script() {
    lua_close(luaState);
}
