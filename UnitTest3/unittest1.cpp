#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest3
{		
	TEST_CLASS(ArgumentsParsing)
	{
	public:
		
		// If "function" arg is empty, should reply "Hello World!!"
		TEST_METHOD(helloworld)
		{			
			char out[50], fun[50] = "";
			int outSize = 50;
			RVExtension(out, outSize, fun);			
			Assert::AreEqual(
				// Expected value:
				"Hello World!!",
				// Actual value:
				out,
				//"Hello World!!",
				// Tolerance:
				0.01,
				// Message:
				L"Hello World failed",
				// Line number - used if there is no PDB file:
				LINE_INFO());
		}

		TEST_METHOD(too_many_args)
		{
			char out[50], fun[] = "sdf:aze:hg:xcv:jgh:oiu:qsd:xcv:ytuiy:sdfsfdg";
			int outSize = 50;
			RVExtension(out, outSize, fun);
			Assert::AreEqual("INPUT not recognized", out, 0.01, L"too_many_args failed", LINE_INFO());
		}

		TEST_METHOD(two_args_not_valid)
		{
			char out[100], fun[] = "sdf:aze";
			int outSize = 100;
			RVExtension(out, outSize, fun);
			Assert::AreEqual("SETUP command invalid: USAGE: OPEN:filename or OPENCREATE:filename", out, 0.01, L"two_args_not_valid failed", LINE_INFO());
		}

		TEST_METHOD(two_args_valid1)
		{
			char out[100], fun[] = "OPEN:filename";
			int outSize = 100;
			RVExtension(out, outSize, fun);
			Assert::AreEqual("OPEN ok", out, 0.01, L"two_args_valid1 failed", LINE_INFO());
		}

		TEST_METHOD(two_args_valid2)
		{
			char out[100], fun[] = "OPENCREATE:filename";
			int outSize = 100;
			RVExtension(out, outSize, fun);
			Assert::AreEqual("OPENCREATE ok", out, 0.01, L"two_args_valid2 failed", LINE_INFO());
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

	TEST_CLASS(SQliteOpen0)
	{
	public:
		TEST_METHOD(sqlite_setup_open_does_not_exist)
		{
			sqlite sq;
			std::string filename = "plop";

			sq.setup_open(filename);
			Assert::AreEqual("unable to open database file", sq.get_err_msg(), 0.01, L"sqlite_setup_open_does_not_exist failed", LINE_INFO());
		}
	};

	TEST_CLASS(SQliteOpen1)
	{
	public:
		TEST_METHOD(sqlite_setup_create)
		{
			sqlite sq;
			std::string filename = "plop.db";

			sq.setup_create(filename);
			Assert::AreEqual("not an error", sq.get_err_msg(), 0.01, L"sqlite_setup_create failed", LINE_INFO());
		}
	};

	TEST_CLASS(SQliteOpen2)
	{
	public:
		TEST_METHOD(sqlite_setup_open_exists)
		{
			sqlite sq;
			std::string filename = "plop.db";

			sq.setup_open(filename);
			Assert::AreEqual("not an error", sq.get_err_msg(), 0.01, L"sqlite_setup_open_exists failed", LINE_INFO());
		}
	};

	TEST_CLASS(SQliteSQLsimple)
	{
	public:
		TEST_METHOD(sqlite_simple_read_exists)
		{
			sqlite sq;
			sq.setup_create("plop.db");
			sq.exec_simple("CREATE TABLE examp(id int PRIMARY KEY, positions text, directions text);");
			sq.exec_simple("SELECT * FROM examp;");
			Assert::AreEqual("not an error", sq.get_err_msg(), 0.01, L"sqlite_simple failed", LINE_INFO());
		}

		TEST_METHOD(sqlite_simple_read_not_exists)
		{
			sqlite sq;
			sq.setup_create("plop.db");

			sq.exec_simple("SELECT * FROM examp2;");
			Assert::AreEqual("SQL logic error or missing database", sq.get_err_msg(), 0.01, L"sqlite_simple failed", LINE_INFO());
		}

		// CREATE TABLE examp(one text, two int);
		// .tables; .schema; SELECT * FROM truc;
		TEST_METHOD(sqlite_create_table_2times)
		{
			sqlite sq;
			sq.setup_create("plop.db");

			sq.exec_simple("CREATE TABLE races2(id int PRIMARY KEY, positions text, directions text);");
			sq.exec_simple("CREATE TABLE races2(id int PRIMARY KEY, positions text, directions text);");
			Assert::AreEqual("SQL logic error or missing database", sq.get_err_msg(), 0.01, L"sqlite_create_table_2times failed", LINE_INFO());
		}

		TEST_METHOD(sqlite_create_ifnotexists)
		{
			sqlite sq;
			sq.setup_create("plop.db");

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
}