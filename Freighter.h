//
// Created by Admin on 6/18/2021.
//

#ifndef UNTITLED2_FREIGHTER_H
#define UNTITLED2_FREIGHTER_H

#include "Model.h"
class Freighter: public Ship {
public:
	Freighter(const string &name, const Point &position, const int &resistance,
			int container = 0) :
			Ship(name, position, freighter), _containers(container), _fuel(
			FREIGHTER_FUEL_TANK_CAPACITY), _resistance(resistance) {
	}
	virtual void update();

	void concreteStatus();

	void refuel(const double &fuel);

	void dock();

	void load(const int &containers);

	void unload(const int &containers);

	void status() override;

	virtual ~Freighter() {
	}

	int getContainers() const {
		return _containers;
	}

	void setContainers(int containers) {
		_containers = containers;
	}

	double getFuel() const {
		return _fuel;
	}

	void setFuel(double fuel) {
		_fuel = fuel;
	}

	int getResistance() const {
		return _resistance;
	}

	void setResistance(int resistance) {
		_resistance = resistance;
	}

private:
	int _containers;
	double _fuel;
	int _resistance;
};

#endif //UNTITLED2_FREIGHTER_H
