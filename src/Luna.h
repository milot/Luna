#ifndef __LUNA_H__
#define __LUNA_H__

extern "C" {
    #include <lua/lua.hpp>
}

#include <string>

namespace Luna {
    class Script {
    public:
        Script();
        Script(std::string luaFile);
        virtual ~Script();

        bool loadLuaScript(std::string filename);
        bool luaFunctionExists(std::string functionName);
        int  executeLuaFunction(std::string functionName,
                                int parameterNumber,
                                int returnNumber);
        std::string getString(std::string globalVariableName);
        void setString(std::string globalVariableName,
                       std::string value);

        int getInteger(std::string globalVariableName);
        void setInteger(std::string globalVariableName,
                        int integerValue);
    private:
        lua_State *luaState;
        std::string resultCodeToString(int resultCode);
    };
}

#endif //__LUNA_H__
