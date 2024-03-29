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

#include <string>
#include "sqlite3/sqlite3.h"

class statement
{
public:
	statement();
	~statement();

private:
	std::string name;		// name, from config file
	std::string sql;		// raw text from config file
	std::string type;		// bind or basic, from config file
	int nb_bindings;		// number of bindings from config

	int id;					// position in the vector in sqlite.h
	sqlite3_stmt **ppStmt;	// result from sqlite3_prepare()	

	std::string result;		// result of the query,sqlite3_step() and sqlite3_column()
};

