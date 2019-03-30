#ifndef DATA_LOADING_UTILITY_H
#define DATA_LOADING_UTILITY_H

#include "Utility/utility.hpp"

template <typename T>
void fillVariable(std::stringstream &iss, T &var, string name)
{
	if (!(iss >> var)) {
		cout << "Unable to fill variable: " << name << endl;
		exit(1);
	}
}

template <typename T>
void fillVariable(std::ifstream &ifs, T &var, string name)
{
	if (!(ifs >> var)) {
		cout << "Unable to fill variable: " << name << endl;
		exit(1);
	}
}

template <typename T>
void fillVector(std::stringstream&iss, vector<T> &var, int to, string name)
{
	for (int i = 0; i < to; i++) {
		T data;
		fillVariable(iss, data, name);
		var.push_back(data);
	}
}

template <typename T>
void fillVector(std::ifstream& ifs, vector<T> &var, int to, string name)
{
	for (int i = 0; i < to; i++) {
		T data;
		fillVariable(ifs, data, name);
		var.push_back(data);
	}
}

int getPreviouslyReadIndex(vector<string> prevReadFileNames, string fileName);
void checkValidFilename(std::ifstream &ifs, string fileName);
void checkExtraText(std::stringstream &iss, string type);
void checkValidSeparatorAndMove(std::stringstream &iss, string type);
void moveToNextLine(std::stringstream &iss);
void moveToNextLine(std::ifstream &ifs);

#endif
