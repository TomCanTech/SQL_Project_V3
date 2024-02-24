#include <iostream>
#include <string>
#include <sstream>

#include "DataBaseIO.h"
#include "DataBaseClass.hpp"

UserIO::UserIO() {
	std::string lastInput = "";
	std::string lastCommand = "";

	bool ValidIn = false;

	std::string commandParam = "";

	int IOMode = 0;
}

void UserIO::SelectCommand(std::string *TotalIn) {
	std::string CommandWord = "";
	std::istringstream iss(*TotalIn);
	iss >> CommandWord;

	if (CommandWord == "cmd") {
		this->lastCommand = CommandWord;
		this->ValidIn = true;
	}
	else if (CommandWord == "help") {
		this->lastCommand = CommandWord;
		this->ValidIn = true;
		}
	else {
		this -> ValidIn = false;
		}
}



std::string UserIO::GetInput() {
	std::string buffer;
	while (this->ValidIn == false) {

		std::getline(std::cin, buffer);
		this->lastInput = buffer;

		this->SelectCommand(&buffer);

	}
	return buffer;
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