#pragma once

#include "DataBaseClass.hpp"
#include "Directory.h"

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

	void DataBaseEnterHandle(std::string FileName);

	void GetCommandParam(std::string TotalIn);
	std::string GetCommand(std::string TotalIn);

	void DirectoryMode(std::string CommandWord);
	void DataBaseMode(std::string CommandWord);

	DataBaseCl db;
	DirectoryHandle dir;
public:
	std::string GetInput();
	UserIO();
};