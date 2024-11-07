#include "Utilities.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::string LoadFileAsString(const std::string& filename){
	std::stringstream bufferedLines;
	std::ifstream file(filename);
	std::string line;

	if (file.is_open()) {
		std::cout << "\x1B[32mOpened File: \x1B[33m" << filename << "\033[0m" << std::endl;
		while (getline(file, line)) {
			bufferedLines << line << std::endl;
			std::cout << "\t" << line << std::endl;
		}
		std::cout << "\x1B[33m" << filename << "\x1B[32m successfully converted to string.\033[0m" << std::endl;
		file.close();
		return bufferedLines.str();
	}
	else {
		std::cout << "\x1B[31m!!!ERROR: File could not be loaded: \x1B[33m" << filename << "\033[0m" << std::endl;
		return bufferedLines.str();
	}
}
