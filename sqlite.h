#pragma once

#include <string>
#include "sqlite3\sqlite3.h"

class sqlite
{
public:
	sqlite();
	~sqlite();

	int setup_open(std::string filename);
	int setup_create(std::string filename);

	int close_db();
	const char * get_err_msg();
private:
	sqlite3 *db;
	char *zErrMsg;
	int rc;
};

