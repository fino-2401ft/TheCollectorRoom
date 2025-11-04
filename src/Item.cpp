#include "../include/Item.h"
#include "../include/Geometry.h"
#include <GL/gl.h>

Item::Item(const Vec3 &pos) : Object3D(pos, {0.4f, 0.2f, 0.2f}, {1.0f, 0.85f, 0.0f}, 0.4f), collected(false) {}

void Item::draw()
{
    if (collected || !visible)
        return;
    glPushMatrix();
    glTranslatef(position.x, position.y + 0.2f, position.z);
    glColor3f(color.x, color.y, color.z);
    glScalef(scale.x, scale.y, scale.z);
    drawUnitCube();
    glPopMatrix();
}
