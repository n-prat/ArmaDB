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

#include "config.h"
#include <iostream>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/format.hpp>

ConfigParser::ConfigParser()
{		
	sql_custom_only = false;
	use_sql_custom = false;
	err_msg = "";
}

ConfigParser::~ConfigParser()
{
}

int ConfigParser::read_config(std::string filename)
{
	int ret = -1;	
	std::string path = filename;

	try
	{		
		path = "config.ini";
		boost::property_tree::ini_parser::read_ini(path, pt);
		ret = 0;
	}
	catch (const std::exception e)
	{
		std::cout << e.what() << std::endl;
		ret = 1;
	}
		

	return ret;
}

int ConfigParser::load_config()
{
	int ret = 0;
	int sql_custom_queries = 0;
	err_msg = "Check";

	// get the values from the config files
	// we pass it the default value
	try
	{
		use_sql_custom = pt.get<bool>("Options.use_sql_custom");
		sql_custom_only = pt.get<bool>("Options.sql_custom_only");		
	}
	catch (const boost::property_tree::ptree_error &e)
	{
		ret = 3;
		err_msg = "";
		err_msg.append("[config] invalid options: ");
		err_msg.append(e.what());
	}

	// if use_sql_custom, we read the "SQL_1 SQL_2..." from the config	
	if (use_sql_custom) {

		sql_custom_queries = pt.get<int>("Options.sql_custom_queries", 0);

		if (sql_custom_queries > 0) {
			std::string section_i, name_i, type_i, sql_raw_i, nb_bind_i, res_name, res_type, res_sql_raw, res_nb_bind;
			boost::format sql_i("SQL_%1%");

			// range is SQL_1, SQL_2...
			// TODO iterate directly on the nodes
			for (int i = 1; i <= sql_custom_queries; i++) {
				// update the format
				sql_i % i;
				name_i = sql_i.str();
				type_i = sql_i.str();
				sql_raw_i = sql_i.str();
				nb_bind_i = sql_i.str();

				// 2 possible types : basic and bind($NNN, @AAAA, etc)
				name_i = name_i.append(".name");
				type_i = type_i.append(".type");
				sql_raw_i = sql_raw_i.append(".sql");
				nb_bind_i = nb_bind_i.append(".parameters");

				try
				{
					res_name = pt.get<std::string>(name_i);
					res_type = pt.get<std::string>(type_i);
					res_sql_raw = pt.get<std::string>(sql_raw_i);

					if (res_type.compare("bind") == 0) {
						res_nb_bind = pt.get<std::string>(nb_bind_i);
					}
				}
				catch (const boost::property_tree::ptree_error &e)
				{
					ret = 2;
					err_msg = "[config] invalid sql custom : ";
					err_msg.append(e.what());
					break;
				}
			}
		}
		else {
			err_msg = "[config] sql_custom_queries must be >0";
			ret = 1;
		}
	}

	if (ret == 0) {
		err_msg = "Config file OK";
	}
	
	return ret;
}
