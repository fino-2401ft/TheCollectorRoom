#pragma once
#include "Object3D.h"

class Item : public Object3D
{
public:
    bool collected;
    Item(const Vec3 &pos);
    void draw() override;
};
