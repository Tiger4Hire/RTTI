#pragma once
#include "Object.h"
#include <string>

class TextLabel : public Object
{
    std::string text;
    void DrawMe() final;

public:
    ~TextLabel();
    TextLabel(std::string&& ref) : text(std::move(ref)) {}
};