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
#include <boost/format.hpp>
#include "../sqlite.h"
#include "../config.h"
#include "../dllmain.h"


// as per https://community.bistudio.com/wiki/Extensions
#define OUTPUTSIZE 4096

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest3
{		
	TEST_CLASS(ArgumentsParsing)
	{
	public:
		
		// If "function" arg is empty, should reply "[armadb] version VERSION"
		TEST_METHOD(version)
		{			
			char out[OUTPUTSIZE], *fun = "version";

			std::string expected = "[armadb] version ";
			std::string version_string = boost::str(boost::format(" %1%.%2%.%3%") % MAJOR % MINOR % REVISION);
			expected.append(version_string);

			RVExtension(out, OUTPUTSIZE, fun);
			Assert::AreEqual(
				// Expected value:
				expected.c_str(),
				// Actual value:
				out,
				// Message:
				L"version check failed");
		}

		TEST_METHOD(output_size_too_big)
		{
			char out[50], fun[] = "sdf:aze:hg:xcv:jgh:oiu:qsd:xcv:ytuiy:sdfsfdg";
			RVExtension(out, 11, fun);
			// "RESULT too big : > outputSize"
			Assert::AreEqual("", out, L"output_size_too_big failed");
		}

		TEST_METHOD(output_size_segfault)
		{			
			char fun[] = "version";
			char *out = (char *) malloc(sizeof(char) * 10);
			RVExtension(out, 8000, fun);
			Assert::AreEqual("[armadb] version 0.0.1", out, L"output_size_segfault failed");
		}
		
		TEST_METHOD(segfault)
		{			
			size_t outputSize = 4096;
			char *out = (char *)malloc(sizeof(char) * 4080);
			bool ok = false;
			memset(out, 5, outputSize);

			Assert::AreEqual(true, ok, L"segfault failed");
		}

		TEST_METHOD(check__outputsize_segfault)
		{			
			size_t outputSize = 4000;
			char *out = (char *)malloc(sizeof(char) * 1000);
			int segfault = check_segfault(out, outputSize);
			segfault = -1;
			Assert::AreEqual(1, segfault, L"check_segfault failed");
		}

		TEST_METHOD(setup)
		{
			char out[OUTPUTSIZE], fun[] = "SETUP:name";
			RVExtension(out, OUTPUTSIZE, fun);
			Assert::AreEqual("SETUP ok", out, L"setup failed");
		}

		TEST_METHOD(initialized)
		{
			char out[OUTPUTSIZE], fun[] = "SETUP:name";
			RVExtension(out, OUTPUTSIZE, fun);
			Assert::AreEqual("SETUP ok", out, L"setup failed");
		}

		TEST_METHOD(not_initialized)
		{
			char out[OUTPUTSIZE], fun[] = "SETUP:ljknghfjhokoredkhdhlk";
			RVExtension(out, OUTPUTSIZE, fun);
			Assert::AreEqual("SETUP ok", out, L"setup failed");
		}
		
		TEST_METHOD(too_many_args)
		{
			char out[OUTPUTSIZE], fun[] = "sdf:aze:hg:xcv:jgh:oiu:qsd:xcv:ytuiy:sdfsfdg";
			RVExtension(out, OUTPUTSIZE, fun);
			Assert::AreEqual("INPUT not recognized", out, L"too_many_args failed");
		}
		
		TEST_METHOD(two_args_not_valid)
		{
			char out[OUTPUTSIZE], fun[] = "sdf:aze";
			RVExtension(out, OUTPUTSIZE, fun);
			Assert::AreEqual("SETUP command invalid: USAGE: SETUP:name", out, L"two_args_not_valid failed");
		}
		
		TEST_METHOD(two_args_valid1)
		{
			char out[OUTPUTSIZE], fun[] = "SETUP:pofldg";
			RVExtension(out, OUTPUTSIZE, fun);
			Assert::AreEqual("SETUP ok", out, L"two_args_valid1 failed");
		}		
	};
		

	TEST_CLASS(SQliteSQLsimple)
	{
	public:
		
		TEST_METHOD(sqlite_simple_read_exists)
		{
			sqlite sq;
			//sq.setup_create("plop.db");
			sq.setName("plop.db");
			sq.open();

			sq.exec_simple("CREATE TABLE examp(id int PRIMARY KEY, positions text, directions text);");
			sq.exec_simple("SELECT * FROM examp;");
			Assert::AreEqual("not an error", sq.get_err_msg(), L"sqlite_simple failed");
		}

		TEST_METHOD(sqlite_simple_read_not_exists)
		{
			sqlite sq;
			//sq.setup_create("plop.db");
			sq.setName("plop.db");
			sq.open();

			sq.exec_simple("SELECT * FROM examp2;");
			Assert::AreEqual("SQL logic error or missing database", sq.get_err_msg(), L"sqlite_simple failed");
		}

		// CREATE TABLE examp(one text, two int);
		// .tables; .schema; SELECT * FROM truc;
		TEST_METHOD(sqlite_create_table)
		{
			sqlite sq;
			sq.setName("plop.db");
			sq.open();

			sq.exec_simple("CREATE TABLE races2(id int PRIMARY KEY, positions text, directions text);");
			Assert::AreEqual("SQL logic error or missing database", sq.get_err_msg(), L"sqlite_create_table failed");
		}		
	};

	TEST_CLASS(SQliteClose)
	{
	public:
		TEST_METHOD(sqlite_close)
		{
			sqlite sq;
			std::string filename = "plop.db";

			sq.close_db();
			Assert::AreEqual("not an error", sq.get_err_msg(), L"sqlite_close_exists failed");
		}
		
	};

	TEST_CLASS(ConfigFile)
	{
	public:	
		TEST_METHOD(config_check)
		{
			ConfigParser cfg;
			cfg.read_config("../../tests/config.ini");
			cfg.load_config();
			std::string str = cfg.get_err_msg();

			Assert::AreEqual("Config file OK", str.c_str(), L"config_check failed");
		}
	};
}
