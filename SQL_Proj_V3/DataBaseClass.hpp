#pragma once

#include <sqlite3.h>
#include <Windows.h>
#include <string>
#include <sys/stat.h>
#include <iostream>
#include <direct.h>

#include "Directory.h"

class DataBaseCl {
	sqlite3* db;
	sqlite3_stmt* stmt;
	char* error;

	DirectoryHandle dir;
public:
	int rc;
	DataBaseCl();
	void OpenDB();
	void ManipDB(std::string* SQL_Func);

private:
	//Error Code
	void SQLErrorHandle() const;
};