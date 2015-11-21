// dllmain.cpp : Defines the entry point for the DLL application.

#include "dllmain.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

void __stdcall RVExtension(char *output, int outputSize, const char *function)
{
	// Split function on delimiter ":"
	std::string str_args(function);

	// Split the input and store the result in "args"
	std::vector<std::string> args;
	split_to_container(args, str_args, ":", split::no_empties);	
	int nb_args = args.size();

	// Hello World : empty argument
	if (nb_args == 0) {
		strncpy_s(output, outputSize, "Hello World!!", _TRUNCATE);
	}
	else {		
		char buffer[50];
		sprintf(buffer, "Unknown: input size = %d", nb_args);
		strncpy_s(output, outputSize, buffer, _TRUNCATE);
	}
	
}

