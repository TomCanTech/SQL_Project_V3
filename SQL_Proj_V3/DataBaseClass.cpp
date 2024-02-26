#include <sqlite3.h>
#include <Windows.h>
#include <string>
#include <sys/stat.h>
#include <iostream>
#include <direct.h>

#include "DataBaseClass.hpp"
#include "Directory.h"

DataBaseCl::DataBaseCl() {
	//Actual db object for use within library
	db = nullptr;
	//???
	stmt = nullptr;
	//Pointer containing error num
	error = nullptr;
	//Error/State code
	rc = NULL;

}

int DataBaseCl::callback(void* NotUsed, int argc, char** argv, char** azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}


void DataBaseCl::OpenDB(){
		const char* cstr_db_path = dir.default_db_path.c_str();

		rc = sqlite3_open(cstr_db_path, &db);
		SQLErrorHandle();
}


void DataBaseCl::ManipDB(std::string* SQL_Func){
	rc = sqlite3_exec(db, SQL_Func->c_str(), NULL, NULL, &error);
	SQLErrorHandle();
}

void DataBaseCl::ListTable(std::string CommandParam) {
	const char* TableNames = "SELECT name FROM sqlite_schema WHERE type = 'table' ORDER BY name; ";
	rc = sqlite3_exec(db, TableNames, callback, NULL, &error);
	SQLErrorHandle();
}

void DataBaseCl::CreateTable(std::string CommandParam) {
	std::string TableSQL = "CREATE TABLE IF NOT EXISTS " + CommandParam;
	const char* TableSQL_c = TableSQL.c_str();

	rc = sqlite3_exec(db, TableSQL_c, callback, NULL, &error);
}

void DataBaseCl::SQLErrorHandle() const {
		//Evaluates if database member, return code == 0 a
		if (rc != SQLITE_OK){
			std::cout << "Error:	" << error << std::endl;
		}
}
