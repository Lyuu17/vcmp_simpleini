#include "main.h"

#include "SimpleIni.h"

extern PluginFuncs* pluginFuncs;

extern HSQAPI sq;
extern HSQUIRRELVM v;

_SQUIRRELDEF(INI_Open) {
	if (sq->gettype(v, 2) != OT_STRING) {
		return sq->throwerror(v, _SC("Error: Invalid filename."));
	}

	CSimpleIni *ini = new CSimpleIni();

	const SQChar *file;
	sq->getstring(v, 2, &file);

	ini->LoadFile(file);

	sq->pushuserpointer(v, ini);

	return 1;
}

_SQUIRRELDEF(INI_SaveFile) {
	if (sq->gettype(v, 2) != OT_USERPOINTER) {
		return sq->throwerror(v, _SC("Error: Invalid INI pointer."));
	}

	if (sq->gettype(v, 3) != OT_STRING) {
		return sq->throwerror(v, _SC("Error: Invalid filename."));
	}

	SQUserPointer ptr = NULL;
	sq->getuserpointer(v, 2, &ptr);

	CSimpleIni *ini = NULL;
	ini = (CSimpleIni*)ptr;

	const SQChar *file;
	sq->getstring(v, 3, &file);

	ini->SaveFile(file);

	return 1;
}

_SQUIRRELDEF(INI_Close) {
	if (sq->gettype(v, 2) != OT_USERPOINTER) {
		return sq->throwerror(v, _SC("Error: Invalid INI pointer."));
	}

	SQUserPointer ptr = NULL;
	sq->getuserpointer(v, 2, &ptr);

	CSimpleIni *ini = NULL;
	ini = (CSimpleIni*)ptr;

	ini->~CSimpleIniTempl();

	sq->pushbool(v, true);

	return 1;
}

_SQUIRRELDEF(INI_Exists) {
	if (sq->gettype(v, 2) != OT_STRING) {
		return sq->throwerror(v, _SC("Error: Invalid filename."));
	}

	const SQChar *name;
	sq->getstring(v, 2, &name);

	bool b = false;

	FILE *f;
	if (f = fopen(name, "r")) {
		b = true;
		fclose(f);
	}

	sq->pushbool(v, b);

	return 1;
}

_SQUIRRELDEF(INI_IsEmpty) {
	if (sq->gettype(v, 2) != OT_USERPOINTER) {
		return sq->throwerror(v, _SC("Error: Invalid INI pointer."));
	}

	SQUserPointer ptr = NULL;
	sq->getuserpointer(v, 2, &ptr);

	CSimpleIni *ini = NULL;
	ini = (CSimpleIni*)ptr;

	sq->pushbool(v, ini->IsEmpty());

	return 1;
}

_SQUIRRELDEF(INI_SetUnicode) {
	if (sq->gettype(v, 2) != OT_USERPOINTER) {
		return sq->throwerror(v, _SC("Error: Invalid INI pointer."));
	}

	if (sq->gettype(v, 3) != OT_BOOL) {
		return sq->throwerror(v, _SC("Error: Invalid bool: not true nor false."));
	}

	SQUserPointer ptr = NULL;
	sq->getuserpointer(v, 2, &ptr);

	CSimpleIni *ini = NULL;
	ini = (CSimpleIni*)ptr;

	SQBool val;
	sq->getbool(v, 3, &val);

	ini->SetUnicode(val);

	return 1;
}

_SQUIRRELDEF(INI_GetSectionSize) {
	if (sq->gettype(v, 2) != OT_USERPOINTER) {
		return sq->throwerror(v, _SC("Error: Invalid INI pointer."));
	}

	if (sq->gettype(v, 3) != OT_STRING) {
		return sq->throwerror(v, _SC("Error: Invalid section, not a string."));
	}

	SQUserPointer ptr = NULL;
	sq->getuserpointer(v, 2, &ptr);

	CSimpleIni *ini = NULL;
	ini = (CSimpleIni*)ptr;

	const SQChar *section;
	sq->getstring(v, 3, &section);

	sq->pushinteger(v, ini->GetSectionSize(section));

	return 1;
}

_SQUIRRELDEF(INI_DeleteSection) {
	if (sq->gettype(v, 2) != OT_USERPOINTER) {
		return sq->throwerror(v, _SC("Error: Invalid INI pointer."));
	}

	if (sq->gettype(v, 3) != OT_STRING) {
		return sq->throwerror(v, _SC("Error: Invalid section, not a string."));
	}

	if (sq->gettype(v, 4) != OT_STRING) {
		return sq->throwerror(v, _SC("Error: Invalid key, not a string."));
	}

	SQUserPointer ptr = NULL;
	sq->getuserpointer(v, 2, &ptr);

	CSimpleIni *ini = NULL;
	ini = (CSimpleIni*)ptr;

	const SQChar *section;
	sq->getstring(v, 3, &section);

	const SQChar *key;
	sq->getstring(v, 4, &key);

	ini->Delete(section, key, true);

	sq->pushbool(v, SQTrue);

	return 1;
}

_SQUIRRELDEF(INI_SetString) {
	if (sq->gettype(v, 2) != OT_USERPOINTER) {
		return sq->throwerror(v, _SC("Error: Invalid INI pointer."));
	}

	if (sq->gettype(v, 3) != OT_STRING) {
		return sq->throwerror(v, _SC("Error: Invalid section, not a string."));
	}

	if (sq->gettype(v, 4) != OT_STRING) {
		return sq->throwerror(v, _SC("Error: Invalid key, not a string."));
	}

	if (sq->gettype(v, 5) != OT_STRING) {
		return sq->throwerror(v, _SC("Error: Invalid value, not a string."));
	}

	SQUserPointer ptr = NULL;
	sq->getuserpointer(v, 2, &ptr);

	CSimpleIni *ini = NULL;
	ini = (CSimpleIni*)ptr;

	const SQChar *section;
	sq->getstring(v, 3, &section);

	const SQChar *key;
	sq->getstring(v, 4, &key);

	const SQChar *value;
	sq->getstring(v, 5, &value);

	ini->SetValue(section, key, value);

	sq->pushbool(v, SQTrue);

	return 1;
}

_SQUIRRELDEF(INI_SetBool) {
	if (sq->gettype(v, 2) != OT_USERPOINTER) {
		return sq->throwerror(v, _SC("Error: Invalid INI pointer."));
	}

	if (sq->gettype(v, 3) != OT_STRING) {
		return sq->throwerror(v, _SC("Error: Invalid section, not a string."));
	}

	if (sq->gettype(v, 4) != OT_STRING) {
		return sq->throwerror(v, _SC("Error: Invalid key, not a string."));
	}

	if (sq->gettype(v, 5) != OT_BOOL) {
		return sq->throwerror(v, _SC("Error: Invalid value, not a bool."));
	}

	SQUserPointer ptr = NULL;
	sq->getuserpointer(v, 2, &ptr);

	CSimpleIni *ini = NULL;
	ini = (CSimpleIni*)ptr;

	const SQChar *section;
	sq->getstring(v, 3, &section);

	const SQChar *key;
	sq->getstring(v, 4, &key);

	SQBool value;
	sq->getbool(v, 5, &value);

	ini->SetBoolValue(section, key, value);

	sq->pushbool(v, SQTrue);

	return 1;
}

_SQUIRRELDEF(INI_SetFloat) {
	if (sq->gettype(v, 2) != OT_USERPOINTER) {
		return sq->throwerror(v, _SC("Error: Invalid INI pointer."));
	}

	if (sq->gettype(v, 3) != OT_STRING) {
		return sq->throwerror(v, _SC("Error: Invalid section, not a string."));
	}

	if (sq->gettype(v, 4) != OT_STRING) {
		return sq->throwerror(v, _SC("Error: Invalid key, not a string."));
	}

	if (sq->gettype(v, 5) != OT_FLOAT) {
		return sq->throwerror(v, _SC("Error: Invalid value, not a float."));
	}

	SQUserPointer ptr = NULL;
	sq->getuserpointer(v, 2, &ptr);

	CSimpleIni *ini = NULL;
	ini = (CSimpleIni*)ptr;

	const SQChar *section;
	sq->getstring(v, 3, &section);

	const SQChar *key;
	sq->getstring(v, 4, &key);

	SQFloat value;
	sq->getfloat(v, 5, &value);

	ini->SetDoubleValue(section, key, value);

	sq->pushbool(v, SQTrue);

	return 1;
}

_SQUIRRELDEF(INI_SetInteger) {
	if (sq->gettype(v, 2) != OT_USERPOINTER) {
		return sq->throwerror(v, _SC("Error: Invalid INI pointer."));
	}

	if (sq->gettype(v, 3) != OT_STRING) {
		return sq->throwerror(v, _SC("Error: Invalid section, not a string."));
	}

	if (sq->gettype(v, 4) != OT_STRING) {
		return sq->throwerror(v, _SC("Error: Invalid key, not a string."));
	}

	if (sq->gettype(v, 5) != OT_INTEGER) {
		return sq->throwerror(v, _SC("Error: Invalid value, not an integer."));
	}

	SQUserPointer ptr = NULL;
	sq->getuserpointer(v, 2, &ptr);

	CSimpleIni *ini = NULL;
	ini = (CSimpleIni*)ptr;

	const SQChar *section;
	sq->getstring(v, 3, &section);

	const SQChar *key;
	sq->getstring(v, 4, &key);

	SQInteger value;
	sq->getinteger(v, 5, &value);

	ini->SetLongValue(section, key, value);

	sq->pushbool(v, SQTrue);

	return 1;
}

_SQUIRRELDEF(INI_GetString) {
	if (sq->gettype(v, 2) != OT_USERPOINTER) {
		return sq->throwerror(v, _SC("Error: Invalid INI pointer."));
	}

	if (sq->gettype(v, 3) != OT_STRING) {
		return sq->throwerror(v, _SC("Error: Invalid section, not a string."));
	}

	if (sq->gettype(v, 4) != OT_STRING) {
		return sq->throwerror(v, _SC("Error: Invalid key, not a string."));
	}

	SQUserPointer ptr = NULL;
	sq->getuserpointer(v, 2, &ptr);

	CSimpleIni *ini = NULL;
	ini = (CSimpleIni*)ptr;

	const SQChar *section;
	sq->getstring(v, 3, &section);

	const SQChar *key;
	sq->getstring(v, 4, &key);

	const char *str = ini->GetValue(section, key);
	if (str == 0 || sizeof str == 0 || strlen(str) == 0) {
		sq->pushnull(v);

		return 1;
	}

	sq->pushstring(v, str, strlen(str));

	return 1;
}

_SQUIRRELDEF(INI_GetBool) {
	if (sq->gettype(v, 2) != OT_USERPOINTER) {
		return sq->throwerror(v, _SC("Error: Invalid INI pointer."));
	}

	if (sq->gettype(v, 3) != OT_STRING) {
		return sq->throwerror(v, _SC("Error: Invalid section, not a string."));
	}

	if (sq->gettype(v, 4) != OT_STRING) {
		return sq->throwerror(v, _SC("Error: Invalid key, not a string."));
	}

	SQUserPointer ptr = NULL;
	sq->getuserpointer(v, 2, &ptr);

	CSimpleIni *ini = NULL;
	ini = (CSimpleIni*)ptr;

	const SQChar *section;
	sq->getstring(v, 3, &section);

	const SQChar *key;
	sq->getstring(v, 4, &key);

	bool b = ini->GetBoolValue(section, key);
	sq->pushbool(v, b);

	return 1;
}

_SQUIRRELDEF(INI_GetFloat) {
	if (sq->gettype(v, 2) != OT_USERPOINTER) {
		return sq->throwerror(v, _SC("Error: Invalid INI pointer."));
	}

	if (sq->gettype(v, 3) != OT_STRING) {
		return sq->throwerror(v, _SC("Error: Invalid section, not a string."));
	}

	if (sq->gettype(v, 4) != OT_STRING) {
		return sq->throwerror(v, _SC("Error: Invalid key, not a string."));
	}

	SQUserPointer ptr = NULL;
	sq->getuserpointer(v, 2, &ptr);

	CSimpleIni *ini = NULL;
	ini = (CSimpleIni*)ptr;

	const SQChar *section;
	sq->getstring(v, 3, &section);

	const SQChar *key;
	sq->getstring(v, 4, &key);

	double val = ini->GetDoubleValue(section, key);
	sq->pushfloat(v, val);

	return 1;
}

_SQUIRRELDEF(INI_GetInteger) {
	if (sq->gettype(v, 2) != OT_USERPOINTER) {
		return sq->throwerror(v, _SC("Error: Invalid INI pointer."));
	}

	if (sq->gettype(v, 3) != OT_STRING) {
		return sq->throwerror(v, _SC("Error: Invalid section, not a string."));
	}

	if (sq->gettype(v, 4) != OT_STRING) {
		return sq->throwerror(v, _SC("Error: Invalid key, not a string."));
	}

	SQUserPointer ptr = NULL;
	sq->getuserpointer(v, 2, &ptr);

	CSimpleIni *ini = NULL;
	ini = (CSimpleIni*)ptr;

	const SQChar *section;
	sq->getstring(v, 3, &section);

	const SQChar *key;
	sq->getstring(v, 4, &key);

	SQInteger val = ini->GetLongValue(section, key);
	sq->pushinteger(v, val);

	return 1;
}

_SQUIRRELDEF(INI_Reset) {
	if (sq->gettype(v, 2) != OT_USERPOINTER) {
		return sq->throwerror(v, _SC("Error: Invalid INI pointer."));
	}

	SQUserPointer ptr = NULL;
	sq->getuserpointer(v, 2, &ptr);

	CSimpleIni *ini = NULL;
	ini = (CSimpleIni*)ptr;

	ini->Reset();

	sq->pushbool(v, true);

	return 1;
}

// -----------------------------------------------------------------

void RegisterSquirrelFunc(HSQUIRRELVM v, SQFUNCTION f, const SQChar* fname, unsigned char ucParams, const SQChar* szParams) {
	char szNewParams[32];

	sq->pushroottable(v);
	sq->pushstring(v, fname, -1);
	sq->newclosure(v, f, 0);

	if (ucParams > 0) {
		ucParams++;

		sprintf(szNewParams, "t%s", szParams);

		sq->setparamscheck(v, ucParams, szNewParams);
	}

	sq->setnativeclosurename(v, -1, fname);
	sq->newslot(v, -3, SQFalse);
	sq->pop(v, 1);
}

void RegisterFuncs(HSQUIRRELVM v) {
	RegisterSquirrelFunc(v, INI_Open, "INI_Open", 0, 0);
	RegisterSquirrelFunc(v, INI_SaveFile, "INI_SaveFile", 0, 0);
	RegisterSquirrelFunc(v, INI_IsEmpty, "INI_IsEmpty", 0, 0);
	RegisterSquirrelFunc(v, INI_SetUnicode, "INI_SetUnicode", 0, 0);
	RegisterSquirrelFunc(v, INI_GetSectionSize, "INI_GetSectionSize", 0, 0);
	RegisterSquirrelFunc(v, INI_Exists, "INI_Exists", 0, 0);
	RegisterSquirrelFunc(v, INI_Close, "INI_Close", 0, 0);

	RegisterSquirrelFunc(v, INI_SetString, "INI_SetString", 0, 0);
	RegisterSquirrelFunc(v, INI_SetBool, "INI_SetBool", 0, 0);
	RegisterSquirrelFunc(v, INI_SetFloat, "INI_SetFloat", 0, 0);
	RegisterSquirrelFunc(v, INI_SetInteger, "INI_SetInteger", 0, 0);

	RegisterSquirrelFunc(v, INI_GetString, "INI_GetString", 0, 0);
	RegisterSquirrelFunc(v, INI_GetBool, "INI_GetBool", 0, 0);
	RegisterSquirrelFunc(v, INI_GetFloat, "INI_GetFloat", 0, 0);
	RegisterSquirrelFunc(v, INI_GetInteger, "INI_GetInteger", 0, 0);

	RegisterSquirrelFunc(v, INI_Reset, "INI_Reset", 0, 0);
}