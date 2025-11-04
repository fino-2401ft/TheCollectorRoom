#include "../include/Room.h"
#include "../include/Geometry.h"
#include <GL/gl.h>

Room::Room() {}
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
    objects.push_back(new Furniture(FT_TABLE, {1.0f, 0.6f, -2.0f}, {1.6f, 0.8f, 1.0f}, {0.5f, 0.3f, 0.2f}));
    objects.push_back(new Furniture(FT_CHAIR, {-1.0f, 0.0f, -2.0f}, {0.6f, 0.6f, 0.6f}, {0.5f, 0.3f, 0.2f}));
    objects.push_back(new Furniture(FT_CHAIR, {3.0f, 0.0f, -2.0f}, {0.6f, 0.6f, 0.6f}, {0.5f, 0.3f, 0.2f}));
    objects.push_back(new Furniture(FT_CHAIR, {1.0f, 0.0f, -3.2f}, {0.6f, 0.6f, 0.6f}, {0.5f, 0.3f, 0.2f}));
    objects.push_back(new Furniture(FT_CHAIR, {-2.0f, 0.0f, 5.0f}, {0.6f, 0.6f, 0.6f}, {0.5f, 0.3f, 0.2f}));
    objects.push_back(new Furniture(FT_TABLE, {7.0f, 0.6f, 6.0f}, {1.6f, 0.8f, 1.0f}, {0.5f, 0.3f, 0.2f}));
    objects.push_back(new Animal({-2.0f, 0.0f, -2.0f}));

    // items (keys)
    items.push_back(new Item({-6.8f, 0.0f, 5.0f}));  // bed
    items.push_back(new Item({6.5f, 0.0f, -7.0f}));  // fridge
    items.push_back(new Item({-6.5f, 0.0f, -7.5f})); // TV
    items.push_back(new Item({-2.0f, 0.0f, -1.5f})); // dog
    items.push_back(new Item({7.0f, 0.0f, 6.0f}));   // right table
}

void Room::draw()
{
    // floor
    glPushMatrix();
    glColor3f(0.85f, 0.8f, 0.75f);
    glBegin(GL_QUADS);
    glVertex3f(-10.0f, 0.0f, -10.0f);
    glVertex3f(10.0f, 0.0f, -10.0f);
    glVertex3f(10.0f, 0.0f, 10.0f);
    glVertex3f(-10.0f, 0.0f, 10.0f);
    glEnd();
    glPopMatrix();

    // back wall
    glPushMatrix();
    glColor3f(0.95f, 0.95f, 0.96f);
    glBegin(GL_QUADS);
    glVertex3f(-10.0f, 0.0f, -10.0f);
    glVertex3f(-10.0f, 6.0f, -10.0f);
    glVertex3f(10.0f, 6.0f, -10.0f);
    glVertex3f(10.0f, 0.0f, -10.0f);
    glEnd();
    glPopMatrix();

    // right wall (with window area - simple colored quad)
    glPushMatrix();
    glColor3f(0.92f, 0.92f, 0.94f);
    glBegin(GL_QUADS);
    glVertex3f(10.0f, 0.0f, -10.0f);
    glVertex3f(10.0f, 6.0f, -10.0f);
    glVertex3f(10.0f, 6.0f, 10.0f);
    glVertex3f(10.0f, 0.0f, 10.0f);
    glEnd();
    // window (darker blue)
    glColor3f(0.6f, 0.8f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(9.0f, 2.0f, -5.0f);
    glVertex3f(9.0f, 4.0f, -5.0f);
    glVertex3f(9.0f, 4.0f, -2.0f);
    glVertex3f(9.0f, 2.0f, -2.0f);
    glEnd();
    glPopMatrix();

    // other walls omitted for brevity—could add left/front etc.

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
