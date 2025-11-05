#pragma once
#include <vector>
#include "Object3D.h"
#include "Furniture.h"
#include "Animal.h"
#include "Item.h"

class Room
{
public:
    std::vector<Object3D *> objects;
    std::vector<Item *> items;
    bool doorOpen;
    Room();
    ~Room();
    void setupScene();
    void draw();
    Item *getNearbyItem(const Vec3 &pos, float range);
    bool isNearDoor(const Vec3 &pos, float range);
    void openDoor();
};
