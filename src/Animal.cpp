#include "../include/Animal.h"
#include "../include/Geometry.h"
#include <GL/gl.h>
#include <cmath>

Animal::Animal(const Vec3 &pos) : Object3D(pos, {1.0f, 0.6f, 0.6f}, {1.0f, 0.85f, 0.2f}, 0.8f), phase(0.0f) {}

void Animal::update(float dt)
{
    phase += dt;
}

void Animal::draw()
{
    if (!visible)
        return;
    glPushMatrix();
    float bob = 0.05f * sinf(phase * 2.0f);
    glTranslatef(position.x, position.y + 0.5f + bob, position.z);
    glColor3f(color.x, color.y, color.z);
    // body
    glPushMatrix();
    glScalef(1.0f, 0.6f, 0.6f);
    drawUnitCube();
    glPopMatrix();
    // head
    glPushMatrix();
    glTranslatef(0.6f, 0.15f, 0.0f);
    glScalef(0.4f, 0.4f, 0.4f);
    drawUnitCube();
    glPopMatrix();
    glPopMatrix();
}
