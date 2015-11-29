/*

	ArmaDB - Arma Extension which allows to connect to SQLite
	Copyright (C) 2015  Nathan Prat

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, version 3 of the License.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#include "dllmain.h"
#include <cstring>
#include <boost/algorithm/string/constants.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "easylogging++.h"
#include "sqlite.h"
#include "config.h"

INITIALIZE_EASYLOGGINGPP

#ifdef _WIN32
BOOL APIENTRY DllMain(HMODULE,
	DWORD  ul_reason_for_call,
	LPVOID
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
#endif

#ifdef _WIN32
void __stdcall RVExtension(char *output, int outputSize, const char *function)
#else
void RVExtension(char *output, int outputSize, const char *function)
#endif
{		
	sqlite sq;
	std::string out("");
	bool initialized = false;
	ConfigParser cfg;

	// Split function on delimiter ":"
	// store the result in "args"
	std::string str_args(function);
	std::vector<std::string> args;
	boost::split( args, str_args, boost::is_any_of(": "), boost::token_compress_on);
	int nb_args = args.size();

	// Parse argument
	if (nb_args == 1) {
		if (args[0].compare("version") == 0) {
			// Version number if no argument
			LOG(DEBUG) << "[armadb] version";
			//strncpy_s(output, outputSize, "Hello World!!", _TRUNCATE);
			out = "[armadb] version ";
			std::string version_string = boost::str(boost::format(" %1%.%2%.%3%") % MAJOR % MINOR % REVISION);
			out.append(version_string);
		}
	}
	else if (nb_args == 2) {
		//		input : "SETUP:dbname"

		if (args[0].compare("SETUP") == 0) {
			sq.setName(args[1]);
			initialized = true;

			// TODO error handling
			if (cfg.read_config("config.ini")) {
				out = "SETUP: can't read config file";
			}
			if (cfg.load_config()) {
				out = cfg.get_err_msg();
			}

			out = "SETUP ok";
		}
		else {
			out = "SETUP command invalid: USAGE: SETUP:name";
		}
	}
	else if (nb_args == 3) {
		//		input : "SQL:SIMPLE:statement"
		//exec_simple(const char *sql);
		// or	input : "SQL:QUERY:statement"

		if (initialized) {
			if (sq.open()) {				
				out = "CAN NOT OPEN DB" ;				
			}
			else {
				// DB ok, we can query

				// exec2(sq.exec(getStatementByName(statement)))
				// res = sq.getResult()
			}
		}
		else {
			out = "DB not initialized, use SETUP:name";
		}		
	}
	else {
		//		input : "BIND:stmtName:value1:value2:..."
		if (args[0].compare("BIND") == 0) {
			// stmt = getStatementByName(stmtName)

			// check number of parameters
			// if stmt.nb_param != (nb_args - 2)
			// out = "BIND invalid number of bindings";
		}
		else {
			std::string debug(function);
			LOG(ERROR) << "INPUT not recognized " << debug;
			out = "INPUT not recognized";
		}
	}

	// close db after each use
	if (sq.close_db()) {
		out = sq.get_err_msg();
	}

	// Send back the result
	// Size check
	if (out.size() >= (size_t) outputSize) {
		output = "";
		//TODO log error		
	}
	else {
		std::size_t length = out.copy(output, out.size(), 0);
		output[length] = '\0';
	}
}


// TODO
// * check output dir for sqlite : default = Arma's root
