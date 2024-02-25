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
	void EnterHandle(std::string path);
	bool ValidPath(std::string* path);

	void GetCommandParam(std::string TotalIn);
	std::string GetCommand(std::string TotalIn);

	void DirectoryMode(std::string CommandWord);
	void DataBaseMode(std::string CommandWord);
	DataBaseCl db;
public:
	std::string GetInput();
	UserIO();
};