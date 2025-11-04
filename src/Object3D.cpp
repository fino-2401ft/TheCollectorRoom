#include "../include/Object3D.h"
#include <cmath>

Object3D::Object3D(const Vec3 &pos, const Vec3 &scl, const Vec3 &col, float r)
    : position(pos), scale(scl), color(col), boundingRadius(r) {}
Object3D::~Object3D() {}

bool Object3D::isNear(const Vec3 &p, float range) const
{
    float dx = position.x - p.x;
    float dy = position.y - p.y;
    float dz = position.z - p.z;
    float dist2 = dx * dx + dy * dy + dz * dz;
    float rr = (range + boundingRadius);
    return dist2 <= rr * rr;
}