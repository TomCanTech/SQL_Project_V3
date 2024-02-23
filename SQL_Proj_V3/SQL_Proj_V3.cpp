#include <sqlite3.h>

#include "DataBaseClass.hpp"

int main()
{
	//Initialises database struct; Finds and creates db connection
	static DataBaseCl(db1);
	db1.OpenDB();

	//Executes SQL code and returns rc into database struct
	db1.ManipDB("CREATE TABLE IF NOT EXISTS alimony(x1 INT, x2 INT, name varchar(100));");

	std::string path  ((db1.current_dir) + "\\databases");
	std::string command = "dir /a-d ";

	command.append(path);
	const char* command_cstr = command.c_str();

	system(command_cstr);
	
	return 0;
}