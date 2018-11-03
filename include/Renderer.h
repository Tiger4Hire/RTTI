#pragma once
#include "Button.h"
#include "TextLabel.h"

class Renderer
{
public:
    void Render(const Button&);
    void Render(TextLabel&);
};
