#include <sqlite3.h>
#include <Windows.h>
#include <string>
#include <sys/stat.h>
#include <iostream>
#include <direct.h>

#include "DataBaseClass.hpp"

DataBaseCl::DataBaseCl() {
	sqlite3* db = nullptr;
	sqlite3_stmt* stmt = nullptr;
	char* error = nullptr;
	rc = NULL;
}

void DataBaseCl::OpenDB()
	{
		std::string exec_path = GetCurrentDirectory();
		const char* cstr_exec_path = exec_path.c_str();

		std::string db_path = exec_path + "\\databases\\database.db";
		const char* cstr_db_path = db_path.c_str();

		struct stat sb;

		if (stat(cstr_db_path, &sb) != 0)
		{
			std::cout << "Created Databases Dir.";
			MakeDirectory(&exec_path);
			this->rc = sqlite3_open(cstr_db_path, &(this->db));
			SQLErrorHandle();
		}
		else
		{
			std::cout << "Directory found.";
			this->rc = sqlite3_open(cstr_db_path, &(this->db));
			SQLErrorHandle();
		}

	}
void DataBaseCl::SQLErrorHandle() 
	{
		//Evaluates if database member, return code == 0 a
		if (this->rc != SQLITE_OK)
		{
			std::cout << "Error:	" << this->error << std::endl;
		}
	}


int DataBaseCl::MakeDirectory(std::string *path)
	{
		std::string buf(*path);
		buf.append("\\databases");

		const char* cstr_d;
		cstr_d = buf.c_str();

		int rv = _mkdir(cstr_d);
		return rv;
	}
		//Obtain .exe path
	
std::string DataBaseCl::GetCurrentDirectory()
	{
		char buffer[MAX_PATH];
		GetModuleFileNameA(NULL, buffer, MAX_PATH);
		std::string::size_type pos = std::string(buffer).find_last_of("\\/");

		return std::string(buffer).substr(0, pos);
	}

