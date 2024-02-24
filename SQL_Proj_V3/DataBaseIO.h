#pragma once

#include "DataBaseClass.hpp"

class UserIO {
	std::string lastInput;
	std::string lastCommand;
	std::string commandParam;

	bool ValidIn;

	int IOMode;

	void SelectCommand(std::string *TotalIn, DataBaseCl db);
	bool ValidDir();
	DataBaseCl db;
public:
	std::string* RequestDir();
	std::string GetInput();
	UserIO();
};