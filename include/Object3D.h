// #pragma once

// struct Vec3
// {
//     float x, y, z;
//     Vec3(float a = 0, float b = 0, float c = 0) : x(a), y(b), z(c) {}
// };

// class Object3D
// {
// public:
//     Vec3 position;
//     Vec3 scale;
//     Vec3 color;
//     float radius;
//     bool visible;
//     Object3D(const Vec3 &pos, const Vec3 &scl, const Vec3 &col, float r = 1.0f)
//         : position(pos), scale(scl), color(col), radius(r), visible(true) {}
//     virtual ~Object3D() {}
//     virtual void draw() = 0;
//     virtual void update(float dt) {}
//     bool isNear(const Vec3 &p, float range) const
//     {
//         float dx = position.x - p.x;
//         float dy = position.y - p.y;
//         float dz = position.z - p.z;
//         float d2 = dx * dx + dy * dy + dz * dz;
//         float R = (range + radius);
//         return d2 <= R * R;
//     }
// };
#pragma once

struct Vec3
{
    float x, y, z;
    Vec3(float a = 0, float b = 0, float c = 0) : x(a), y(b), z(c) {}
};

class Object3D
{
public:
    Vec3 position;
    Vec3 scale;
    Vec3 color;
    float boundingRadius;
    bool visible;
    Object3D(const Vec3 &pos, const Vec3 &scl, const Vec3 &col, float r = 1.0f);
    virtual ~Object3D();
    virtual void draw() = 0;
    virtual void update(float dt) {}
    bool isNear(const Vec3 &p, float range) const;
};