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
    
    // Enable smooth shading for better appearance
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    
    glColor3f(color.x, color.y, color.z);

    switch (type)
    {
    case FT_TABLE:
        // tabletop (wooden, darker with rounded edges effect)
        glColor3f(0.65f, 0.45f, 0.28f);
        glPushMatrix();
        glScalef(1.0f, 0.1f, 1.0f);
        drawUnitCube();
        glPopMatrix();
        // Table edge (slightly darker)
        glColor3f(0.55f, 0.38f, 0.22f);
        glPushMatrix();
        glTranslatef(0.0f, -0.05f, 0.0f);
        glScalef(1.02f, 0.02f, 1.02f);
        drawUnitCube();
        glPopMatrix();
        // legs (darker wood, thicker)
        glColor3f(0.4f, 0.28f, 0.18f);
        for (int i = 0; i < 4; i++)
        {
            glPushMatrix();
            float lx = (i < 2) ? -0.42f : 0.42f;
            float lz = (i % 2 == 0) ? -0.42f : 0.42f;
            glTranslatef(lx, -0.48f, lz);
            glScalef(0.1f, 0.75f, 0.1f);
            drawUnitCube();
            glPopMatrix();
        }
        break;
    case FT_CHAIR:
        // Seat cushion (wooden with padding effect)
        glColor3f(0.62f, 0.42f, 0.26f);
        glPushMatrix();
        glScalef(0.85f, 0.1f, 0.85f);
        drawUnitCube();
        glPopMatrix();
        // Seat padding (lighter)
        glColor3f(0.68f, 0.48f, 0.32f);
        glPushMatrix();
        glTranslatef(0.0f, 0.06f, 0.0f);
        glScalef(0.82f, 0.04f, 0.82f);
        drawUnitCube();
        glPopMatrix();
        // Backrest (wooden frame)
        glColor3f(0.52f, 0.36f, 0.24f);
        glPushMatrix();
        glTranslatef(0.0f, 0.4f, -0.36f);
        glScalef(0.85f, 0.75f, 0.1f);
        drawUnitCube();
        glPopMatrix();
        // Backrest padding
        glColor3f(0.58f, 0.4f, 0.28f);
        glPushMatrix();
        glTranslatef(0.0f, 0.4f, -0.34f);
        glScalef(0.8f, 0.7f, 0.06f);
        drawUnitCube();
        glPopMatrix();
        // Backrest supports (vertical bars)
        for (int i = 0; i < 2; i++)
        {
            glColor3f(0.48f, 0.32f, 0.2f);
            glPushMatrix();
            glTranslatef((i == 0 ? -0.35f : 0.35f), 0.2f, -0.36f);
            glScalef(0.04f, 0.6f, 0.08f);
            drawUnitCube();
            glPopMatrix();
        }
        // Four legs (classic 4-legged chair)
        glColor3f(0.42f, 0.28f, 0.18f);
        for (int i = 0; i < 4; i++)
        {
            glPushMatrix();
            float lx = (i < 2) ? -0.38f : 0.38f;
            float lz = (i % 2 == 0) ? -0.38f : 0.38f;
            glTranslatef(lx, -0.45f, lz);
            glScalef(0.08f, 0.55f, 0.08f);
            drawUnitCube();
            glPopMatrix();
        }
        // Leg connectors (horizontal bars for stability)
        glColor3f(0.4f, 0.26f, 0.16f);
        // Front bar
        glPushMatrix();
        glTranslatef(0.0f, -0.2f, -0.38f);
        glScalef(0.76f, 0.06f, 0.06f);
        drawUnitCube();
        glPopMatrix();
        // Back bar
        glPushMatrix();
        glTranslatef(0.0f, -0.2f, 0.38f);
        glScalef(0.76f, 0.06f, 0.06f);
        drawUnitCube();
        glPopMatrix();
        // Side bars
        glPushMatrix();
        glTranslatef(-0.38f, -0.2f, 0.0f);
        glScalef(0.06f, 0.06f, 0.76f);
        drawUnitCube();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0.38f, -0.2f, 0.0f);
        glScalef(0.06f, 0.06f, 0.76f);
        drawUnitCube();
        glPopMatrix();
        break;
    case FT_BED:
        // Mattress (white/cream)
        glColor3f(0.95f, 0.95f, 0.9f);
        glPushMatrix();
        glScalef(2.0f, 0.35f, 1.2f);
        drawUnitCube();
        glPopMatrix();
        // Bed frame (wooden)
        glColor3f(0.5f, 0.35f, 0.22f);
        glPushMatrix();
        glTranslatef(0.0f, -0.2f, 0.0f);
        glScalef(2.1f, 0.15f, 1.3f);
        drawUnitCube();
        glPopMatrix();
        // Headboard
        glColor3f(0.55f, 0.38f, 0.24f);
        glPushMatrix();
        glTranslatef(0.0f, 0.5f, -0.55f);
        glScalef(2.0f, 0.8f, 0.1f);
        drawUnitCube();
        glPopMatrix();
        break;
    case FT_CABINET:
        // Main body (wooden)
        glColor3f(0.55f, 0.38f, 0.24f);
        glPushMatrix();
        glScalef(1.0f, 2.0f, 0.8f);
        drawUnitCube();
        glPopMatrix();
        // Door handles (metallic)
        glColor3f(0.7f, 0.7f, 0.75f);
        glPushMatrix();
        glTranslatef(0.45f, 1.0f, 0.41f);
        glScalef(0.08f, 0.15f, 0.05f);
        drawUnitCube();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0.45f, -0.5f, 0.41f);
        glScalef(0.08f, 0.15f, 0.05f);
        drawUnitCube();
        glPopMatrix();
        break;
    case FT_FRIDGE:
        // Main body (white)
        glColor3f(0.95f, 0.95f, 0.97f);
        glPushMatrix();
        glScalef(0.9f, 2.0f, 0.9f);
        drawUnitCube();
        glPopMatrix();
        // Door seam (dark line)
        glColor3f(0.3f, 0.3f, 0.3f);
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.46f);
        glScalef(0.02f, 2.0f, 0.02f);
        drawUnitCube();
        glPopMatrix();
        // Handle (metallic)
        glColor3f(0.6f, 0.6f, 0.65f);
        glPushMatrix();
        glTranslatef(0.0f, 0.5f, 0.48f);
        glScalef(0.3f, 0.08f, 0.05f);
        drawUnitCube();
        glPopMatrix();
        break;
    case FT_TV:
        // Screen (black)
        glColor3f(0.05f, 0.05f, 0.05f);
        glPushMatrix();
        glScalef(1.2f, 0.7f, 0.08f);
        drawUnitCube();
        glPopMatrix();
        // Screen border (silver)
        glColor3f(0.7f, 0.7f, 0.75f);
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.05f);
        glScalef(1.25f, 0.75f, 0.02f);
        drawUnitCube();
        glPopMatrix();
        // Screen glow (slightly blue when on)
        glColor3f(0.15f, 0.2f, 0.25f);
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.045f);
        glScalef(1.15f, 0.65f, 0.01f);
        drawUnitCube();
        glPopMatrix();
        // Stand
        glColor3f(0.4f, 0.4f, 0.45f);
        glPushMatrix();
        glTranslatef(0.0f, -0.45f, 0.0f);
        glScalef(0.4f, 0.15f, 0.3f);
        drawUnitCube();
        glPopMatrix();
        break;
    case FT_LOW_CABINET:
        // Main body (wooden, lower height)
        glColor3f(0.6f, 0.42f, 0.28f);
        glPushMatrix();
        glScalef(1.2f, 0.6f, 0.6f);
        drawUnitCube();
        glPopMatrix();
        // Top surface (darker wood)
        glColor3f(0.5f, 0.35f, 0.22f);
        glPushMatrix();
        glTranslatef(0.0f, 0.31f, 0.0f);
        glScalef(1.22f, 0.05f, 0.62f);
        drawUnitCube();
        glPopMatrix();
        // Drawer/door handles
        glColor3f(0.7f, 0.7f, 0.75f);
        for (int i = 0; i < 2; i++)
        {
            glPushMatrix();
            glTranslatef(0.0f, 0.1f - i * 0.25f, 0.31f);
            glScalef(0.15f, 0.08f, 0.05f);
            drawUnitCube();
            glPopMatrix();
        }
        break;
    case FT_LAMP:
        // Base (metallic)
        glColor3f(0.6f, 0.6f, 0.65f);
        glPushMatrix();
        glTranslatef(0.0f, -0.25f, 0.0f);
        glScalef(0.15f, 0.1f, 0.15f);
        drawUnitCube();
        glPopMatrix();
        // Pole (thin)
        glColor3f(0.5f, 0.5f, 0.55f);
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f);
        glScalef(0.05f, 0.4f, 0.05f);
        drawUnitCube();
        glPopMatrix();
        // Shade (white/cream)
        glColor3f(0.95f, 0.95f, 0.9f);
        glPushMatrix();
        glTranslatef(0.0f, 0.25f, 0.0f);
        glScalef(0.3f, 0.2f, 0.3f);
        drawUnitCube();
        glPopMatrix();
        // Top of shade (smaller)
        glColor3f(0.9f, 0.9f, 0.85f);
        glPushMatrix();
        glTranslatef(0.0f, 0.36f, 0.0f);
        glScalef(0.25f, 0.05f, 0.25f);
        drawUnitCube();
        glPopMatrix();
        break;
    }

    glPopMatrix();
}
