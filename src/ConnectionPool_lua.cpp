#include <lua5.3/lua.h>
#include "ConnectionPool.h"

static int lua_getInstance(lua_State* L) {
    ConnectionPool* cp = ConnectionPool::getConnectionPool();
    lua_pushlightuserdata(L, cp);
    return 1;
}


