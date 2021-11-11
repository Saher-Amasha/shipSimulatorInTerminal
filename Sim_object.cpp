//
// Created by Admin on 6/18/2021.
//

#include <algorithm>
#include <cmath>
#include "Sim_object.h"


const std::string &Sim_object::getName() const {
    return _name;
}

void Sim_object::setName(const std::string &name) {
    Sim_object::_name = name;
}

Sim_object::Sim_object(std::string name, object_type type_name): _type(type_name)
{

    if (name.size() > MAX_NAME_SIZE)
        throw "ERROR: _name too long";

    //checks if _name is made up of only alphabet letters
    if (!(std::find_if(name.begin(), name.end(), [](char c) { return !std::isalpha(c); }) != name.end())) {
        this->_name = name;
    } else throw "ERROR: _name contains something other than letters";

}

object_type Sim_object::getType() const {
    return _type;
}

void Sim_object::setType(object_type type) {
    Sim_object::_type = type;
}

void Sim_object::status() {
   // cout<<this->getName()<<endl;

}

bool inProximity(Point a,Point b,int radius)
{
    //check if two points are in proximity
  return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2)) <= radius;
}