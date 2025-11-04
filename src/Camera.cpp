#include "../include/Camera.h"
#include <GL/gl.h>
#include <cmath>

static float deg2rad(float d) { return d * 3.14159265f / 180.0f; }

Camera::Camera() : pos(0.0f, 1.6f, 8.5f), yaw(180.0f), pitch(0.0f), speed(5.0f) {}

void Camera::applyView()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(-pitch, 1.0f, 0.0f, 0.0f);
    glRotatef(-yaw, 0.0f, 1.0f, 0.0f);
    glTranslatef(-pos.x, -pos.y, -pos.z);
}

void Camera::processKeyboard(int dir, float dt)
{
    float rad = deg2rad(yaw);
    float forwardX = -sinf(rad);
    float forwardZ = -cosf(rad);
    float rightX = -sinf(rad - 3.14159265f / 2.0f);
    float rightZ = -cosf(rad - 3.14159265f / 2.0f);
    float dist = speed * dt;
    if (dir == 0)
    {
        pos.x += forwardX * dist;
        pos.z += forwardZ * dist;
    }
    if (dir == 1)
    {
        pos.x -= forwardX * dist;
        pos.z -= forwardZ * dist;
    }
    if (dir == 2)
    {
        pos.x += rightX * dist;
        pos.z += rightZ * dist;
    }
    if (dir == 3)
    {
        pos.x -= rightX * dist;
        pos.z -= rightZ * dist;
    }
}

void Camera::processMouse(float dx, float dy)
{
    yaw += dx * 0.12f;
    pitch += dy * 0.12f;
    if (pitch > 89.9f)
        pitch = 89.9f;
    if (pitch < -89.9f)
        pitch = -89.9f;
}
