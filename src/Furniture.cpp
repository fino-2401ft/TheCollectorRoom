#include "../include/Furniture.h"
#include "../include/Geometry.h"
#include <GL/gl.h>
#include <algorithm>

Furniture::Furniture(FurnitureType t, const Vec3 &pos, const Vec3 &scl, const Vec3 &col)
    : Object3D(pos, scl, col, std::max({scl.x, scl.y, scl.z})), type(t) {}

void Furniture::draw()
{
    if (!visible)
        return;
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glScalef(scale.x, scale.y, scale.z);
    glColor3f(color.x, color.y, color.z);

    switch (type)
    {
    case FT_TABLE:
        // tabletop
        glPushMatrix();
        glScalef(1.0f, 0.15f, 1.0f);
        drawUnitCube();
        glPopMatrix();
        // legs
        for (int i = 0; i < 4; i++)
        {
            glPushMatrix();
            float lx = (i < 2) ? -0.4f : 0.4f;
            float lz = (i % 2 == 0) ? -0.4f : 0.4f;
            glTranslatef(lx, -0.5f, lz);
            glScalef(0.1f, 0.7f, 0.1f);
            drawUnitCube();
            glPopMatrix();
        }
        break;
    case FT_CHAIR:
        glPushMatrix();
        glScalef(0.8f, 0.15f, 0.8f);
        drawUnitCube();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0.0f, 0.35f, -0.32f);
        glScalef(0.8f, 0.7f, 0.15f);
        drawUnitCube();
        glPopMatrix();
        break;
    case FT_BED:
        glPushMatrix();
        glScalef(2.0f, 0.4f, 1.2f);
        drawUnitCube();
        glPopMatrix();
        break;
    case FT_CABINET:
        glPushMatrix();
        glScalef(1.0f, 2.0f, 0.8f);
        drawUnitCube();
        glPopMatrix();
        break;
    case FT_FRIDGE:
        glPushMatrix();
        glScalef(0.9f, 2.0f, 0.9f);
        drawUnitCube();
        glPopMatrix();
        break;
    case FT_TV:
        glPushMatrix();
        glScalef(1.2f, 0.7f, 0.1f);
        drawUnitCube();
        glPopMatrix();
        break;
    }

    glPopMatrix();
}
