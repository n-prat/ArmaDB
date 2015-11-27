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

#pragma once

#include "config.h"
#include "sqlite.h"
#include "easylogging++.h"
//#include <boost/program_options/parsers.hpp>

#define MAJOR 0
#define MINOR 0
#define REVISION 1

// test ingame : hint ("Arma_db" callExtension "");
extern "C"
{
	__declspec (dllexport) void __stdcall RVExtension(char *output, int outputSize, const char *function);
}

// Split string into a container
// http://www.cplusplus.com/faq/sequences/strings/split/#string-find_first_of
struct split
{
	enum empties_t { empties_ok, no_empties };
};

template <typename Container>
Container& split_to_container(
	Container&                            result,
	const typename Container::value_type& s,
	const typename Container::value_type& delimiters,
	split::empties_t                      empties = split::empties_ok)
{
	result.clear();
	size_t current;
	size_t next = -1;
	do
	{
		if (empties == split::no_empties)
		{
			next = s.find_first_not_of(delimiters, next + 1);
			if (next == Container::value_type::npos) break;
			next -= 1;
		}
		current = next + 1;
		next = s.find_first_of(delimiters, current);
		result.push_back(s.substr(current, next - current));
	} while (next != Container::value_type::npos);
	return result;
}


