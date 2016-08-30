#include "main.h"

#include "SimpleIni.h"

extern PluginFuncs* pluginFuncs;

extern HSQAPI sq;
extern HSQUIRRELVM v;

_SQUIRRELDEF(INI_Open) {
	CSimpleIni *ini = new CSimpleIni();

	const SQChar *file;
	sq->getstring(v, 2, &file);

	ini->LoadFile(file);

	sq->pushuserpointer(v, ini);

	return 1;
}

_SQUIRRELDEF(INI_SaveFile) {
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
	SQUserPointer ptr = NULL;
	sq->getuserpointer(v, 2, &ptr);

	CSimpleIni *ini = NULL;
	ini = (CSimpleIni*)ptr;

	ini->~CSimpleIniTempl();

	sq->pushbool(v, true);

	return 1;
}

_SQUIRRELDEF(INI_Exists) {
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
	SQUserPointer ptr = NULL;
	sq->getuserpointer(v, 2, &ptr);

	CSimpleIni *ini = NULL;
	ini = (CSimpleIni*)ptr;

	sq->pushbool(v, ini->IsEmpty());

	return 1;
}

_SQUIRRELDEF(INI_SetUnicode) {
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

	ini->Delete(section, key, true);

	sq->pushbool(v, SQTrue);

	return 1;
}

_SQUIRRELDEF(INI_SetString) {
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

_SQUIRRELDEF(INI_ReadString) {
	SQUserPointer ptr = NULL;
	sq->getuserpointer(v, 2, &ptr);

	CSimpleIni *ini = NULL;
	ini = (CSimpleIni*)ptr;

	const SQChar *section;
	sq->getstring(v, 3, &section);

	const SQChar *key;
	sq->getstring(v, 4, &key);

	const char *str = ini->GetValue(section, key);
	sq->pushstring(v, str, strlen(str));

	return 1;
}

_SQUIRRELDEF(INI_ReadBool) {
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

_SQUIRRELDEF(INI_ReadFloat) {
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

_SQUIRRELDEF(INI_ReadInteger) {
	SQUserPointer ptr = NULL;
	sq->getuserpointer(v, 2, &ptr);

	CSimpleIni *ini = NULL;
	ini = (CSimpleIni*)ptr;

	const SQChar *section;
	sq->getstring(v, 3, &section);

	const SQChar *key;
	sq->getstring(v, 4, &key);

	long val = ini->GetLongValue(section, key);
	sq->pushinteger(v, val);

	return 1;
}

_SQUIRRELDEF(INI_Reset) {
	SQUserPointer ptr = NULL;
	sq->getuserpointer(v, 2, &ptr);

	CSimpleIni *ini = NULL;
	ini = (CSimpleIni*)ptr;

	const SQChar *section;
	sq->getstring(v, 3, &section);

	const SQChar *key;
	sq->getstring(v, 4, &key);

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
	RegisterSquirrelFunc(v, INI_SetString, "INI_SetInteger", 0, 0);

	RegisterSquirrelFunc(v, INI_ReadString, "INI_ReadString", 0, 0);
	RegisterSquirrelFunc(v, INI_ReadBool, "INI_ReadBool", 0, 0);
	RegisterSquirrelFunc(v, INI_ReadFloat, "INI_ReadFloat", 0, 0);
	RegisterSquirrelFunc(v, INI_ReadInteger, "INI_ReadInteger", 0, 0);

	RegisterSquirrelFunc(v, INI_Reset, "INI_Reset", 0, 0);
}