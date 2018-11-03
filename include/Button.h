#pragma once
#include "Object.h"

class Button : public Object
{
    void DrawMe() final;
    ObjectType GetType() final { return ObjectType::Button; }
};