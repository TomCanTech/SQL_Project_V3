#include <sqlite3.h>
#include <Windows.h>
#include <string>
#include <sys/stat.h>
#include <iostream>
#include <direct.h>

#include "DataBaseClass.hpp"

DataBaseCl::DataBaseCl() {
	//Actual db object for use within library
	db = nullptr;
	//???
	stmt = nullptr;
	//Pointer containing error num
	error = 0;
	//Error/State code
	rc = NULL;
	//default database path, no user inputs boo hoo
	db_path = "C:\\Program Files\\Cornish_Project\\Cornish_Project.db";
}

int DataBaseCl::callback(void* NotUsed, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; i++) {
		printf("%s = %s", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int DataBaseCl::callbacknoheader(void* NotUsed, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; i++) {
		std::cout << "--) ";
		printf("%s", argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

void DataBaseCl::OpenDB(){
		const char* cstr_db_path = db_path.c_str();

		rc = sqlite3_open(cstr_db_path, &db);
		SQLErrorHandle();
}


void DataBaseCl::ManipDB(std::string* SQL_Func){
	rc = sqlite3_exec(db, SQL_Func->c_str(), callbacknoheader, NULL, &error);
	SQLErrorHandle();
}

void DataBaseCl::ListTable(std::string CommandParam) {
	const char* TableNames = "SELECT name FROM sqlite_schema WHERE type = 'table' ORDER BY name; ";
	rc = sqlite3_exec(db, TableNames, callbacknoheader, NULL, &error);
	SQLErrorHandle();
}

void DataBaseCl::SQLErrorHandle() const {
		//Evaluates if database member, return code == 0 a
		if (rc != SQLITE_OK){
			std::cout << "Error:	" << *error << std::endl;
		}
}
