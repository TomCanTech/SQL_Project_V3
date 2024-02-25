#pragma once

#include <string>

struct DirectoryHandle {
	DirectoryHandle();

	std::string default_dir;
	std::string user_dir;

	std::string default_db_path;
	std::string user_db_path;

	bool ValidPath(std::string path);
	int MakeDir(std::string *path);
private:
	std::string SetDefaultDirectory();
};