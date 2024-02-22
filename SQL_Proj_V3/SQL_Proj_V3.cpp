#include <sqlite3.h>

#include "DataBaseClass.hpp"

int main()
{
	//Initialises database struct; Finds and creates db connection
	DataBaseCl(db1);
	db1.OpenDB();

	//Executes SQL code and returns rc into database struct
	//db1.rc = sqlite3_exec(db1.db, "CREATE TABLE IF NOT EXISTS alimony(x1 INT, x2 INT, name varchar(100));", NULL,NULL,&(db1.error));
	//Calls Error Handle in response to sqlite3_exec
	//db1.SQLErrorHandle();

	return 0;
}