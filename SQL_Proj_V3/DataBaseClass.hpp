#pragma once

#include <sqlite3.h>
#include <Windows.h>
#include <string>
#include <sys/stat.h>
#include <iostream>
#include <direct.h>

class DataBaseCl {

	//DB Variables
		//Initialises database object
	sqlite3* db;
	//Initialises SQL readable code
	sqlite3_stmt* stmt;
	//Initialises error handling vars
	char* error;

public:
	int m_rc;
	std::string current_dir;
	std::string user_dir;
	DataBaseCl();
	//Open DB in .exe folder
	void OpenDB(std::string* UserDir);
	void ManipDB(std::string* SQL_Func);
	std::string GetCurrentDirectory();

private:
	//Error Code
	void SQLErrorHandle() const;

	// DIR Manipulation
		//Create DB dir in input dir
	int MakeDirectory(std::string* path);
		//Obtain .exe path
};