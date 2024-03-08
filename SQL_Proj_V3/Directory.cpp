#include <string>
#include <sys/stat.h>
#include <Windows.h>
#include <direct.h>

#include "Directory.h"


DirectoryHandle::DirectoryHandle() {
	//default_dir = SetDefaultDirectory() + "\\
	// bases";
	db_path = "C:\\Program Files\\Cornish_Project\\Cornish_Project.db";

}
