#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <sys/stat.h>

#include "DataBaseIO.h"
#include "DataBaseClass.hpp"

UserIO::UserIO() {
	std::string lastInput = "";
	std::string lastCommand = "";
	std::string commandParam = "";

	std::string InputResponse = "";

	int IOMode = NULL;
	int InputMode = NULL;

	DataBaseCl* db;

	bool ValidIn = false;
	bool WaitingInput = true;

}

std::string UserIO::GetInput() {
	std::string buffer;

	switch (this->InputMode){
	case (0):
		while (true) {

			std::getline(std::cin, buffer);
			this->lastInput = buffer;

			this->SelectCommand(&buffer);
		}
		break;
	case(1):
		std::getline(std::cin, buffer);
		this->InputResponse = buffer;

		break;
	} 
	return buffer;
}

void UserIO::SelectCommand(std::string* TotalIn) {
	std::string CommandWord = GetCommand(*TotalIn);
	GetCommandParam(*TotalIn);

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
		
	}

	}
}

std::string UserIO::GetCommand(std::string TotalIn) {

	std::string CommandWord = "";
	std::istringstream iss(TotalIn);
	iss >> CommandWord;

	this->lastCommand = CommandWord;

	return CommandWord;
}

void UserIO::GetCommandParam(std::string TotalIn) {

	int CharDelete = (this->lastCommand).size() + 1;
	std::string tempString = TotalIn;
	tempString.erase(0, CharDelete);
	this->commandParam = tempString;
}

void UserIO::DirectoryMode(std::string CommandWord) {
	if (CommandWord == "open" or CommandWord == "enter") {
		EnterHandle(this->commandParam);
	}
	else if (CommandWord == "quit" or CommandWord == "exit") {
		ExitHandle();
	}
	else if (CommandWord == "enter") {
	}
	else
	{
		this->ValidIn = false;
	}
}

void UserIO::EnterHandle(std::string path) {
	
	if (path == "default") {
		std::string default_path = db.current_dir;
		if (ValidPath(&default_path)) {
			std::cout << "Using default path" << std::endl;
			IOMode = 1;
		}
	}
	else if(ValidPath(&path)) {
		db.user_dir = (path + "\\databases");
		std::cout << "Path found." << std::endl;
		IOMode = 1;
	}
	else {
		std::cout << "Invalid path. Please try another path." << std::endl;
	}

}

bool UserIO::ValidPath(std::string* path) {
	struct stat sb;

	if (stat(path->c_str(), &sb) == 0)
		return true;
	else
		return false;
}

void UserIO::ExitHandle() {
	{
		std::cout << "Would you like to exit the program: Y / N ?" << std::endl;

		this->InputMode = 1;

		while ((this->WaitingInput) or InputMode == 1) {
			std::string Input = this->GetInput();

			if (Input == "Y") {
				this->ValidIn = true;
				exit(0);
			}
			else if (Input == "N") {
				this->InputMode = 0;
				this->ValidIn = true;
			}
			else {
				std::cout << "That is not a valid response, please try again." << std::endl;
				this->WaitingInput = true;
			}
			
		}
	}
}

void UserIO::DataBaseMode(std::string CommandWord) {
	if (CommandWord == "open" or CommandWord == "enter") {
		this->ValidIn = true;
		db.OpenDB(&this->commandParam);
		this->IOMode = 2;
	}
	else if (CommandWord == "quit") {
		ExitHandle();
	}
	else if (CommandWord == "return") {
		std::cout << "Returning to directory mode" << std::endl;
		this->IOMode = 0;

	}
	else
	{
		this->ValidIn = false;
	}
}