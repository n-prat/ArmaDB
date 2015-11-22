// dllmain.cpp : Defines the entry point for the DLL application.

#include "dllmain-dev.h"


//void __stdcall RVExtension(char *output, int outputSize, const char *function)
void __stdcall RVExtension_Dev(char *output, int outputSize, const char *function)
{
	//__declspec (dllimport) void __stdcall RVExtension(char *output, int outputSize, const char *function);
	// call 
	RVExtension(output, outputSize, function);
}