//
// Created by Admin on 6/18/2021.
//

#include <algorithm>
#include "Port.h"
#include "Freighter.h"
#include "Boat_patrol.h"

void Port::update() {
	if (_fuelQueue.empty() == false) {
		if (_fuelQueue.front()->getType() == object_type::freighter) {
			double fuelNeeded =
					FREIGHTER_FUEL_TANK_CAPACITY
							- dynamic_cast<Freighter*>(_fuelQueue.front().get())->getFuel();
			dynamic_cast<Freighter*>(_fuelQueue.front().get())->refuel(
					(_fuel >= fuelNeeded) ? fuelNeeded : _fuel);
			_fuelQueue.pop();
		} else if (_fuelQueue.front()->getType() == object_type::patrol) {

			double fuelNeeded =
					PATROL_BOAT_FUEL_TANK_CAPACITY
							- dynamic_cast<Boat_patrol*>(_fuelQueue.front().get())->getFuel();
			dynamic_cast<Boat_patrol*>(_fuelQueue.front().get())->reFuel(
					(_fuel >= fuelNeeded) ? fuelNeeded : _fuel);
		}
	}

}

Port::Port(std::string name, double x, double y, double Fuel, int containers,
		int FPH) :
		Sim_object(std::move(name), object_type::port), _coordinates(
				Point(x, y)), _fuel(Fuel), _containers(containers), _FPH(FPH) {

}

void Port::setCoordinates(const Point &coordinates) {
	Port::_coordinates = coordinates;
}

const Point& Port::getPosition() const {
	return _coordinates;
}

void Port::addShipToFuelQueue(Ship *a) {
	if (a->getType() == object_type::patrol) {
		if (_fuelQueue.empty()) {
			_fuelQueue.push(std::unique_ptr<Ship>(a));
		}
	} else {
		_fuelQueue.push(std::unique_ptr<Ship>(a));
	}

}

int Port::getContainers() const {
	return _containers;
}

void Port::setContainers(int containers) {
	Port::_containers = containers;
}

void Port::status() {
	Sim_object::status();
}
