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
			char out[OUTPUTSIZE], *fun = "";

			std::string expected = "[armadb] version ";
			std::string version_string = boost::str(boost::format(" %1%.%2%.%3%") % MAJOR % MINOR % REVISION);
			expected.append(version_string);

			RVExtension(out, OUTPUTSIZE, fun);
			Assert::AreEqual(
				// Expected value:
				expected.c_str(),
				// Actual value:
				out,
				// Tolerance:
				0.01,
				// Message:
				L"version check failed",
				// Line number - used if there is no PDB file:
				LINE_INFO());
		}

		TEST_METHOD(output_size_too_big)
		{
			char out[OUTPUTSIZE], fun[] = "sdf:aze:hg:xcv:jgh:oiu:qsd:xcv:ytuiy:sdfsfdg";
			RVExtension(out, 11, fun);
			// "RESULT too big : > outputSize"
			Assert::AreEqual("RESULT too", out, 0.01, L"output_size_too_big failed", LINE_INFO());
		}

		TEST_METHOD(setup)
		{
			char out[OUTPUTSIZE], fun[] = "SETUP:name";
			RVExtension(out, OUTPUTSIZE, fun);
			Assert::AreEqual("SETUP ok", out, 0.01, L"setup failed", LINE_INFO());
		}

		TEST_METHOD(initialized)
		{
			char out[OUTPUTSIZE], fun[] = "SETUP:name";
			RVExtension(out, OUTPUTSIZE, fun);
			Assert::AreEqual("SETUP ok", out, 0.01, L"setup failed", LINE_INFO());
		}

		TEST_METHOD(not_initialized)
		{
			char out[OUTPUTSIZE], fun[] = "SETUP:ljknghfjhokoredkhdhlk";
			RVExtension(out, OUTPUTSIZE, fun);
			Assert::AreEqual("SETUP ok", out, 0.01, L"setup failed", LINE_INFO());
		}
		
		TEST_METHOD(too_many_args)
		{
			char out[OUTPUTSIZE], fun[] = "sdf:aze:hg:xcv:jgh:oiu:qsd:xcv:ytuiy:sdfsfdg";
			RVExtension(out, OUTPUTSIZE, fun);
			Assert::AreEqual("INPUT not recognized", out, 0.01, L"too_many_args failed", LINE_INFO());
		}
		
		TEST_METHOD(two_args_not_valid)
		{
			char out[OUTPUTSIZE], fun[] = "sdf:aze";
			RVExtension(out, OUTPUTSIZE, fun);
			Assert::AreEqual("SETUP command invalid: USAGE: SETUP:name", out, 0.01, L"two_args_not_valid failed", LINE_INFO());
		}
		
		TEST_METHOD(two_args_valid1)
		{
			char out[OUTPUTSIZE], fun[] = "SETUP:pofldg";
			RVExtension(out, OUTPUTSIZE, fun);
			Assert::AreEqual("SETUP ok", out, 0.01, L"two_args_valid1 failed", LINE_INFO());
		}

		TEST_METHOD(split_to_container_1)
		{			
			const char *function = "dfgfd:xcwb:poiuyt:dsgf";
			std::string str_test(function);

			std::vector<std::string> fields;
			split_to_container(fields, str_test, ":", split::no_empties);

			Assert::AreNotEqual(3, fields.size(), 0.01, L"split_to_container_1 failed", LINE_INFO());
		}

		TEST_METHOD(split_to_container_2)
		{
			const char *function = "dfgfd:xcwb::poiuyt";
			std::string str_test(function);

			std::vector<std::string> fields;
			split_to_container(fields, str_test, ":", split::no_empties);

			Assert::AreEqual(3, fields.size(), 0.01, L"split_to_container_2 failed", LINE_INFO());
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
			Assert::AreEqual("not an error", sq.get_err_msg(), 0.01, L"sqlite_simple failed", LINE_INFO());
		}

		TEST_METHOD(sqlite_simple_read_not_exists)
		{
			sqlite sq;
			//sq.setup_create("plop.db");
			sq.setName("plop.db");
			sq.open();

			sq.exec_simple("SELECT * FROM examp2;");
			Assert::AreEqual("SQL logic error or missing database", sq.get_err_msg(), 0.01, L"sqlite_simple failed", LINE_INFO());
		}

		// CREATE TABLE examp(one text, two int);
		// .tables; .schema; SELECT * FROM truc;
		TEST_METHOD(sqlite_create_table_2times)
		{
			sqlite sq;
			//sq.setup_create("plop.db");
			sq.setName("plop.db");
			sq.open();

			sq.exec_simple("CREATE TABLE races2(id int PRIMARY KEY, positions text, directions text);");
			sq.exec_simple("CREATE TABLE races2(id int PRIMARY KEY, positions text, directions text);");
			Assert::AreEqual("SQL logic error or missing database", sq.get_err_msg(), 0.01, L"sqlite_create_table_2times failed", LINE_INFO());
		}

		TEST_METHOD(sqlite_create_ifnotexists)
		{
			sqlite sq;
			//sq.setup_create("plop.db");
			sq.setName("plop.db");
			sq.open();

			sq.exec_simple("CREATE TABLE IF NOT EXISTS races0(id int PRIMARY KEY, positions text, directions text);");
			sq.exec_simple("CREATE TABLE IF NOT EXISTS races0(id int PRIMARY KEY, positions text, directions text);");
			Assert::AreEqual("not an error", sq.get_err_msg(), 0.01, L"sqlite_create_ifnotexists failed", LINE_INFO());
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
			Assert::AreEqual("not an error", sq.get_err_msg(), 0.01, L"sqlite_close_exists failed", LINE_INFO());
		}
		
	};

	TEST_CLASS(ConfigFile)
	{
	public:
		TEST_METHOD(read_config_Value1)
		{
			ConfigParser cfg;
			cfg.read_config("config.ini");
			std::string str = cfg.get_pt().get<std::string>("Section1.Value1");
			
			Assert::AreEqual("plop", str.c_str(), 0.01, L"read_config_Value1 failed", LINE_INFO());
		}

		TEST_METHOD(read_config_Value2_with_whitespaces)
		{
			ConfigParser cfg;
			cfg.read_config("config.ini");
			std::string str = cfg.get_pt().get<std::string>("Section1.Value2");

			Assert::AreEqual("that is a multitoken value", str.c_str(), 0.01, L"read_config_Value2_with_whitespaces failed", LINE_INFO());
		}

		TEST_METHOD(read_config_Value3)
		{
			ConfigParser cfg;
			cfg.read_config("config.ini");
			std::string str = cfg.get_pt().get<std::string>("Section1.Value3");

			Assert::AreEqual("that contains a;", str.c_str(), 0.01, L"read_config_Value3 failed", LINE_INFO());
		}

		// TODO multiline parsing
		/*
		TEST_METHOD(read_config_Value4)
		{
			ConfigParser cfg;
			cfg.read_config("config.ini");
			std::string str = cfg.get_pt().get<std::string>("Section1.Value4");

			Assert::AreEqual("that contains a;", str.c_str(), 0.01, L"read_config_Value4 failed", LINE_INFO());
		}*/

		TEST_METHOD(config_check)
		{
			ConfigParser cfg;
			cfg.read_config("config.ini");
			cfg.load_config();
			std::string str = cfg.get_err_msg();

			Assert::AreEqual("Config file OK", str.c_str(), 0.01, L"read_config_Value3 failed", LINE_INFO());
		}
	};
}
