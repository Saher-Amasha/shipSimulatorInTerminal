//
// Created by Admin on 6/18/2021.
//

#ifndef UNTITLED2_MODEL_H
#define UNTITLED2_MODEL_H

#include <list>
#include <cstdio>
#include <vector>
#include <memory>
#include <cmath>

#include "Sim_object.h"
#include "View.h"
#include "Ship.h"
#include "Port.h"

class Model {
protected:
	static std::unique_ptr<Model> _ptr;

private:
	std::vector<std::unique_ptr<Sim_object>> _Sim_object_vector;

	std::vector<std::unique_ptr<Ship>> _ship_vector;

	std::vector<std::unique_ptr<Port>> _port_vector;

	std::vector<std::unique_ptr<View>> _view_vector;

	Model();

public:

	static Model& get_Instance();

	Model(const Model&) = delete;

	Model& operator=(const Model&) = delete;

	Model(const Model&&) = delete;

	Model& operator=(const Model&&) = delete;

	void update();

	const vector<std::unique_ptr<Sim_object>>& getSimObjectVector();

	const vector<std::unique_ptr<Ship>>& getShipVector() const;

	const vector<std::unique_ptr<Port>>& getPortVector() const;

	const vector<std::unique_ptr<View>>& getViewVector() const;

	void addShip(Ship *newShip);

	void addCruiser(std::string name, Point position, int power,
			double captureRange);

	void addFreighter(string &name, const Point &position,
			const int &resistance, int container);

	void addBoatPatrol(string &name, Point position, const int &resistance);

	void addPort(Port *a);

	void addPort(std::string name, double x, double y, double Fuel = 10000,
			int containers = 0, int FPH = 0);

	void addView(View *newView);

	void Attatch(Ship &newShip, Port &newPort);

	void Dettatch(Ship &newShip, Port &newPort);

	int getShipByName(const std::string &name);

	Port* getPortByName(std::string name);

	void course(std::string shipName, double angle, double speed);

	void position(std::string shipName, double x, double y, double speed);

	void destination(std::string shipName, std::string portName, double speed);

	void load_at(std::string shipName, std::string portName);

	void unload_at(std::string shipName, std::string portName,
			double numberOfShipmentsToUnload);

	Port* findClosestPort(const Point &point);

	virtual ~Model() = default;

	/* Implementation of the function make_unique */
	template<typename T, typename ... Args>
	std::unique_ptr<T> make_unique(Args &&... args) {
		return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
	}

	void status();

};

#endif //UNTITLED2_MODEL_H
