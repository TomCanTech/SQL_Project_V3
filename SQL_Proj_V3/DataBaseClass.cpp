#include <sqlite3.h>
#include <Windows.h>
#include <string>
#include <sys/stat.h>
#include <iostream>
#include <direct.h>

#include "DataBaseClass.hpp"

DataBaseCl::DataBaseCl() {
	//Actual db object for use within library
	sqlite3* db = nullptr;
	//???
	sqlite3_stmt* stmt = nullptr;
	//Pointer containing error num
	char* error = nullptr;
	//Error/State code
	int rc = NULL;
	//Default directory
	this->current_dir = GetCurrentDirectory();
	//Directory input by user
	std::string user_dir = "";
}

void DataBaseCl::OpenDB(std::string* UserDir)
	{
		std::string db_path = current_dir + "\\databases\\database.db";
		const char* cstr_db_path = db_path.c_str();

		struct stat sb;

		if (stat(cstr_db_path, &sb) != 0)
		{
			std::cout << "Created Databases dir.";
			MakeDirectory(&current_dir);
		}
		else
		{
			std::cout << "Directory found.";
		}
	this->m_rc = sqlite3_open(cstr_db_path, &(this->db));
	SQLErrorHandle();
	}


void DataBaseCl::SQLErrorHandle() const 
	{
		//Evaluates if database member, return code == 0 a
		if (this->m_rc != SQLITE_OK)
		{
			std::cout << "Error:	" << this->error << std::endl;
		}
	}

void DataBaseCl::ManipDB(std::string* SQL_Func){
	this->m_rc = sqlite3_exec(this->db, SQL_Func->c_str(), NULL, NULL, &this->error);
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