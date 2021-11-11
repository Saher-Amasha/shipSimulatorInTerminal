//
// Created by Admin on 6/18/2021.
//

#ifndef UNTITLED2_CONTROLLER_H
#define UNTITLED2_CONTROLLER_H

#include <list>
#include <cstdio>
#include <sstream>
#include "Sim_object.h"
#include "Model.h"

class Controller {
public:
	Controller(View *viewPtr);

	virtual ~Controller() = default;
	//get a path to a file as input and adds all the ports in the file
	static void init(std::string Filepath);

	// creates View object, runs the program by accepting user commands, then destroys View object
	void run();

	static void CreateObject(string command);

	int getCommandIndex(string first);

	const list<string>& getCommandList() const;

	void setCommandList(const list<string> &commandList);

	int getTime() const;

	void setTime(int time);

	View* getViewPtr() const;

	void setViewPtr(View *viewPtr);

	void pan(string command);

	void zoom(string command);

	void size(string command);

	void defaultSettings();

	/* the function separate the word "line" by the character del and returns the words as vector
	 * for example tokenize("cpp hw2 ", ' ') => { "hw2" , "cpp" }  */
	vector<string> tokenize(string line, char del) {
		vector<string> tokens;
		stringstream check1(line);
		string intermediate;
		while (getline(check1, intermediate, del)) {
			tokens.push_back(intermediate);
		}
		return tokens;
	}

private:
	std::list<string> _commandList;
	int _time = 0;
	View *_view_ptr { };
};

#endif //UNTITLED2_CONTROLLER_H
