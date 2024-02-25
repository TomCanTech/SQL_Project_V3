#pragma once

#include "DataBaseClass.hpp"

class UserIO {
	std::string lastInput;
	std::string lastCommand;

	std::string commandParam;
	std::string InputResponse;

	int IOMode;
	int InputMode;
	bool ValidIn;
	bool WaitingInput;

	void SelectCommand(std::string *TotalIn, DataBaseCl db);
	void ExitHandle();

	void GetCommandParam(std::string TotalIn);
	std::string GetCommand(std::string TotalIn);

	DataBaseCl db;
public:
	std::string GetInput();
	UserIO();
};