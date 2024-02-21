#include <sqlite3.h>
#include "Database.h"
#include <Windows.h>
#include <string>

std::string GetCurrentDirectory()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");

	return std::string(buffer).substr(0, pos);
}

void OpenDB(DataBase *db) 
{

	sqlite3_open("Databases/myDb.db", &(db->db));
}