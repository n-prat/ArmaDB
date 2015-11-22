// dllmain.h : Defines the entry point for the DLL application.
#pragma once

#include "stdafx.h"

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