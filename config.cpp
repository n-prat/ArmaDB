#include "config.h"
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

ConfigParser::ConfigParser()
{
}

ConfigParser::~ConfigParser()
{
}

int ConfigParser::read_config(std::string filename)
{
	int ret = -1;
	boost::property_tree::ptree pt;

	try
	{
		boost::property_tree::ini_parser::read_ini("config.ini", pt);
		sql_custom_path = pt.get<std::string>("Section1.Value1");

		ret = 0;
	}
	catch (const std::exception e)
	{
		std::cout << e.what() << std::endl;
		ret = 1;
	}
		

	return ret;
}
