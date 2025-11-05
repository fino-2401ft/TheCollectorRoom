#include "../include/Room.h"
#include "../include/Geometry.h"
#include <GL/gl.h>

Room::Room() : doorOpen(false) {}
Room::~Room()
{
    for (auto p : objects)
        delete p;
    for (auto it : items)
        delete it;
}

void Room::setupScene()
{
    // furniture (positions follow your top-view layout)
    objects.push_back(new Furniture(FT_TV, {-7.0f, 1.8f, -8.0f}, {1.5f, 0.8f, 0.1f}, {0.05f, 0.05f, 0.07f}));
    objects.push_back(new Furniture(FT_FRIDGE, {7.0f, 1.0f, -8.0f}, {1.0f, 2.0f, 1.0f}, {0.85f, 0.88f, 0.9f}));
    objects.push_back(new Furniture(FT_CABINET, {-9.0f, 1.0f, -7.0f}, {1.0f, 2.0f, 0.8f}, {0.45f, 0.35f, 0.25f}));
    objects.push_back(new Furniture(FT_CABINET, {8.0f, 1.0f, 2.0f}, {1.0f, 2.0f, 0.8f}, {0.45f, 0.35f, 0.25f}));
    objects.push_back(new Furniture(FT_BED, {-6.0f, 0.4f, 6.0f}, {3.0f, 0.8f, 1.6f}, {0.7f, 0.5f, 0.3f}));
    objects.push_back(new Furniture(FT_TABLE, {1.0f, 0.6f, -2.0f}, {2.2f, 0.9f, 1.4f}, {0.5f, 0.3f, 0.2f}));
    objects.push_back(new Furniture(FT_CHAIR, {-0.5f, 0.0f, -2.0f}, {0.9f, 0.9f, 0.9f}, {0.5f, 0.3f, 0.2f}));
    objects.push_back(new Furniture(FT_CHAIR, {2.5f, 0.0f, -2.0f}, {0.9f, 0.9f, 0.9f}, {0.5f, 0.3f, 0.2f}));
    objects.push_back(new Furniture(FT_CHAIR, {1.0f, 0.0f, -3.5f}, {0.9f, 0.9f, 0.9f}, {0.5f, 0.3f, 0.2f}));
    objects.push_back(new Furniture(FT_CHAIR, {0.0f, 0.0f, -1.0f}, {0.9f, 0.9f, 0.9f}, {0.5f, 0.3f, 0.2f})); // Moved from near bed
    objects.push_back(new Furniture(FT_TABLE, {7.0f, 0.6f, 6.0f}, {2.2f, 0.9f, 1.4f}, {0.5f, 0.3f, 0.2f}));
    objects.push_back(new Animal({-2.0f, 0.0f, -2.0f}));
    // Low cabinet with lamp on top
    objects.push_back(new Furniture(FT_LOW_CABINET, {-3.0f, 0.3f, 4.0f}, {1.2f, 0.6f, 0.6f}, {0.6f, 0.42f, 0.28f}));
    objects.push_back(new Furniture(FT_LAMP, {-3.0f, 0.9f, 4.0f}, {0.3f, 0.5f, 0.3f}, {0.95f, 0.95f, 0.9f}));

    // items (keys)
    items.push_back(new Item({-6.8f, 0.0f, 5.0f}));  // bed
    items.push_back(new Item({6.5f, 0.0f, -7.0f}));  // fridge
    items.push_back(new Item({-6.5f, 0.0f, -7.5f})); // TV
    items.push_back(new Item({-2.0f, 0.0f, -1.5f})); // dog
    items.push_back(new Item({7.0f, 0.0f, 6.0f}));   // right table
}

void Room::draw()
{
    // floor (white with subtle pattern)
    glPushMatrix();
    glShadeModel(GL_SMOOTH);
    glBegin(GL_QUADS);
    glColor3f(0.96f, 0.96f, 0.96f);
    glVertex3f(-10.0f, 0.0f, -10.0f);
    glColor3f(0.98f, 0.98f, 0.98f);
    glVertex3f(10.0f, 0.0f, -10.0f);
    glColor3f(0.98f, 0.98f, 0.98f);
    glVertex3f(10.0f, 0.0f, 10.0f);
    glColor3f(0.96f, 0.96f, 0.96f);
    glVertex3f(-10.0f, 0.0f, 10.0f);
    glEnd();
    glPopMatrix();

    // back wall (white with subtle shading)
    glPushMatrix();
    glShadeModel(GL_SMOOTH);
    glBegin(GL_QUADS);
    glColor3f(0.97f, 0.97f, 0.97f);
    glVertex3f(-10.0f, 0.0f, -10.0f);
    glColor3f(0.99f, 0.99f, 0.99f);
    glVertex3f(-10.0f, 6.0f, -10.0f);
    glColor3f(0.99f, 0.99f, 0.99f);
    glVertex3f(10.0f, 6.0f, -10.0f);
    glColor3f(0.97f, 0.97f, 0.97f);
    glVertex3f(10.0f, 0.0f, -10.0f);
    glEnd();
    glPopMatrix();

    // right wall (white with window area)
    glPushMatrix();
    glShadeModel(GL_SMOOTH);
    glBegin(GL_QUADS);
    glColor3f(0.97f, 0.97f, 0.97f);
    glVertex3f(10.0f, 0.0f, -10.0f);
    glColor3f(0.99f, 0.99f, 0.99f);
    glVertex3f(10.0f, 6.0f, -10.0f);
    glColor3f(0.99f, 0.99f, 0.99f);
    glVertex3f(10.0f, 6.0f, 10.0f);
    glColor3f(0.97f, 0.97f, 0.97f);
    glVertex3f(10.0f, 0.0f, 10.0f);
    glEnd();
    // Window frame (white border)
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex3f(9.95f, 1.95f, -5.05f);
    glVertex3f(9.95f, 4.05f, -5.05f);
    glVertex3f(9.95f, 4.05f, -1.95f);
    glVertex3f(9.95f, 1.95f, -1.95f);
    glEnd();
    // Window glass (bright blue with gradient)
    glShadeModel(GL_SMOOTH);
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.75f, 0.95f);
    glVertex3f(9.0f, 2.0f, -5.0f);
    glColor3f(0.7f, 0.85f, 1.0f);
    glVertex3f(9.0f, 4.0f, -5.0f);
    glColor3f(0.7f, 0.85f, 1.0f);
    glVertex3f(9.0f, 4.0f, -2.0f);
    glColor3f(0.5f, 0.75f, 0.95f);
    glVertex3f(9.0f, 2.0f, -2.0f);
    glEnd();
    glPopMatrix();

    // left wall (white with subtle shading)
    glPushMatrix();
    glShadeModel(GL_SMOOTH);
    glBegin(GL_QUADS);
    glColor3f(0.97f, 0.97f, 0.97f);
    glVertex3f(-10.0f, 0.0f, -10.0f);
    glColor3f(0.99f, 0.99f, 0.99f);
    glVertex3f(-10.0f, 6.0f, -10.0f);
    glColor3f(0.99f, 0.99f, 0.99f);
    glVertex3f(-10.0f, 6.0f, 10.0f);
    glColor3f(0.97f, 0.97f, 0.97f);
    glVertex3f(-10.0f, 0.0f, 10.0f);
    glEnd();
    glPopMatrix();

    // front wall with door (white with subtle shading)
    glPushMatrix();
    glShadeModel(GL_SMOOTH);
    // Left side of door
    glBegin(GL_QUADS);
    glColor3f(0.97f, 0.97f, 0.97f);
    glVertex3f(-10.0f, 0.0f, 10.0f);
    glColor3f(0.99f, 0.99f, 0.99f);
    glVertex3f(-10.0f, 6.0f, 10.0f);
    glColor3f(0.99f, 0.99f, 0.99f);
    glVertex3f(-2.0f, 6.0f, 10.0f);
    glColor3f(0.97f, 0.97f, 0.97f);
    glVertex3f(-2.0f, 0.0f, 10.0f);
    glEnd();
    // Right side of door
    glBegin(GL_QUADS);
    glColor3f(0.97f, 0.97f, 0.97f);
    glVertex3f(2.0f, 0.0f, 10.0f);
    glColor3f(0.99f, 0.99f, 0.99f);
    glVertex3f(2.0f, 6.0f, 10.0f);
    glColor3f(0.99f, 0.99f, 0.99f);
    glVertex3f(10.0f, 6.0f, 10.0f);
    glColor3f(0.97f, 0.97f, 0.97f);
    glVertex3f(10.0f, 0.0f, 10.0f);
    glEnd();
    // Top of door
    glBegin(GL_QUADS);
    glColor3f(0.99f, 0.99f, 0.99f);
    glVertex3f(-2.0f, 4.0f, 10.0f);
    glColor3f(0.99f, 0.99f, 0.99f);
    glVertex3f(-2.0f, 6.0f, 10.0f);
    glColor3f(0.99f, 0.99f, 0.99f);
    glVertex3f(2.0f, 6.0f, 10.0f);
    glColor3f(0.99f, 0.99f, 0.99f);
    glVertex3f(2.0f, 4.0f, 10.0f);
    glEnd();
    // Door (brown) - rotated if open
    glColor3f(0.4f, 0.25f, 0.15f);
    if (doorOpen)
    {
        // Draw door rotated 90 degrees (opened)
        glPushMatrix();
        glTranslatef(2.0f, 0.0f, 10.0f);
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex3f(-4.0f, 0.0f, 0.0f);
        glVertex3f(-4.0f, 4.0f, 0.0f);
        glVertex3f(0.0f, 4.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glEnd();
        glPopMatrix();
    }
    else
    {
        glBegin(GL_QUADS);
        glVertex3f(-2.0f, 0.0f, 10.0f);
        glVertex3f(-2.0f, 4.0f, 10.0f);
        glVertex3f(2.0f, 4.0f, 10.0f);
        glVertex3f(2.0f, 0.0f, 10.0f);
        glEnd();
    }
    glPopMatrix();

    // ceiling (white with subtle shading)
    glPushMatrix();
    glShadeModel(GL_SMOOTH);
    glBegin(GL_QUADS);
    glColor3f(0.98f, 0.98f, 0.98f);
    glVertex3f(-10.0f, 6.0f, -10.0f);
    glColor3f(0.99f, 0.99f, 0.99f);
    glVertex3f(-10.0f, 6.0f, 10.0f);
    glColor3f(0.99f, 0.99f, 0.99f);
    glVertex3f(10.0f, 6.0f, 10.0f);
    glColor3f(0.98f, 0.98f, 0.98f);
    glVertex3f(10.0f, 6.0f, -10.0f);
    glEnd();
    glPopMatrix();

    // draw objects & items
    for (auto o : objects)
        o->draw();
    for (auto it : items)
        it->draw();
}

Item *Room::getNearbyItem(const Vec3 &pos, float range)
{
    for (auto it : items)
        if (!it->collected && it->isNear(pos, range))
            return it;
    return nullptr;
}

bool Room::isNearDoor(const Vec3 &pos, float range)
{
    // Door is at z=10, x from -2 to 2
    float dx = pos.x - 0.0f;
    float dz = pos.z - 10.0f;
    return (dx * dx + dz * dz) < range * range;
}

void Room::openDoor()
{
    doorOpen = true;
}
