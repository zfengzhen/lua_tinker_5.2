extern "C" 
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};

#include "lua_tinker.h"

int TestFunc(lua_State* L)
{
    printf("# TestFunc aaaaaa\n");
    return lua_yield(L, 0);
}

int TestFunc2(lua_State* L, float a)
{
    printf("# TestFunc2(L,%f) bbbbbb\n", a);
    return lua_yield(L, 0);
}

class TestClass
{
public:

    int TestFunc(lua_State* L)
    {
        printf("# TestClass::TestFunc aaaaaa\n");
        return lua_yield(L, 0);
    }

    int TestFunc2(lua_State* L, float a)
    {
        printf("# TestClass::TestFunc2(L,%f) bbbbbb\n", a);
        return lua_yield(L, 0);
    }
};

int main()
{
    lua_State* L = luaL_newstate();

    luaopen_base(L);
    luaopen_string(L);

    lua_tinker::def(L, "TestFunc", &TestFunc);
    lua_tinker::def(L, "TestFunc2", &TestFunc2);


    lua_tinker::class_add<TestClass>(L, "TestClass");
    lua_tinker::class_def<TestClass>(L, "TestFunc", &TestClass::TestFunc);
    lua_tinker::class_def<TestClass>(L, "TestFunc2", &TestClass::TestFunc2);

    TestClass g_test;
    lua_tinker::set(L, "g_test", &g_test);


    lua_tinker::dofile(L, "sample6.lua");

    lua_State* new_L = lua_newthread(L);
    lua_tinker::enum_stack(L);
    lua_tinker::enum_stack(new_L);

    lua_getglobal(L, "ThreadTest");

    printf("* lua_resume() 호출\n");
    lua_resume(L, L, 0);

    printf("* lua_resume() 호출\n");
    lua_resume(L, L, 0);

    printf("* lua_resume() 호출\n");
    lua_resume(L, L, 0);

    printf("* lua_resume() 호출\n");
    lua_resume(L, L, 0);

    printf("* lua_resume() 호출\n");
    lua_resume(L, L, 0);

    lua_close(L);

    return 0;
}

