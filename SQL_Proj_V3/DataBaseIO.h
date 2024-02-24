#pragma once

class UserIO {
	std::string lastInput;
	std::string lastCommand;
	std::string commandParam;

	bool ValidIn;

	int IOMode;

	void SelectCommand(std::string *TotalIn);
	bool ValidDir();
public:
	std::string* RequestDir();
	std::string GetInput();
	UserIO();
};