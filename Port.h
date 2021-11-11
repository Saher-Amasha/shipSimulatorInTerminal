//
// Created by Admin on 6/18/2021.
//

#ifndef UNTITLED2_PORT_H
#define UNTITLED2_PORT_H

#include <string>
#include <queue>
#include <list>
#include "Sim_object.h"
#include "Geometry.h"
#include "Ship.h"
#define MAX_CONTAINERS_IN_PORT 500
class Port: public Sim_object {
protected:
	Point _coordinates;
	double _fuel { };
	int _containers;
	int _FPH;
	std::queue<std::unique_ptr<Ship>> _fuelQueue;
public:
	Port(std::string name, double x, double y, double Fuel = 10000,
			int containers = 0, int FPH = 10);

	virtual const Point& getPosition() const;

	void setCoordinates(const Point &coordinates);

	virtual void update();

	void addShipToFuelQueue(Ship *a);

	int getContainers() const;

	void setContainers(int containers);
	void status() override;

	virtual ~Port() = default;
};

#endif //UNTITLED2_PORT_H
