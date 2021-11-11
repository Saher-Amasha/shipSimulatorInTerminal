//
// Created by Admin on 6/18/2021.
//

#ifndef UNTITLED2_SIM_OBJECT_H
#define UNTITLED2_SIM_OBJECT_H

#include <string>
#include <utility>
#include "Geometry.h"

#define MAX_NAME_SIZE 12
enum object_type {
	port, cruiser, freighter, patrol
};
class Sim_object {
private:

	std::string _name;
	object_type _type;
public:
	Sim_object(std::string name, object_type type_name);

	const std::string& getName() const;

	void setName(const std::string &name);

	virtual void update()=0;

	virtual const Point& getPosition() const =0;

	object_type getType() const;

	void setType(object_type type);

	virtual void status();
	virtual ~Sim_object() = default;
};

bool inProximity(Point a, Point b, int radius);
#endif //UNTITLED2_SIM_OBJECT_H
