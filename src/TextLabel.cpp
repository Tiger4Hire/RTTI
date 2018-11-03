#include "TextLabel.h"
#include <iostream>

TextLabel::~TextLabel()
{
    std::cout << "Deleting TextLabel\n";
}

void TextLabel::DrawMe()
{
    std::cout << "I am a label containing \"" << text << "\"\n";
}