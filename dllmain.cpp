// dllmain.cpp : Defines the entry point for the DLL application.

#include "dllmain.h"

INITIALIZE_EASYLOGGINGPP

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
	sqlite sq();

	// Split function on delimiter ":"
	std::string str_args(function);

	// Split the input and store the result in "args"
	std::vector<std::string> args;
	split_to_container(args, str_args, ":", split::no_empties);	
	int nb_args = args.size();

	// Parse argument
	if (nb_args == 0) {
		// Hello World if empty
		LOG(DEBUG) << "Hello World!!";
		strncpy_s(output, outputSize, "Hello World!!", _TRUNCATE);
	}
	else {		
		char buffer[50];
		std::string debug(function);
		LOG(ERROR) << "INPUT not recognized: " << debug;
		strncpy_s(output, outputSize, "INPUT not recognized", _TRUNCATE);
	}
	
}

