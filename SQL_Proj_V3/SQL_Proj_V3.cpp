#include "sqlite3.h"
#include <iostream>

int main()
{
	char* error;
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Databases/myDb.db", &db);

	int rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS alimony(x1 INT, x2 INT, name varchar(100));",NULL,NULL,&error);
	if (rc != SQLITE_OK)
	{
		std::cout << "Error:	" << error << std::endl;
	}

	for (int i = 0; i < 10; i++)
	{
		const char* query = "Insert into alimony VALUES (12, 15, 'Your mother');";
		std::cout << query << std::endl;
		rc = sqlite3_exec(db, query, NULL, NULL, &error);
			if (rc != SQLITE_OK)
			{
				std::cout << "Error:	" << error << std::endl;
			}
	}


	return 0;
}