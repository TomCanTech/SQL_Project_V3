#include <string>
#include <sys/stat.h>
#include <Windows.h>
#include <direct.h>

#include "Directory.h"


DirectoryHandle::DirectoryHandle() {
	default_dir = SetDefaultDirectory() + "\\databases";
	user_dir =  "";

	default_db_path = default_dir + "\\database.db";
	user_db_path = "";
}

std::string DirectoryHandle::SetDefaultDirectory()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");

	return std::string(buffer).substr(0, pos);
}

bool DirectoryHandle::ValidPath(std::string* path) {
	struct stat sb;
	if (stat(path->c_str(), &sb) == 0)
		return true;
	else
		return false;
}

int DirectoryHandle::MakeDir(std::string* path) {
	std::string buf(*path);
	buf.append("\\databases");

	const char* cstr_d;
	cstr_d = buf.c_str();

	int rv = _mkdir(cstr_d);
	return rv;
}