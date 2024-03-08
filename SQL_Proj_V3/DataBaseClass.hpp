#pragma once

#include <sqlite3.h>
#include <Windows.h>
#include <string>
#include <sys/stat.h>
#include <iostream>
#include <direct.h>


class DataBaseCl {
	sqlite3* db;
	sqlite3_stmt* stmt;
	char* error;
	std::string db_path;
public:
	int rc;

	DataBaseCl();
	void OpenDB();
	void ManipDB(std::string* SQL_Func);

	void ListTable(std::string CommandParam);
	static int callback(void* NotUsed, int argc, char** argv, char** azColName);
	static int callbacknoheader(void* NotUsed, int argc, char** argv, char** azColName);
private:
	//Error Code
	void SQLErrorHandle() const;
};