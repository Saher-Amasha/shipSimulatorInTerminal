//
// Created by Admin on 6/18/2021.
//

#include "Controller.h"
#include "Cruiser.h"
#include "Freighter.h"
#include <fstream>
#include <algorithm>

Controller::Controller(View *viewPtr) {
	_view_ptr = viewPtr;

	_commandList.emplace_back("create"); // 1

	_commandList.emplace_back("status"); // 2

	_commandList.emplace_back("go"); // 3

	_commandList.emplace_back("show"); // 4

	_commandList.emplace_back("pan"); // 5

	_commandList.emplace_back("zoom"); // 6

	_commandList.emplace_back("size"); // 7

	_commandList.emplace_back("default"); // 8

	_commandList.emplace_back("course"); // 9

	_commandList.emplace_back("position");  // 10

	_commandList.emplace_back("destination"); // 11

	_commandList.emplace_back("load_at"); // 12

	_commandList.emplace_back("unload_at"); // 13

	_commandList.emplace_back("dock_at"); // 14

	_commandList.emplace_back("refuel"); // 15

	_commandList.emplace_back("attack"); // 16

	_commandList.emplace_back("stop"); // 17
}

void Controller::run() {

	bool sea_craft_cmd = true;
	vector<string> cmd;
	int index;
	while (true) {
		sea_craft_cmd = true;
		std::cout << "Time " << _time << ": Enter command: ";
		//get Command and store it in the variable command
		string command;
		getline(cin, command);
		cmd = tokenize(command, ' ');
		if (cmd.size() == 1 && cmd[0] == "exit")
			return;
		//get the first word in the string command
		switch (getCommandIndex(command.substr(0, command.find(' ')))) {
		/* this switch case is for the View & Model*/
		case 0:
			cout << "create " << endl;
			//command CreateObject
			sea_craft_cmd = false;
			CreateObject(command);
			break;
		case 1:
			cout << "status" << endl;
			sea_craft_cmd = false;
			//command get status
			//todo add virtual method print status to simObject
			Model::get_Instance().status();
			break;
		case 2:
			cout << "go" << endl;
			sea_craft_cmd = false;
			// command go
			Model::get_Instance().update();
			_time++;
			break;
		case 3:
			cout << "show" << endl;
			sea_craft_cmd = false;
			_view_ptr->show();
			break;
		case 4:
			cout << "pan " << endl;
			sea_craft_cmd = false;
			pan(command);
			break;
		case 5:
			cout << "zoom" << endl;
			sea_craft_cmd = false;
			zoom(command);
			break;
		case 6:
			cout << "size " << endl;
			sea_craft_cmd = false;
			size(command);
			break;
		case 7:
			cout << "default" << endl;
			sea_craft_cmd = false;
			defaultSettings();
			break;
		default:
			break;
		}
		/* if the command is for the sea crafts then
		 * the next switch case will work */
		if (sea_craft_cmd) {
			switch (getCommandIndex(cmd[1])) {
			case 8:
				cout << "course" << endl;
				cmd = tokenize(command, ' ');
				if (cmd.size() != 4) {
					cerr << "command not valid ! " << endl;
					return;
				}
				try {
					index = Model::get_Instance().getShipByName(
							cmd[0].substr(0, 2));
					Model::get_Instance().getShipVector()[index]->setAngle(
							stod(cmd[2]));
					Model::get_Instance().getShipVector()[index]->setSpeed(
							stod(cmd[3]));
				} catch (...) {
					cerr << "command not valid ! " << endl;
					return;
				}
				break;
			case 9:
				cout << "position " << endl;
				if (cmd.size() != 5) {
					cerr << "command not valid ! " << endl;
					return;
				}
				try {
					// ship position 1 3 200
					Model::get_Instance().position(cmd[0].substr(0, 2),
							stod(cmd[2]), stod(cmd[3]), stod(cmd[4]));
				} catch (...) {
					cerr << "command not valid ! " << endl;
					return;
				}
				break;
			case 10:
				cout << "destination" << endl;
				if (cmd.size() != 4) {
					cerr << "command not valid ! " << endl;
					return;
				}
				try {
					// Emma destination PearlHarbor 10
					Model::get_Instance().destination(cmd[0].substr(0, 2),
							cmd[2].substr(0, 2), stod(cmd[3]));
				} catch (...) {
					cerr << "command not valid ! " << endl;
					return;
				}
				break;
			case 11:
				// Emma load_at PearlHarbor
				cout << "load_at" << endl;
				if (cmd.size() != 3) {
					cerr << "command not valid ! " << endl;
					return;
				}
				try {
					Model::get_Instance().load_at(cmd[0].substr(0, 2),
							cmd[2].substr(0, 2));
				} catch (...) {
					cerr << "command not valid ! " << endl;
					return;
				}
				break;
			case 12:
				// Emma unload_at Valdez 100
				cout << "unload_at" << endl;
				if (cmd.size() != 4) {
					cerr << "command not valid ! " << endl;
					return;
				}
				try {
					Model::get_Instance().unload_at(cmd[0].substr(0, 2),
							cmd[2].substr(0, 2), stoi(cmd[3]));
				} catch (...) {
					cerr << "command not valid ! " << endl;
					return;
				}
				break;
			case 13:
				// Emma dock_at PearlHarbor
				cout << "dock_at" << endl;
				if (cmd.size() != 3) {
					cerr << "command not valid ! " << endl;
					return;
				}
				try {
					index = Model::get_Instance().getShipByName(
							cmd[0].substr(0, 2));
					Model::get_Instance().destination(cmd[0].substr(0, 2),
							cmd[2].substr(0, 2),
							Model::get_Instance().getShipVector()[index]->getSpeed());
				} catch (...) {
					cerr << "command not valid ! " << endl;
					return;
				}
				break;
			case 14:
				// Emma refuel
				cout << "refuel" << endl;
				if (cmd.size() != 2) {
					cerr << "command not valid ! " << endl;
					return;
				}
				try {
					// port, cruiser, freighter, patrol
					index = Model::get_Instance().getShipByName(
							cmd[0].substr(0, 2));
					if (Model::get_Instance().getShipVector()[index]->getType()
							== port
							|| Model::get_Instance().getShipVector()[index]->getType()
									== cruiser) {
						cerr << "command not valid ! " << endl;
						return;
					}
					/* there is no need to use the refuel for the patrol boat
					 * because the update function of the ports & Boat_patrol will do the job  */
					if (Model::get_Instance().getShipVector()[index]->getType()
							== freighter) {
						dynamic_cast<Freighter*>(Model::get_Instance().getShipVector()[index].get())->refuel(
								900);
						/* 900 is the full capacity of the fuel tank of the freighter ship*/
					}
				} catch (...) {
					cerr << "command not valid ! " << endl;
					return;
				}
				break;
			case 15:
				// Emma attack ship
				cout << "attack" << endl;
				if (cmd.size() != 3) {
					cerr << "command not valid ! " << endl;
					return;
				}
				try {
					// port, cruiser, freighter, patrol
					index = Model::get_Instance().getShipByName(
							cmd[0].substr(0, 2));
					Model::get_Instance().getShipByName(cmd[2]); // just to check if the is found (exists)
					if (Model::get_Instance().getShipVector()[index]->getType()
							== cruiser) {
						dynamic_cast<Cruiser*>(Model::get_Instance().getShipVector()[index].get())->attack(
								cmd[2]);
					} else {
						cerr << "command not valid ! " << endl;
						return;
					}
				} catch (...) {
					cerr << "command not valid ! " << endl;
					return;
				}
				break;
			case 16:
				break;
			default:
				/* if the command isn't for the view,model or sea crafts
				 *  then the command isn't valid */
				cerr << "Invalid command ! " << endl;
				return;
			}
		}
	}
}

void Controller::CreateObject(string command) {
	char d1, d2, d3;
	int arg1, arg2;
	double x, y;
	string create, name, type;
	stringstream ss(command);

	if ((ss >> create >> name >> type >> d1 >> x >> d2 >> y >> d3 >> arg1)
			&& d1 == '(' && d2 == ',' && d3 == ')' && create == "create") { // verify that separators are correct
		if (type == "Port") {
			ss >> arg2;
			Model::get_Instance().addPort(name, x, y, arg1, 0, arg2);
		} else if (type == "Cruiser") {
			ss >> arg2;
			Model::get_Instance().addCruiser(name, Point(x, y), arg1, arg2);
		} else if (type == "Freighter") {
			ss >> arg2;
			Model::get_Instance().addFreighter(name, Point(x, y), arg1, arg2);
		} else if (type == "Patrol_boat")
			Model::get_Instance().addBoatPatrol(name, Point(x, y), arg1);
		else
			throw "Type not legal";
	}
}

void Controller::init(std::string Filepath) {
	ifstream inData;

	inData.open(Filepath); // opens the file

	//check if file is open
	if (!inData) {
		cerr << "Error: file could not be opened" << endl;
		exit(1);
	}

	//CreateObject variable to house data in file
	char d1, d2, d3;
	int newFPH, CurrentFuel;
	double x, y;
	string portName;

	while (!inData.eof()) { // keep reading until end-of-file
		//check if line is in the correct format and add the port accordingly
		if ((inData >> portName >> d1 >> x >> d2 >> y >> d3 >> CurrentFuel
				>> newFPH) && d1 == '(' && d3 == ')' && d2 == ',') // verify that separators are correct
			Model::get_Instance().addPort(portName, x, y, CurrentFuel, 0,
					newFPH);
	}

	//close file
	inData.close();

}

int Controller::getCommandIndex(string first) {
	return distance(_commandList.begin(),
			find_if(_commandList.begin(), _commandList.end(),
					[&](const string &val) {
						return (first == val);
					}));
}

const list<string>& Controller::getCommandList() const {
	return _commandList;
}

void Controller::setCommandList(const list<string> &commandList) {
	_commandList = commandList;
}

int Controller::getTime() const {
	return _time;
}

void Controller::setTime(int time) {
	_time = time;
}

View* Controller::getViewPtr() const {
	return _view_ptr;
}

void Controller::setViewPtr(View *viewPtr) {
	_view_ptr = viewPtr;
}
void Controller::pan(string command) {
	char d1, d2, d3;
	double x, y;
	string commandName;
	stringstream ss(command);

	if ((ss >> commandName >> d1 >> x >> d2 >> y >> d3) && d1 == '('
			&& d2 == ',' && d3 == ')') {   // verify that separators are correct
		if (commandName == "pan")
			_view_ptr->pan(Point(x, y));
	}
}

void Controller::zoom(string command) {

	double y;
	string commandName;
	stringstream ss(command);

	if (ss >> commandName >> y) // verify that separators are correct
		if (commandName == "zoom")
			_view_ptr->zoom(y);

}

void Controller::size(string command) {
    double y;
    string commandName;
    stringstream ss(command);

    if (ss >> commandName >> y) // verify that separators are correct
        if (commandName == "size")
            _view_ptr->size(y);

}

void Controller::defaultSettings() {
    _view_ptr->defaultSettings();

}
