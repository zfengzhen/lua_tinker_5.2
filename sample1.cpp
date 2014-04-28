#include <iostream>

#include <lua.hpp>
#include <stdint.h>
#include "lua_tinker.h"
enum NumEnum {
    ONE = 1,
    TWO = 2,
    THREE = 3,
};

int cpp_func(int arg1, int arg2)
{
    return arg1 + arg2;
}

void cpp_test_str(char* str)
{
    printf("%s\n", str);
}

int main()
{
    lua_State* L = luaL_newstate();

    luaopen_base(L);
    lua_tinker::init(L);

    uint64_t task_id = 120;
    uint64_t task_id2 = -1;
    uint64_t task_id3 = -2;
    int rand_id = 123;

    lua_tinker::set(L, "task_id", task_id);
    lua_tinker::set(L, "task_id2", task_id2);
    lua_tinker::set(L, "task_id3", task_id3);
    lua_tinker::set(L, "rand_id", rand_id);

    lua_tinker::set(L, "ONE", ONE);

    lua_tinker::def(L, "cpp_func", cpp_func);
    lua_tinker::def(L, "cpp_test_str", cpp_test_str);

    lua_tinker::dofile(L, "sample1.lua");

    int result = lua_tinker::call<int>(L, "lua_func", 3, 4);

    printf("lua_func(3,4) = %d\n", result);

    lua_close(L);

    return 0;
}
