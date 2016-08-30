# vcmp_simpleini
A VC-MP 0.4 module.

Functions available:
- INI_Open(string filename) -- returns the ini pointer.
- INI_SaveFile(ini pointer, filename).
- INI_IsEmpty(ini pointer, string filename).
- INI_SetUnicode(ini pointer, bool).
- INI_GetSectionSize(ini pointer, string section).
- INI_Exists(string filename).
- INI_Close(ini pointer).
- INI_SetString(ini pointer, string section, string key, string value).
- INI_SetBool(ini pointer, string section, string key, bool value).
- INI_SetFloat(ini pointer, string section, string key, float value).
- INI_SetInteger(ini pointer, string section, string key, integer value).
- INI_GetString(ini pointer, string section, string key).
- INI_GetBool(ini pointer, string section, string key).
- INI_GetFloat(ini pointer, string section, string key).
- INI_GetInteger(ini pointer, string section, string key).
