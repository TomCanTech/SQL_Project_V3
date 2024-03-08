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

	void SelectCommand(std::string *TotalIn);
	void ExitHandle();

	void DataBaseEnterHandle();

	void GetCommandParam(std::string TotalIn);
	void GetCommand(std::string TotalIn);

	void DataBaseMode();
	void TableMode();

	void QueryTableHeaders();

	void TableInputMode();

	DataBaseCl db;
public:
	std::string GetInput();
	UserIO();
};