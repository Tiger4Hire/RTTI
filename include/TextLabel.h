#pragma once
#include "Object.h"
#include <string>

class TextLabel : public Object
{
    std::string text;

public:
    TextLabel(std::string&& s) : text(std::move(s)) {}
    void DrawMe() const;
    void Translate();
};