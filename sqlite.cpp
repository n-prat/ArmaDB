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

#include "stdafx.h"

#include "sqlite.h"



sqlite::sqlite()
{
	db = NULL;
	zErrMsg = "error";
	rc = -1;
	sql_custom_only = true;
}


sqlite::~sqlite()
{
}

int sqlite::setup_open(std::string filename)
{	

	rc = sqlite3_open_v2(filename.c_str(), &db, SQLITE_OPEN_READWRITE, nullptr);
	if (rc) {
		// Error opening DB
		sqlite3_close(db);
	}

	// TODO
	// stuff
	return rc;
}

int sqlite::setup_create(std::string filename)
{	

	rc = sqlite3_open_v2(filename.c_str(), &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE,nullptr);
	if (rc) {
		// Error opening DB
		sqlite3_close(db);
	}

	// TODO
	// stuff
	return rc;
}

int sqlite::close_db()
{
	rc = sqlite3_close(db);
	return rc;
}

const char * sqlite::get_err_msg()
{
	return sqlite3_errstr(rc);
}

// no values will be returned, no callback, etc
// mostly for testing
int sqlite::exec_simple(const char * sql)
{
	rc = sqlite3_exec(db, sql, nullptr, nullptr, nullptr);
	return rc;
}
