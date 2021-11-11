//
// Created by Admin on 6/18/2021.
//

#include "Cruiser.h"
#include "Freighter.h"
#include "Boat_patrol.h"

void Cruiser::update() {
	switch (_currentState) {
	/* if the ship is "stopped" , "docked" or "dead" then don't update the ship location */
	case Stopped:

	case Docked:

	case Dead:
		break;

	case MovingTo:
		MoveAgent(_position, _currentDestination, getSpeed());
		break;
	case MovingOnCourse:
		MoveAgent(_position, _currentDestination, getSpeed(), _angle);
		break;
	default:
		break;
	}
}

void Cruiser::concreteStatus() {
	std::cout << "Cruiser " << getName() << " at";
	getPosition().print();
	std::cout << ", force: " << this->_force << ",";
	if (_currentState != Stopped)
		std::cout << " moving on course " << _angle << " deg,";
	std::cout << " speed " << std::setprecision(4) << std::round(getSpeed())
			<< " nm/hr" << endl;

}

void Cruiser::attack(std::string shipName) {
	for (auto &i : Model::get_Instance().getShipVector()) {
		if (i->getName() == getName())
			continue;
		if (i->getName() == shipName) {
			if (inProximity(nextState(_position, _angle, _speed),
					nextState(i->getPosition(), i->getAngle(), i->getSpeed()),
					_captureRange)) {
				if (i->getType() == object_type::freighter) {
					if (_force
							> dynamic_cast<Freighter*>(i.get())->getResistance()) {
						std::cout << getName() << " Attacked "
								<< i.get()->getName() << std::endl;
						i->update();
						dynamic_cast<Freighter*>(i.get())->setContainers(0);
						_force++;
						i.get()->setCurrentState(state::Dead);
					} else {
						std::cout << getName() << " Failed to Attack "
								<< i.get()->getName() << std::endl;
						_force--;
					}
				} else if (i->getType() == patrol) {
					double wq =
							dynamic_cast<Boat_patrol*>(i.get())->getResistance();
					if (_force
							> dynamic_cast<Boat_patrol*>(i.get())->getResistance()) {
						std::cout << getName() << " Attacked "
								<< i.get()->getName() << std::endl;
						i->update();
						dynamic_cast<Boat_patrol*>(i.get())->setResistance(
								wq--);
						_force++;
						i->stop();
						i->setCurrentState(Dead);
					} else {
						std::cout << getName() << " Failed to Attack "
								<< i.get()->getName() << std::endl;
						dynamic_cast<Boat_patrol*>(i.get())->setResistance(
								wq++);
						_force--;
					}
				}
			} else {
				throw "cant attack cruiser";
			}
		}
	}
}

void Cruiser::status() {
	this->concreteStatus();
}

Point nextState(Point a, double angle, double speed) {
	return Point(a.x + std::abs(std::cos(angle) * speed),
			a.y + std::abs(speed * sin(angle)));

}

Point nextState(Point a, Point b, double speed) {
	Cartesian_vector q;
	q.delta_x = a.x - b.x;
	q.delta_y = a.y - b.y;
	Polar_vector temp = Polar_vector(q);
	return nextState(a, temp.r, speed);
}
