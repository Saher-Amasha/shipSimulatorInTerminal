//
// Created by Admin on 6/18/2021.
//

#include <cmath>
#include "Freighter.h"

// Stopped, Docked, Dead, MovingTo, MovingOnCourse
void Freighter::update() {
	/* check if the fuel is equal or less than 0
	 * if so -> don't do move the ship and update the state of the ship to "stopped" */
	if (_fuel <= 0 && _currentState != Dead) {
		setCurrentState(Stopped);
		return;
	}
	switch (_currentState) {
	/* if the ship is "stopped" , "docked" or "dead" then don't update the ship location */
	case Stopped:
		return;
		break;
	case Docked:
		return;
		break;
	case Dead:
		return;
		break;
	case MovingTo:
		_fuel -= (int) getSpeed() * FREIGHTER_CONSUMPTION;
		MoveAgent(_position, _currentDestination, getSpeed());
		break;
	case MovingOnCourse:
		_fuel -= (int) getSpeed() * FREIGHTER_CONSUMPTION;
		MoveAgent(_position, _currentDestination, getSpeed());
		break;
	default:
		break;
	}
}

void Freighter::concreteStatus() {
	std::cout << "Freighter " << getName() << " at ";
	getPosition().print();
	cout << ", fuel: " << ((_fuel > 0) ? _fuel : 0);
	cout << ", resistance: " << _resistance;
	std::cout << ", ";
	this->printStatus("");
	std::cout << " ,speed " << std::setprecision(4) << std::round(getSpeed())
			<< " nm/hr";
	cout << ", Containers: " << _containers << endl;

}

void Freighter::refuel(const double &fuel) {
	if (_currentState != Docked)
		throw "The ship isn't at a port at the moment";
	if (fuel < 0)
		throw "Not a valid amount of fuel at the port";
	int needed_fuel = FREIGHTER_FUEL_TANK_CAPACITY - fuel;
	if (needed_fuel <= fuel) {
		_fuel += needed_fuel;
	} else if (needed_fuel > fuel) {
		_fuel += fuel;
	}
}

void Freighter::dock() {
	if (_currentState == Dead || _currentState == Stopped)
		throw "Can't dock at the moment";

	/*
	 //checks if ship is near any port
	 for (auto & i : Model::get_Instance().getPortVector()){
	 if (inProximity(this->_position,i->getPosition())){
	 _currentState = Docked;
	 _currentPort=i->getName();
	 }
	 }

	 */
	return;

}

void Freighter::load(const int &containers) {
	if (_currentState != Docked)
		throw "The ship isn't at a port at the moment";
	_containers += containers;
	return;
}

void Freighter::unload(const int &containers) {
	if (_currentState != Docked)
		throw "The ship isn't at a port at the moment";
	if (containers > _containers)
		throw "The number of requested _containers is more than what the ship has at the moment";
	_containers -= containers;

}

void Freighter::status() {
	this->concreteStatus();
}
