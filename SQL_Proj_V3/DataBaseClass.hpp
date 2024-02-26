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
	int* data;

	DataBaseCl();
	void OpenDB();
	void ManipDB(std::string* SQL_Func);

	void ListTable(std::string CommandParam);
	void CreateTable(std::string CommandParam);
	static int callback(void* NotUsed, int argc, char** argv, char** azColName);
private:
	//Error Code
	void SQLErrorHandle() const;
};