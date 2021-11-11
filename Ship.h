//
// Created by Admin on 6/18/2021.
//

#ifndef UNTITLED2_SHIP_H
#define UNTITLED2_SHIP_H

#include <string>
#include <limits>
#include <iostream>
#include <utility>
#include <cmath>
#include <memory>
#include "Sim_object.h"
#define FREIGHTER_FUEL_TANK_CAPACITY 900
#define FREIGHTER_MAX_SPEED 15
#define FREIGHTER_CONSUMPTION 2000
#define PATROL_BOAT_FUEL_TANK_CAPACITY 900
#define PATROL_BOAT_MAX_SPEED 15
#define PATROL_BOAT_CONSUMPTION 2000
#define Cruiser_MAX_SPEED 75
#define MAX_CONTAINERS_IN_FREIGHTER 20
#define INFINITE_POINT Point(std::numeric_limits<double>::max(), std::numeric_limits<double>::max())
enum state {
	Stopped, Docked, Dead, MovingTo, MovingOnCourse
};
class Ship: public Sim_object {
protected:
	state _currentState;

	Point _position;

	double _speed;
	double _angle;

	Point _currentDestination;
	std::string _currentPort;

public:

	Ship(std::string new_name, Point position, object_type type) :
			Sim_object(new_name, type), _currentState(Stopped), _position(
					position), _speed(0), _angle(90) {
	}
	;

	virtual void update() =0;

	void Position(double x, double y, double newSpeed);

	void Course(double angle, double speed, const Point &destination =
	INFINITE_POINT);

	void destination(double new_speed, const std::string &portName);

	double getAngle() const;

	void setAngle(double angle);

	void stop();

	void printStatus(std::string end = "\n");

	double getSpeed() const;

	void setSpeed(double speed);

	const Point& getPosition() const override;

	void setPosition(const Point &position);

	const Point& getDestination() const;

	void setDestination(const Point &destination);

	state getCurrentState() const;

	void setCurrentState(state currentState);

	static std::string getState_Name(state s);

	virtual ~Ship() = default;
	void status() override;
};

double calc_angle(const Point &origin, const Point &destination);

bool MoveAgent(Point &origin, const Point &destination, const double &speed,
		double angle2 = std::numeric_limits<double>::max());

#endif //UNTITLED2_SHIP_H
