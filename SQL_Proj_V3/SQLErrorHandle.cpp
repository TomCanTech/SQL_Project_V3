#include <sqlite3.h>
#include <iostream>
#include "Database.h"

#include <Windows.h>
#include <string>

void SQLErrorHandle(DataBase *db)
{
	if (db->rc != SQLITE_OK)
	{
		std::cout << "Error:	" << (db->error) << std::endl;
	}
}