#pragma once
#include "Object.h"

class Button : public Object
{
public:
    void DrawMe() const;
    void DoNothing() const final;
};