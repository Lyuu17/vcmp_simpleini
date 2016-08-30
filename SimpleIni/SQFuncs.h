#pragma once

#define _SQUIRRELDEF( x ) SQInteger x( HSQUIRRELVM v )

void					RegisterSquirrelFunc(HSQUIRRELVM v, SQFUNCTION f, const SQChar* fname, unsigned char uiParams, const SQChar* szParams);
void					RegisterFuncs(HSQUIRRELVM v);