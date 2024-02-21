#include <sqlite3.h>
#include <iostream>

#include "Database.h"
#include "SQLErrorHandle.h"
#include "SQLInit.h"

int main()
{
	DataBase db1;
	OpenDB(&db1);

	db1.rc = sqlite3_exec(db1.db, "CREATE TABLE IF NOT EXISTS alimony(x1 INT, x2 INT, name varchar(100));", NULL,NULL,&(db1.error));
	SQLErrorHandle(&db1);

	return 0;
}