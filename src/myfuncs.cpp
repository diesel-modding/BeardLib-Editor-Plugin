#include "myfuncs.h"
#include <sys/stat.h>
#include <ctime>

int get_file_attribute(lua_State *L) {
	struct stat fileInfo;

	const char* path = luaL_checkstring(L, 1);
	const int attr = luaL_checkinteger(L, 2);

	if (stat(path, &fileInfo) != 0)
	{
		PD2HOOK_LOG_ERROR("Couldn't get file attribute");
		return 0;
	}

	switch (attr)
	{
		case 0:
			lua_pushinteger(L, fileInfo.st_size);
			break;
		case 1:
			lua_pushstring(L, std::ctime(&fileInfo.st_ctime));
			break;
		case 2:
			lua_pushstring(L, std::ctime(&fileInfo.st_mtime));
			break;
		default:
			PD2HOOK_LOG_ERROR("Couldn't get file attribute: attribute doesn't exist");
			return 0;
	}

	return 1;
}
