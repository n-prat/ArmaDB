#include "sqlite.h"



sqlite::sqlite()
{
	db = NULL;
	char *zErrMsg = "";
	int rc = 0;
}


sqlite::~sqlite()
{
}

void sqlite::setup_open(std::string filename)
{
	const char *zVfs;

	int rc = sqlite3_open_v2(filename.c_str(), &db, SQLITE_OPEN_READWRITE, zVfs);
	if (rc) {
		// Error opening DB
		sqlite3_close(db);
	}

	// TODO
	// stuff
}

void sqlite::setup_create(std::string filename)
{
	const char *zVfs;

	int rc = sqlite3_open_v2(filename.c_str(), &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE,zVfs);
	if (rc) {
		// Error opening DB
		sqlite3_close(db);
	}

	// TODO
	// stuff
}
