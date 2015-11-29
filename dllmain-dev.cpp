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

#include "dllmain-dev.h"

#ifdef _WIN32
void __stdcall RVExtension_Dev(char *output, int outputSize, const char *function)
#else
void RVExtension_Dev(char *output, int outputSize, const char *function)
#endif
{
	//__declspec (dllimport) void __stdcall RVExtension(char *output, int outputSize, const char *function);
	// call 
	RVExtension(output, outputSize, function);
}
