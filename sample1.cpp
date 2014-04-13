#include <iostream>

#include <lua.hpp>
#include <stdint.h>
#include "lua_tinker.h"

int cpp_func(int arg1, int arg2)
{
	return arg1 + arg2;
}

int main()
{
	lua_State* L = luaL_newstate();

	luaopen_base(L);

    uint64_t zfz = 123;
    int zfz1 = 123;
    int zfz2 = 11213;

    lua_tinker::set(L, "task_id", zfz);
    lua_tinker::set(L, "rand_id", zfz1);

	lua_tinker::def(L, "cpp_func", cpp_func);

	lua_tinker::dofile(L, "sample1.lua");

	int result = lua_tinker::call<int>(L, "lua_func", 3, 4);

	printf("lua_func(3,4) = %d\n", result);

	lua_close(L);

	return 0;
}
