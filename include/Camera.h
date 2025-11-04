#pragma once
#include "Object3D.h"

class Camera
{
public:
    Vec3 pos;
    float yaw;
    float pitch;
    float speed;
    Camera();
    void applyView();
    void processKeyboard(int dir, float dt);
    void processMouse(float dx, float dy);
};
