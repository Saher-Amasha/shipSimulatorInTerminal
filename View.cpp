//
// Created by Admin on 6/18/2021.
//

#include <algorithm>
#include <map>
#include "Model.h"

View::View(int currentSize, const Point &origin, int scale) :
		_displaySize(currentSize), _scale(scale), _origin(origin) {
}

int View::getDisplaySize() const {
	return _displaySize;
}

void View::size(int currentSize) {
	if (currentSize <= MAX_MAP_SIZE && currentSize >= MIN_MAP_SIZE)
		_displaySize = currentSize;
}

const Point& View::getOrigin() const {
	return _origin;
}

void View::pan(const Point &origin) {
	_origin.x = origin.x;
	_origin.y = origin.y;
}

void View::zoom(int zoom) {
	_scale = zoom;
}

std::string isThereAnObjectAtInterval(Point a, int _scale) {

	for (auto &i : Model::get_Instance().getSimObjectVector()) {

		if (inProximity(a, i->getPosition(), _scale))
			return i->getName();

	}
	return "";

}

void View::show() {
	//print first line ;stats
	cout << "Display size: " << _displaySize << ", scale: " << _scale
			<< ", origin: ";
	std::map<string, int> sample_map;
	int interval = (3 * _scale);
	_origin.print();
	cout << endl;
	int Min_Y = _origin.y;
	int isThere_A_Negative_Y_Value = (Min_Y < 0) ? 1 : 0;
	int initialY = _origin.y + interval;
	int Max_y = initialY + (floor(_displaySize / 3) - 1) * interval;

	int numOfSpaces = max(log10(Max_y),
			log10(abs(Min_Y)) + isThere_A_Negative_Y_Value) + 1;
	int D = 0;
	for (int i = _displaySize + _origin.y - 1; i >= _origin.y; --i) {
		//print the y values
		if (D % 3 == 0) {
			cout << std::right << setw(numOfSpaces) << Max_y << " ";
			Max_y -= interval;
		} else {
			if (_origin.y < 0)
				cout << setw(2 * numOfSpaces);
			else
				cout << setw(2 * numOfSpaces + 1);
		}
		D++;
		//print each point
		for (int j = _origin.x; j < _displaySize + _origin.x; j++) {
			//find if a point is in _scale range of every point we are checking
			std::string Name = isThereAnObjectAtInterval(
					Point(ceil(abs(_origin.x) + j * _scale),ceil(abs(_origin.y) + i * _scale)), _scale);
			if (Name.empty())
				cout << ". ";
			else{
				    if (sample_map.find(Name) == sample_map.end())
				    {
					    sample_map.insert( { Name, 1 });
				    }
				    else if (sample_map.find(Name) != sample_map.end())
				    {
				        sample_map.find(Name)->second++;
				    }

                if(sample_map.find(Name)->second == 1)
                    cout << Name;
                else
                    cout << ". ";

			}
		}
		cout << endl;

	}
	cout << setw(numOfSpaces + log10(abs(_origin.y)) + 1) << std::right
			<< getOrigin().x;
	int initial = _origin.x + interval;
	for (int j = 0; j < _displaySize / 3; j++) {

		cout << std::right << setw(6) << initial;
		initial += interval;

	}
	cout << endl;

}

int View::getScale() const {
	return _scale;
}

void View::setScale(int scale) {
	_scale = scale;
}

void View::setDisplaySize(int displaySize) {
	_displaySize = displaySize;
}

void View::setOrigin(const Point &origin) {
	_origin = origin;
}

void View::defaultSettings() {
    this->size(DEFAULT_SIZE);
    this->setOrigin(DEFAULT_ORIGIN);
    this->zoom(DEFAULT_ZOOM);

}

View::View() {
    this->size(DEFAULT_SIZE);
    this->setOrigin(DEFAULT_ORIGIN);
    this->zoom(DEFAULT_ZOOM);

}

std::string isThereAnObjectAt(Point a) {
	for (auto &i : Model::get_Instance().getSimObjectVector()) {
		if (a.x == floor(i->getPosition().x)
				&& a.y == floor(i->getPosition().y))
			return i->getName();
	}
	return "";

}
