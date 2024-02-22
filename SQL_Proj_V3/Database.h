#pragma once
#include "sqlite3.h"

struct DataBase
{
	//Initialises database object
	sqlite3* db;
	//Initialises SQL readable code
	sqlite3_stmt* stmt;
	//Initialises error handling vars
	char* error;
	int rc;
};