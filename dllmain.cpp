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
	sqlite sq;
	std::string out("");

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
		//strncpy_s(output, outputSize, "Hello World!!", _TRUNCATE);
		out = "Hello World!!";
	}
	else if (nb_args == 2) {
		//		input : "OPEN:filename"
		// or	input : "OPENCREATE:filename"
		if (args[0].compare("OPEN") == 0) {
			if (sq.setup_open(args[1])) {
				std::string msg(sq.get_err_msg());
				out = "SETUP error: " + msg;
			}
		}
		else if (args[0].compare("OPENCREATE") == 0) {
			if (sq.setup_create(args[1])) {
				std::string msg(sq.get_err_msg());
				out = "SETUP error: " + msg;
			}			
		}
		else {			
			out = "SETUP command invalid: USAGE: OPEN:filename or OPENCREATE:filename";
		}
	}
	else if (nb_args == 3) {
		//		input : "SQL:SIMPLE:statement"
		// or	input : "SQL:QUERY:statement"
	}
	else {				
		std::string debug(function);
		LOG(ERROR) << "INPUT not recognized " << debug;
		out = "INPUT not recognized";
	}	
	
	// Send back the result
	strncpy_s(output, outputSize, out.c_str(), _TRUNCATE);
}

