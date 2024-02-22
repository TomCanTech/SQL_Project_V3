#include <sqlite3.h>
#include <iostream>

#include "Database.h"
#include "SQLErrorHandle.h"
#include "DataBaseManip.h"

int main()
{
	//Initialises database struct; Finds and creates db connection
	static DataBase db1;
	OpenDB(&db1);

	//Executes SQL code and returns rc into database struct
	db1.rc = sqlite3_exec(db1.db, "CREATE TABLE IF NOT EXISTS alimony(x1 INT, x2 INT, name varchar(100));", NULL,NULL,&(db1.error));
	//Calls Error Handle in response to sqlite3_exec
	SQLErrorHandle(&db1);

	return 0;
}