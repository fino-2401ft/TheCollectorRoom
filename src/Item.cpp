#include "../include/Item.h"
#include "../include/Geometry.h"
#include <GL/gl.h>
#include <cmath>

Item::Item(const Vec3 &pos) : Object3D(pos, {0.4f, 0.2f, 0.2f}, {1.0f, 0.85f, 0.0f}, 0.4f), collected(false) {}

void Item::draw()
{
    if (collected || !visible)
        return;
    glPushMatrix();
    glTranslatef(position.x, position.y + 0.15f, position.z);
    
    // Key ring (golden circle)
    glColor3f(0.85f, 0.75f, 0.3f);
    glPushMatrix();
    glTranslatef(0.0f, 0.1f, 0.0f);
    glScalef(0.08f, 0.08f, 0.08f);
    // Draw a simple ring using rotated cube
    for (int i = 0; i < 8; i++)
    {
        glPushMatrix();
        float angle = i * 3.14159f / 4.0f;
        glTranslatef(cosf(angle) * 0.5f, 0.0f, sinf(angle) * 0.5f);
        glScalef(0.15f, 0.2f, 0.15f);
        drawUnitCube();
        glPopMatrix();
    }
    glPopMatrix();
    
    // Key body (golden)
    glColor3f(1.0f, 0.85f, 0.2f);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glScalef(0.15f, 0.05f, 0.3f);
    drawUnitCube();
    glPopMatrix();
    
    // Key head (bit part)
    glColor3f(0.9f, 0.75f, 0.15f);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.18f);
    glScalef(0.12f, 0.04f, 0.08f);
    drawUnitCube();
    glPopMatrix();
    
    glPopMatrix();
}
