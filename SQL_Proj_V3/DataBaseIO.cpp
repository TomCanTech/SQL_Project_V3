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
	bool WaitingInput = true;
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
	std::string CommandWord = GetCommand(*TotalIn);
	GetCommandParam(*TotalIn);

	if (CommandWord == "open") {
		this->ValidIn = true;
		db.OpenDB(&this->commandParam);
	}
	else if (CommandWord == "quit" or CommandWord == "exit") {
		ExitHandle();
	}
	else if (CommandWord == "enter") {

	} else
	{
		this -> ValidIn = false;
		}

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