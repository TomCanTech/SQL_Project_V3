#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <sys/stat.h>

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
	std::string buffer;

	switch (InputMode){
	case (0):
		while (true) {

			std::getline(std::cin, buffer);
			lastInput = buffer;

			SelectCommand(&buffer);
		}
		break;
	case(1):
		std::getline(std::cin, buffer);
		InputResponse = buffer;

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

	lastCommand = CommandWord;

	return CommandWord;
}

void UserIO::GetCommandParam(std::string TotalIn) {

	int CharDelete = (lastCommand).size() + 1;
	std::string tempString = TotalIn;
	tempString.erase(0, CharDelete);
	commandParam = tempString;
}

void UserIO::DirectoryMode(std::string CommandWord) {
	if (CommandWord == "open" or CommandWord == "enter") {
		EnterHandle(commandParam);
	}
	else if (CommandWord == "quit" or CommandWord == "exit") {
		ExitHandle();
	}
	else if (CommandWord == "enter") {
	}
	else
	{
		ValidIn = false;
	}
}

void UserIO::EnterHandle(std::string path) {
	
	if (path == "default") {
	
		std::cout << "Using default path" << std::endl;
		IOMode = 1;
		
	}
	else if(ValidPath(&path)) {
		dir.user_dir = (path + "\\databases");
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
				WaitingInput = true;
			}
			
		}
	}
}

void UserIO::DataBaseMode(std::string CommandWord) {
	if (CommandWord == "open" or CommandWord == "enter") {
		this->ValidIn = true;
		db.OpenDB();
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