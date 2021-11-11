//
// Created by Admin on 6/18/2021.
//

#ifndef UNTITLED2_BOAT_PATROL_H
#define UNTITLED2_BOAT_PATROL_H

#include "Model.h"
#include "Ship.h"

class Boat_patrol: public Ship {
public:
	Boat_patrol(const string &name, Point position, const int &resistance) :
			Ship(name, position, object_type::patrol), _fuel(
			PATROL_BOAT_FUEL_TANK_CAPACITY), _resistance(resistance) {
	}
	virtual void update();

	void status() override;

	void concreteStatus();

	void dock();

	void finish_route(); // this function is called only if the boat visited all the ports once

	virtual ~Boat_patrol() = default;

	void reFuel(double fuel);

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

	bool isFinished() const {
		return _finished;
	}

	void setFinished(bool finished = false) {
		_finished = finished;
	}

	int getStep() const {
		return _step;
	}

	void setStep(int step = 0) {
		_step = step;
	}

private:
	double _fuel;
	int _resistance;
	bool _finished = false;
	int _step = -1;
	/*
	 * step = -1 => the ship has just been created
	 * step = 0 => the ship is stopped
	 * step = 1 => the ship is moving
	 * step = 2 => the ship is dead
	 * step = 3 => the ship is deciding which ship to move next
	 * step = 4 => the ship is trying to get fuel
	 */
};

#endif //UNTITLED2_BOAT_PATROL_H
