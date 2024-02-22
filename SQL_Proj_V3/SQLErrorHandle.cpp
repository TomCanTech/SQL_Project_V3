#include <sqlite3.h>
#include <iostream>
#include <Windows.h>
#include <string>

#include "Database.h"

void SQLErrorHandle(DataBase *db)
{
	//Evaluates if database member, return code == 0 a
	if (db->rc != SQLITE_OK)
	{
		std::cout << "Error:	" << db->error << std::endl;
	}
}