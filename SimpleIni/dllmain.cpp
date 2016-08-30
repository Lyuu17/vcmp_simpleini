#include "main.h"

PluginFuncs* pluginFuncs;

HSQAPI sq;
HSQUIRRELVM v;

extern "C" EXPORT unsigned int VcmpPluginInit(PluginFuncs* functions, PluginCallbacks* callbacks, PluginInfo* info) {
	printf("Loading SimpleIni... ");

	info->pluginVersion = 0x1200;
	strncpy(info->name, "SimpleIni", sizeof(info->name));

	info->apiMajorVersion = PLUGIN_API_MAJOR;
	info->apiMinorVersion = PLUGIN_API_MINOR;

	pluginFuncs = functions;

	callbacks->OnPluginCommand = OnPluginCommand;

	printf("done\n");

	return 1;
}