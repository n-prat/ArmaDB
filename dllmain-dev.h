// dllmain-dev : wrapper to RVExtension, with renamed entry point
#pragma once

#include "dllmain.h"

// test ingame : hint ("Arma_db" callExtension "");
extern "C"
{
	__declspec (dllexport) void __stdcall RVExtension_Dev(char *output, int outputSize, const char *function);
}