#include "main.h"

extern PluginFuncs* pluginFuncs;

extern HSQAPI sq;
extern HSQUIRRELVM v;

void OnSquirrelScriptLoad() {
	size_t size;
	int32_t sqId = pluginFuncs->FindPlugin("SQHost2");

	if (sqId == -1) return;

	void **sqExports = (void**)pluginFuncs->GetPluginExports(sqId, &size);

	if (sqExports == NULL && size <= 0) return;

	SquirrelImports ** sqDerefFuncs = (SquirrelImports **)sqExports;
	SquirrelImports * sqFuncs = (SquirrelImports *)(*sqDerefFuncs);

	if (!sqFuncs) {
		printf("Failed to attach to SQHost2\n");

		return;
	}

	sq = *(sqFuncs->GetSquirrelAPI());
	v = *(sqFuncs->GetSquirrelVM());

	RegisterFuncs(v);
}

uint8_t OnPluginCommand(uint32_t commandIdentifier, const char* message) {
	switch (commandIdentifier) {
	case 0x7D6E22D8:
		OnSquirrelScriptLoad();
		break;
	}
	return true;
}