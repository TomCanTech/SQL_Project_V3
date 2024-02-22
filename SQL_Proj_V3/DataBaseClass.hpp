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
	int rc;
	DataBaseCl();
	//Open DB in .exe folder
	void OpenDB();
private:
	//Error Code
	void SQLErrorHandle();

	// DIR Manipulation
		//Create DB dir in input dir
	int MakeDirectory(std::string* path);
		//Obtain .exe path
	std::string GetCurrentDirectory();
};