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
#include <boost/property_tree/ptree.hpp>

class ConfigParser
{
public:
	ConfigParser();
	~ConfigParser();


	int read_config(std::string filename);
	int load_config();

	std::string get_err_msg() { return err_msg; }
	
	// TODO remove (used Tests only)
	boost::property_tree::ptree & get_pt() { return pt; }
private:	
	boost::property_tree::ptree pt;
	bool sql_custom_only;
	bool use_sql_custom;
	std::string err_msg;
};
