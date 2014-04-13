extern "C" 
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
};

#include "lua_tinker.h"

int main()
{
	lua_State* L = luaL_newstate();

	luaL_openlibs(L);

    // 创建table haha
	lua_tinker::table haha(L, "haha");

    // 设置数值
	haha.set("value", 1);

    // 设置table
	haha.set("inside", lua_tinker::table(L));

    // 获取inside
	lua_tinker::table inside = haha.get<lua_tinker::table>("inside");

    // 插入数值
	inside.set("value", 2);

    // 运行脚本
	lua_tinker::dofile(L, "sample4.lua");

    // 从lua获取变量
	const char* test = haha.get<const char*>("test");
	printf("haha.test = %s\n", test);

    lua_tinker::table from_lua_table(L, "lua_table");
	printf("lua_table[2] = %d\n", from_lua_table.get<int>(4));

    // 调用lua函数
	lua_tinker::call<void>(L, "print_table", from_lua_table);

    // 新建一个表格
	lua_tinker::table temp(L);

    // 设置值
	temp.set("name", "local table !!");

    // 调用lua函数
	lua_tinker::call<void>(L, "print_table", temp);

    // 调用lua函数
	lua_tinker::table ret = lua_tinker::call<lua_tinker::table>(L, "return_table", "give me a table !!");
	printf("ret.name =\t%s\n", ret.get<const char*>("name"));

	lua_close(L);

	return 0;
}

