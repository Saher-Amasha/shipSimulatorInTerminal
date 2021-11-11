//
// Created by Admin on 6/18/2021.
//

#include <cmath>
#include "Boat_patrol.h"

void Boat_patrol::update() {
	/* first check if the boat didn't finish the Route (still didn't visit all the ports once) */
	/* if still -> update the boat*/
	if (!_finished) {
		/* check if the fuel is equal or less than 0
		 * if so -> don't do move the ship and update the state of the ship to "stopped" */
		if (_fuel <= 0) {
			setCurrentState(Stopped);
			_step = 0;
			return;
		}
		switch (_currentState) {
		/* if the ship is "stopped" , "docked" or "dead" then don't update the ship location */
		case Stopped:
			return;
			break;
		case Docked:
			_step = 3;
			return;
			break;
		case Dead:
			_step = 2;
			return;
			break;
		case MovingTo:
			_step = 1;
			_fuel -= (int) getSpeed() * PATROL_BOAT_CONSUMPTION;
			MoveAgent(_position, _currentDestination, getSpeed());
			break;
		case MovingOnCourse:
			_step = 1;
			_fuel -= (int) getSpeed() * PATROL_BOAT_CONSUMPTION;
			MoveAgent(_position, _currentDestination, getSpeed());
			break;
		default:
			break;
		}
		/* check if the boat is at the destination port
		 * and update the state of the boat if so */
		if (_position == _currentDestination) {
			dock();
		}
	}
}

void Boat_patrol::concreteStatus() {
	std::cout << "Patrol_boat " << getName() << " at ";
	getPosition().print();
	cout << ", fuel: " << _fuel;
	cout << ", resistance: " << _resistance;
	std::cout << ", ";
	this->printStatus("");
	std::cout << ", speed " << std::setprecision(4) << round(getSpeed())
			<< " nm/hr" << endl;
}

void Boat_patrol::dock() {
	if (_currentState == Dead || _currentState == Stopped)
		throw "Can't dock at the moment";
	_currentState = Docked;
	_step = 4;
	return;
}

void Boat_patrol::finish_route() {
	setFinished(true);
}

void Boat_patrol::reFuel(double fuel) {
	if (_currentState != Docked)
		throw "The ship isn't at a port at the moment";
	if (fuel < 0)
		throw "Not a valid amount of fuel at the port";
	int needed_fuel = PATROL_BOAT_FUEL_TANK_CAPACITY - fuel;
	if (needed_fuel <= fuel) {
		_fuel += needed_fuel;
	} else if (needed_fuel > fuel) {
		_fuel += fuel;
	}
	_step = 0;
}

void Boat_patrol::status() {
	this->concreteStatus();
}
