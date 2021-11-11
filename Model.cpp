//
// Created by Admin on 6/18/2021.
//

#include "Model.h"
#include "Freighter.h"
#include "Boat_patrol.h"
#include "Cruiser.h"
std::unique_ptr<Model> Model::_ptr = nullptr; // initialized during or immediately after loading

Model& Model::get_Instance() {
	if (_ptr == nullptr)
		_ptr = std::unique_ptr<Model>(new Model());
	return *(_ptr.get());
}

Model::Model() {
}

void Model::update() {
	Port *closest = nullptr;
	Boat_patrol *b_p = nullptr;
	for (unsigned int i = 0; i < _Sim_object_vector.size(); i++) {
		/* if the object is a patrol boat then do the next
		 * time step of the 3 ( refuel -> dock -> set next port destination) */
		if (_Sim_object_vector[i]->getType() == patrol) {
			switch ((dynamic_cast<Boat_patrol*>(_ship_vector[getShipByName(
					_Sim_object_vector[i]->getName())].get()))->getStep()) {
			case -1:
				closest = findClosestPort(_Sim_object_vector[i]->getPosition());
				destination(_Sim_object_vector[i]->getName(),
						closest->getName(),
						_ship_vector[getShipByName(
								_Sim_object_vector[i]->getName())]->getSpeed());
				_Sim_object_vector[i]->update();
				break;
			case 0:
				_Sim_object_vector[i]->update();
				break;
			case 1:
				_Sim_object_vector[i]->update();
				break;
			case 2:
				break;
			case 3:
				// this is the step the patrol boat chooses the next close port
				closest = findClosestPort(_Sim_object_vector[i]->getPosition());
				b_p = dynamic_cast<Boat_patrol*>(_ship_vector[getShipByName(
						_Sim_object_vector[i]->getName())].get());
				destination(_Sim_object_vector[i]->getName(),
						closest->getName(), b_p->getSpeed());
				b_p->setStep(0);
				break;
			case 4:
				// after we got in the port , now refuel (in other words add the ship to the queue of the
				// ships the port will refuel
				closest = findClosestPort(_Sim_object_vector[i]->getPosition());
				closest->addShipToFuelQueue(
						dynamic_cast<Boat_patrol*>(_ship_vector[getShipByName(
								_Sim_object_vector[i]->getName())].get()));
				break;
			default:
				break;
			}
			return;
		} else {
			_Sim_object_vector[i]->update();
		}
	}
}

void Model::addShip(Ship *newShip) {
	_Sim_object_vector.emplace_back(newShip);
	_ship_vector.emplace_back(newShip);
}
void Model::addCruiser(std::string name, Point position, int power,
		double captureRange) {
	if (name.length() > 2)
		name = name.substr(0, 2);
	std::unique_ptr<Cruiser> p = make_unique<Cruiser>(name, position, power,
			captureRange);
	auto a = new Cruiser(name, position, power, captureRange);
	_Sim_object_vector.emplace_back(a);
	_ship_vector.emplace_back(a);
}

void Model::addPort(Port *a) {
	_Sim_object_vector.emplace_back(a);
	_port_vector.emplace_back(a);
}

void Model::addPort(std::string name, double x, double y, double Fuel,
		int containers, int FPH) {
	if (name.length() > 2)
		name = name.substr(0, 2);
	auto p = new Port(name, x, y, Fuel, containers, FPH);
	_Sim_object_vector.emplace_back(p);
	_port_vector.emplace_back(p);
}

void Model::addView(View *newView) {
	_view_vector.emplace_back(newView);

}
void Model::Attatch(Ship &newShip, Port &newPort) {

}

void Model::Dettatch(Ship &newShip, Port &newPort) {

}

const vector<std::unique_ptr<Sim_object>>& Model::getSimObjectVector() {
	return _Sim_object_vector;
}

const vector<std::unique_ptr<Ship>>& Model::getShipVector() const {
	return _ship_vector;
}

const vector<std::unique_ptr<Port>>& Model::getPortVector() const {
	return _port_vector;
}

const vector<std::unique_ptr<View>>& Model::getViewVector() const {
	return _view_vector;
}

int Model::getShipByName(const std::string &name) {
	for (unsigned int i = 0; i < _ship_vector.size(); ++i) {
		auto &k = _ship_vector.at(i);
		if (k != nullptr && k.get()->getName() == name) {
			return i;
		}
	}
	throw "Ship not found !";
}

Port* Model::getPortByName(std::string name) {
	int q = 0;
	for (auto &i : _port_vector) {
		q++;
		if (i->getName() == name) {
			auto temp = i.get();
			// _port_vector.erase(_port_vector.cbegin()+q);
			return temp;
		}
	}
	throw "Port not found !";
}

void Model::destination(std::string shipName, std::string portName,
		double speed) {
	int q = getShipByName(shipName);
	if (_ship_vector[q]->getType() == cruiser)
		throw "ERROR Cruiser only moves in a direction";
	_ship_vector[q]->destination(speed, portName);
}

void Model::course(std::string shipName, double angle, double speed) {
	auto a = getShipByName(shipName);
	auto b = _ship_vector[a].get();
	b->Course(angle, speed);

}

void Model::position(std::string shipName, double x, double y, double speed) {
	auto a = getShipByName(shipName);
	if (_ship_vector[a]->getType() == cruiser)
		throw "ERROR Cruiser only moves in a direction";
	else
		_ship_vector[getShipByName(shipName)].get()->Position(x, y, speed);
}

void Model::load_at(std::string shipName, std::string portName) {
	auto a = getShipByName(shipName);
	auto port = getPortByName(portName);
	if (_ship_vector[a]->getType() != freighter) {
		throw "ERROR only freighter can load ";
	}
	if (inProximity(_ship_vector[a]->getPosition(), port->getPosition(), 0.1)) {
		int needed = MAX_CONTAINERS_IN_FREIGHTER
				- dynamic_cast<Freighter&>(*_ship_vector[a]).getContainers();
		int final =
				(port->getContainers() > needed) ?
						needed : port->getContainers();
		dynamic_cast<Freighter&>(*_ship_vector[a]).load(final);
		port->setContainers(port->getContainers() - final);
	}
}

void Model::unload_at(std::string shipName, std::string portName,
		double numberOfShipmentsToUnload) {
	auto a = getShipByName(shipName);
	auto port = getPortByName(portName);
	if (_ship_vector[a]->getType() != freighter)
		throw "ERROR only freighter can load ";
	if (inProximity(_ship_vector[a]->getPosition(), port->getPosition(), 0.1)) {
		int needed = MAX_CONTAINERS_IN_PORT - port->getContainers();
		int final =
				(dynamic_cast<Freighter&>(*_ship_vector[a]).getContainers()
						> needed) ? needed : port->getContainers();
		port->setContainers(port->getContainers() + final);
		dynamic_cast<Freighter&>(*_ship_vector[a]).unload(final);

	}
}

void Model::addBoatPatrol(string &name, Point position, const int &resistance) {
	if (name.length() > 2)
		name = name.substr(0, 2);
	std::unique_ptr<Boat_patrol> p = make_unique<Boat_patrol>(name, position,
			resistance);
	auto a = new Boat_patrol(name, position, resistance);
	_Sim_object_vector.emplace_back(a);
	_ship_vector.emplace_back(a);
}

void Model::addFreighter(string &name, const Point &position,
		const int &resistance, int container) {
	if (name.length() > 2) {
		name = name.substr(0, 2);
	}
	std::unique_ptr<Freighter> p = make_unique<Freighter>(name, position,
			resistance, container);
	auto a = new Freighter(name, position, resistance, container);
	_Sim_object_vector.emplace_back(a);
	_ship_vector.emplace_back(a);
}

Port* Model::findClosestPort(const Point &point) {
	if (_port_vector.empty() == true) {
		throw "there is no ports yet !";
	}
	Port *found = nullptr;
	Point temp = _port_vector[0]->getPosition();
	double min_dist = sqrt(
			pow(point.x - temp.x, 2) + pow(point.y - temp.y, 2) * 1.0), dist;
	for (unsigned int i = 0; i < _port_vector.size(); i++) {
		temp = _port_vector[i]->getPosition();
		dist = sqrt(pow(point.x - temp.x, 2) + pow(point.y - temp.y, 2) * 1.0);
		if (dist <= min_dist) {
			found = _port_vector[i].get();
			min_dist = dist;
		}
	}
	return found;
}

void Model::status() {
	for (auto &i : _Sim_object_vector)
		i->status();
}
