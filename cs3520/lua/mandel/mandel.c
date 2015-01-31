#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdio.h>

int calcPoint(lua_State *L);

int main() {
    // setup
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // register calcPoint function
    lua_pushcfunction(L, calcPoint);
    lua_setglobal(L, "calcPoint");

    // load lua file
    if (luaL_dofile(L, "mandel.lua")) {
        printf("Error in dofile\n");
    }

    // call generateImage
    lua_getglobal(L, "generateImage");
    lua_pushstring(L, "fractal.ppm");
    lua_pcall(L, 1, 0, 0);

    // shut down
    lua_close(L);
    return 0;
}

// z' = z*z + c
int calcPoint(lua_State *L) {
    double x = lua_tonumber(L, 1);
    double y = lua_tonumber(L, 2);
    double maxIters = lua_tonumber(L, 3);
    double a = x;
    double b = y;
    for (double i = 1.0; i <= maxIters; i += 1.0) {
        double a2 = a * a;
        double b2 = b * b;
        if (a2 + b2 >= 4.0) {
            lua_pushnumber(L, i);
            return 1;
        }
        double ab = a * b;
        b = ab + ab + y;
        a = a2 - b2 + x;
    }
    lua_pushnumber(L, 0.0);
    return 1;
}
