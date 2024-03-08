#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <sys/stat.h>
#include <vector>

#include "DataBaseIO.h"
#include "DataBaseClass.hpp"

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
			std::getline(std::cin, Input);
			lastInput = Input;
			SelectCommand(&Input);
		}
		break;
	case(1):
		std::getline(std::cin, Input);
		InputResponse = Input;
		break;
	} 
	return Input;
}

void UserIO::GetCommand(std::string TotalIn) {

	std::istringstream iss(TotalIn);
	iss >> lastCommand;
}

void UserIO::GetCommandParam(std::string TotalIn) {

	int CharDelete = (lastCommand).size() + 1;
	std::string tempString = TotalIn;
	tempString.erase(0, CharDelete);
	commandParam = tempString;
}

void UserIO::SelectCommand(std::string* TotalIn) {
	GetCommand(*TotalIn);
	GetCommandParam(*TotalIn);

	if (lastCommand == "quit" or lastCommand == "exit") {
		ExitHandle();
	}

	switch (IOMode) {
		case 0: {
			DataBaseMode();
			break;
		}
		case 1: {
			TableMode();
			break;
		}
		case 2: {
			TableInputMode();
			break;
		}
		case 3: {
			//TableReadMode();
			break;
		}
		case 4: {
			//TableEditMode();
			break;
		}
	}
}


void UserIO::ExitHandle() {
	{
		std::cout << "Would you like to exit the program: Y / N ?" << std::endl;

		InputMode = 1;

		while (InputMode == 1) {
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
			}
		}
	}
}

void UserIO::DataBaseMode() {
	if (lastCommand == "open" or lastCommand == "enter") {
		ValidIn = true;
		DataBaseEnterHandle();
	}
	else  if (lastCommand == "input") {
		ValidIn = true;
		IOMode = 2;
	} else {
		ValidIn = false;
	}
}

void UserIO::DataBaseEnterHandle() {
	if (commandParam == "") {
		std::cout << "Opening default database" << std::endl;
		db.OpenDB();
		IOMode = 1;
	}
	else {
		std::cout << "That is not a valid command, please try again." << std::endl;
		ValidIn = false;
		WaitingInput = true;
	}

}

void UserIO::TableMode() {
	if (lastCommand == "list") {
		db.ListTable(commandParam);
	}
	else if (lastCommand == "headers") {
		QueryTableHeaders();
	}
	else if (lastCommand == "quit" or lastCommand == "exit") {
		ExitHandle();
	}
}

void UserIO::QueryTableHeaders() {
	std::string SQL_query = "SELECT name FROM PRAGMA_table_info('" + commandParam + "');";
	db.ManipDB(&SQL_query);
}

void UserIO::TableInputMode() {

}