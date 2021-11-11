//
// Created by Admin on 6/18/2021.
//

#ifndef UNTITLED2_VIEW_H
#define UNTITLED2_VIEW_Hs
#include "Geometry.h"

#define MAX_MAP_SIZE 30
#define MIN_MAP_SIZE 7

#define DEFAULT_SIZE 25

#define DEFAULT_ORIGIN Point(0,0)

#define DEFAULT_ZOOM 1

class View {
    int _displaySize;
    int _scale;
    Point _origin;
public:
    View();

    View(int currentSize, const Point &origin,int scale);

    void size(int currentSize);

    void pan(const Point &origin);

    void show();

    void zoom(int zoom);

    int getDisplaySize() const;

    const Point &getOrigin() const;

    int getScale() const;

    void setScale(int scale);

    void setDisplaySize(int displaySize);

    void setOrigin(const Point &origin);

    void defaultSettings();


};
std::string isThereAnObjectAt(Point a);
#endif //UNTITLED2_VIEW_H
