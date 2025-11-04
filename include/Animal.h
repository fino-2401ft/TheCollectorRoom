#pragma once
#include "Object3D.h"

class Animal : public Object3D
{
public:
    float phase;
    Animal(const Vec3 &pos);
    void draw() override;
    void update(float dt) override;
};
