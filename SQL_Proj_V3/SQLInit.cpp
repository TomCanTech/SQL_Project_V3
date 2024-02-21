#include <sqlite3.h>
#include "Database.h"

void OpenDB(DataBase *db) 
{
	sqlite3_open("Databases/myDb.db", &(db->db));
}