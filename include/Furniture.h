#pragma once
#include "Object3D.h"

enum FurnitureType
{
    FT_TABLE,
    FT_CHAIR,
    FT_BED,
    FT_CABINET,
    FT_FRIDGE,
    FT_TV
};

class Furniture : public Object3D
{
public:
    FurnitureType type;
    Furniture(FurnitureType t, const Vec3 &pos, const Vec3 &scl, const Vec3 &col);
    void draw() override;
};
