#include "TextLabel.h"
#include <iostream>

void TextLabel::DrawMe() const
{
    std::cout << "I am a label containing \"" << text << "\"\n";
}

// Example translation, in this case for people with *really* bad ey sight
void TextLabel::Translate()
{
    for (char& c : text)
        c = std::toupper(c);
}