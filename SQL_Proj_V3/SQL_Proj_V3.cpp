#include <sqlite3.h>

#include "DataBaseClass.hpp"
#include "DataBaseIO.h"

int main()
{
	static DataBaseCl db;
	static UserIO foo;

	foo.GetInput();



	////Executes SQL code and returns rc into database struct
	//std::string cmd ("CREATE TABLE IF NOT EXISTS alimony(x1 INT, x2 INT, name varchar(100));");
	//db1.ManipDB(&cmd);

	//std::string path  ((db1.current_dir) + "\\databases");
	//std::string command = "dir /a-d ";

	//command.append(path);
	//const char* command_cstr = command.c_str();

	//system(command_cstr);
	//
	//std::string fooIn = foo.GetInput();

	return 0;
}