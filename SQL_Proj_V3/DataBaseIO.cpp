#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <sys/stat.h>
#include <vector>

#include "DataBaseIO.h"
#include "DataBaseClass.hpp"
#include "Directory.h"

UserIO::UserIO() {
	lastInput = "hello";
	lastCommand = "";
	commandParam = "";

	InputResponse = "";

	IOMode = NULL;
	InputMode = NULL;

	db;

	ValidIn = false;
	WaitingInput = true;
}

std::string UserIO::GetInput() {
	std::string Input;

	switch (InputMode){
	case (0):
		while (WaitingInput) {
			std::string buffer;

			std::getline(std::cin, buffer);
			lastInput = buffer;

			SelectCommand(&buffer);

			Input = buffer;
		}
		break;
	case(1):
		std::string buffer;

		std::getline(std::cin, buffer);
		InputResponse = buffer;

		Input = buffer;
		break;
	} 
	return Input;
}

std::string UserIO::GetCommand(std::string TotalIn) {

	std::string CommandWord = "";
	std::istringstream iss(TotalIn);
	iss >> CommandWord;

	lastCommand = CommandWord;
	return CommandWord;
}

void UserIO::GetCommandParam(std::string TotalIn) {

	int CharDelete = (lastCommand).size() + 1;
	std::string tempString = TotalIn;
	tempString.erase(0, CharDelete);
	commandParam = tempString;
}

void UserIO::SelectCommand(std::string* TotalIn) {
	std::string CommandWord = GetCommand(*TotalIn);
	GetCommandParam(*TotalIn);

	if (lastCommand == "quit" or lastCommand == "exit") {
		ExitHandle();
	}

	switch (IOMode) {
	case 0: {
		DirectoryMode(CommandWord);
		break;
	}
	case 1: {
		DataBaseMode(CommandWord);
		break;
	}
	case 2: {
		TableMode(CommandWord);
		break;
	}
	}
}

void UserIO::DirectoryMode(std::string CommandWord) {
	if (CommandWord == "open" or CommandWord == "enter") {
		EnterHandle(commandParam);
	}
	else if (CommandWord == "enter") {
	}
	else
	{
		ValidIn = false;
	}
}

void UserIO::EnterHandle(std::string directory) {
	
	if (directory == "default") {
	
		std::cout << "Using default directory" << std::endl;
		IOMode = 1;
		dir.current_path = 0;
	}
	else if(dir.ValidPath(directory)) {
		dir.user_dir = (directory);
		std::cout << "Using user-defined directory." << std::endl;
		IOMode = 1;
		dir.current_path = 1;
	}
	else {
		std::cout << "Invalid directory. Please try another directory." << std::endl;
	}

}

void UserIO::ExitHandle() {
	{
		std::cout << "Would you like to exit the program: Y / N ?" << std::endl;

		InputMode = 1;

		while ((WaitingInput) or InputMode == 1) {
			std::string Input = GetInput();

			if (Input == "Y") {
				ValidIn = true;
				exit(0);
			}
			else if (Input == "N") {
				InputMode = 0;
				ValidIn = true;
			}
			else {
				std::cout << "That is not a valid response, please try again." << std::endl;
				ValidIn = false;
				WaitingInput = true;
			}
		}
	}
}

void UserIO::DataBaseMode(std::string CommandWord) {
	if (CommandWord == "open" or CommandWord == "enter") {
		ValidIn = true;
		DataBaseEnterHandle(commandParam);
		IOMode = 2;
	}
	else if (CommandWord == "return") {
		std::cout << "Returning to directory mode" << std::endl;
		IOMode = 0;
	}
	else
	{
		ValidIn = false;
	}
}

void UserIO::DataBaseEnterHandle(std::string FileName) {
	if (commandParam == "default") {
		std::cout << "Opening default database" << std::endl;
		db.OpenDB();
	}
	else if (dir.ValidPath(dir.user_dir + FileName)) {

	}

}

void UserIO::TableMode(std::string CommandWord) {
	if (CommandWord == "list") {
		db.ListTable(commandParam);
	}
	else if (CommandWord == "tablemake") {
		CreateTable();
	}
	else if (CommandWord == "quit" or CommandWord == "exit") {
		ExitHandle();
	}
}

void UserIO::CreateTable() {
	std::cout << "What would you like to call the table: " << std::endl;
	InputMode = 1;
	std::string TableName = GetInput();
	std::cout << "How many headers would you like: " << std::endl;
	std::string TableHeadNum;
 
	ValidIn = false;
	while (ValidIn == false) {
		std::string TableHeadNumStr = GetInput();
		for (int i = 0; i < TableHeadNumStr.length(); i++)
			if (isdigit(TableHeadNumStr[i]) == false) {
				ValidIn = false;
				break;
			}
			else {
				ValidIn = true;
			}
		if (ValidIn == true) {
			WaitingInput = false;
			TableHeadNum = TableHeadNumStr;
		}
		else if (ValidIn == false) {
			std::cout << "That is not a valid response. Please try again." << std::endl;
		}
	}
	WaitingInput = true;

	std::vector<std::string> HeadNames;
	for (int i = 0; i < stoi(TableHeadNum); i++) {
		std::cout << "What is the title of header number " << (i + 1) << ":" << std::endl;
		HeadNames.push_back(GetInput());
	}
	
	std::string HeadsInOrder = "";
	for (int i = 0; i < stoi(TableHeadNum); i++) {
		HeadsInOrder = HeadsInOrder + HeadNames.at(i) + " varchar(150),";
	}
	
	if (!HeadsInOrder.empty()) {
		HeadsInOrder.pop_back();
	}

	std::string SQL_Code = TableName + "(" + HeadsInOrder + ")";

	db.CreateTable(SQL_Code);
}