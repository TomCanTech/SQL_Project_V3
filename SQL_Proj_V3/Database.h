#pragma once
#include "sqlite3.h"

struct DataBase
{
	char* error;
	sqlite3* db;
	sqlite3_stmt* stmt;
	int rc;
};