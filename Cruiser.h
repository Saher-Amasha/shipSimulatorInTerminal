//
// Created by Admin on 6/18/2021.
//

#ifndef UNTITLED2_CRUISER_H
#define UNTITLED2_CRUISER_H

#include "Model.h"
class Cruiser: public Ship {
	int _force;
	double _captureRange;
public:
	Cruiser(std::string name, Point position, int power, double captureRange) :
			Ship(std::move(name), position, object_type::cruiser), _force(
					power), _captureRange(captureRange) {
	}
	void update() override;
	void concreteStatus();
	void attack(std::string shipName);
	void status() override;
};
Point nextState(Point a, double angle, double speed);

Point nextState(Point a, Point b, double speed);

#endif //UNTITLED2_CRUISER_H
