#include <sqlite3.h>
#include <Windows.h>
#include <string>
#include <sys/stat.h>
#include <iostream>
#include <direct.h>

#include "Database.h"
#include "SQLErrorHandle.h"

std::string GetCurrentDirectory()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");

	return std::string(buffer).substr(0, pos);
}

int MakeDirectory(std::string* d)
{
	std::string buf(*d);
	buf.append("\\databases");

	const char* cstr_d;
	cstr_d = buf.c_str();

	int rv = _mkdir(cstr_d);
	return rv;
}

void OpenDB(DataBase *db) 
{
	std::string exec_path = GetCurrentDirectory();
	const char* cstr_exec_path = exec_path.c_str();

	std::string db_path = exec_path + "\\databases\\database.db";
	const char* cstr_db_path = db_path.c_str();

	struct stat sb;

	if (stat(cstr_db_path, &sb) != 0)
	{
		std::cout << "Making Directory...";
		MakeDirectory(&exec_path);
	}
	else
	{
		std::cout << "Directory found.";
		db->rc = sqlite3_open(cstr_db_path, &(db->db));
		SQLErrorHandle(db);
	};
}