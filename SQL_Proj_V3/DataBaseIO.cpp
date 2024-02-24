#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>

#include "DataBaseIO.h"
#include "DataBaseClass.hpp"

UserIO::UserIO() {
	std::string lastInput = "";
	std::string lastCommand = "";

	std::string commandParam = "";
	std::string InputResponse = "";

	int IOMode = NULL;
	int InputMode = NULL;

	bool ValidIn = false;
}

std::string UserIO::GetInput() {
	std::string buffer;

	switch (this->InputMode){
	case (0):
		while (true) {

			std::getline(std::cin, buffer);
			this->lastInput = buffer;

			this->SelectCommand(&buffer, db);
		}
		break;
	case(1):
		std::getline(std::cin, buffer);
		this->InputResponse = buffer;

		break;
	} 
	

	return buffer;
}

void UserIO::SelectCommand(std::string *TotalIn, DataBaseCl db) {
	std::string CommandWord = "";
	std::istringstream iss(*TotalIn);
	iss >> CommandWord;


	int CharDelete = CommandWord.size() + 1;
	std::string tempString = *TotalIn;
	tempString.erase(0, CharDelete);
	this->commandParam = tempString;

	if (CommandWord == "open") {
		this->lastCommand = CommandWord;
		this->ValidIn = true;
		db.OpenDB(&this->commandParam);
	}
	else if (CommandWord == "quit" or CommandWord == "exit") {
		std::cout << "Would you like to exit the program: Y / N ?";

		this->InputMode = 1;

		std::string Input = this->GetInput();

		if (Input == "Y") {
			this->ValidIn = true;
			exit(0);
		}
		else if (Input == "N") {
			this->InputMode = 0;
			this->ValidIn = true;
		}

		this->lastCommand = CommandWord;
		this->ValidIn = true;
		}
	else {
		this -> ValidIn = false;
		}

}

std::string* UserIO::RequestDir() {
	std::string InputDir = this->GetInput();

	if (this->ValidDir()) {
		return &InputDir;
	}
	else {
		return nullptr;
	}
}


bool UserIO::ValidDir() {
	return true;
}
