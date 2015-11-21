#pragma once

#include <string>
#include "sqlite3\sqlite3.h"

class sqlite
{
public:
	sqlite();
	~sqlite();

	void setup_open(std::string filename);
	void setup_create(std::string filename);

private:
	sqlite3 *db;
	char *zErrMsg;
	int rc;
};

