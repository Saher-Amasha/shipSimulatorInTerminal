//
// Created by Admin on 6/18/2021.
//

#include <cmath>
#include "Ship.h"
#include "Model.h"
#include <iostream>

bool isPort(Point &destination) {
	Model &a = Model::get_Instance();

//    dynamic_pointer_cast<Port>( a.getSimObjectVector()[4]);
	for (unsigned int i = 0; i < a.getSimObjectVector().size(); i++) {
		if (a.getSimObjectVector()[i]->getType() == object_type::port) {
			if (destination == a.getSimObjectVector()[i]->getPosition())
				return true;
		}
	}
	return false;
}
bool isPort(const std::string &portName) {

	Model &a = Model::get_Instance();

	for (unsigned int i = 0; i < a.getSimObjectVector().size(); i++) {
		if (a.getSimObjectVector()[i]->getType() == object_type::port) {
			if (portName == a.getSimObjectVector()[i]->getName())
				return true;
		}
	}
	return false;

}
Sim_object* getPortByName(std::string portName) {
	Model &a = Model::get_Instance();
	const vector<std::unique_ptr<Sim_object>> &temp = a.getSimObjectVector();
	for (unsigned int i = 0; i < a.getSimObjectVector().size(); i++) {
		if (temp[i]->getType() == object_type::port) {
			if (portName == temp[i]->getName()) {
				return temp[i].get();
			}
		}
	}
	return nullptr;

}

void Ship::stop() {
	_speed = 0;
	_currentState = Stopped;
	_currentDestination = _position;

}

void Ship::printStatus(std::string end) {
	switch (_currentState) {
	case Dead:
		std::cout << "Dead in the water" << end;
		break;
	case Stopped:
		std::cout << "Stopped" << end;
		break;
	case Docked:
		std::cout << "Docked at " << _currentPort << end;
		break;
	case MovingOnCourse:
		std::cout << "Moving on course " << this->_angle << end;
		break;
	case MovingTo:
		if (isPort(_currentDestination)) {
			std::cout << std::setprecision(1) << "Moving to "
					<< this->_currentPort << " on course " << this->_angle
					<< end;
		} else {
			std::cout << "Moving to ";
			_currentDestination.print();
			std::cout << " on course ..." << end;
		}
		break;

	}

}

std::string Ship::getState_Name(state s) {
	return (s == Stopped) ? "Stopped" : (s == Dead) ? "Dead" :
			(s == Docked) ? "Docked" : "Moving";
}

const Point& Ship::getPosition() const {
	return _position;
}

void Ship::setPosition(const Point &position) {
	Ship::_position = position;
}

const Point& Ship::getDestination() const {
	return _currentDestination;
}

void Ship::setDestination(const Point &destination) {
	_currentState = MovingOnCourse;
	_currentDestination = destination;
}

state Ship::getCurrentState() const {
	return _currentState;
}

void Ship::setCurrentState(state currentState) {
	_currentState = currentState;
}

double Ship::getSpeed() const {
	return _speed;
}

void Ship::setSpeed(double speed) {
	double limit = 0;
	switch (this->getType()) {
	case object_type::freighter:
		limit = FREIGHTER_MAX_SPEED;
		break;
	case object_type::patrol:
		limit = PATROL_BOAT_MAX_SPEED;
		break;
	case object_type::cruiser:
		limit = Cruiser_MAX_SPEED;
		break;
	default:
		break;
	}
	if (speed > limit)
		throw "speed is too high";
	Ship::_speed = speed;
}

double Ship::getAngle() const {
	return _angle;
}

void Ship::setAngle(double angle) {
	Ship::_angle = angle;
}

void Ship::Course(double angle, double speed, const Point &destination) {
	_currentState = MovingOnCourse;
	this->_angle = angle;
	this->setSpeed(speed);
	this->setDestination(destination);
}

void Ship::Position(double x, double y, double newSpeed) {
	Point destination(x, y);
	setDestination(destination);
	setSpeed(newSpeed);
	_currentState = MovingTo;
	setAngle(calc_angle(_position, destination));

}

void Ship::destination(double new_speed, const std::string &portName) {
	if (!isPort(portName))
		throw "ERROR: port doesn't exist";
	Position(getPortByName(portName)->getPosition().x,
			getPortByName(portName)->getPosition().y, new_speed);
}

void Ship::status() {
	this->printStatus("\n");
}

double calc_angle(const Point &origin, const Point &destination) {
	double x2 = destination.x;
	double x1 = origin.x;
	double y2 = destination.y;
	double y1 = origin.y;
	double angle = 1 / std::tan((y2 - y1) / (x2 - x1));

	return (angle < 0) ? 2 * M_PI * angle : angle;

}

bool MoveAgent(Point &origin, const Point &destination, const double &speed,
		double angle2) {
	double q = angle2;
	if (angle2 == std::numeric_limits<double>::max())
		q = calc_angle(origin, destination);

	auto dx = std::cos(q) * speed;
	auto dy = std::sin(q) * speed;

	origin.x += dx;
	origin.y += dy;

	return false;
}
