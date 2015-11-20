// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

// test ingame : hint ("Arma_db" callExtension "");
extern "C"
{
	__declspec (dllexport) void __stdcall RVExtension(char *output, int outputSize, const char *function);
}
