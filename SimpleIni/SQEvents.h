#ifdef WIN32
	#define EXPORT __declspec(dllexport)
#else
	#define EXPORT
#endif

uint8_t OnPluginCommand(uint32_t commandIdentifier, const char* message);

void OnSquirrelScriptLoad();