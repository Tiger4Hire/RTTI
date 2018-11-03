#include "Button.h"
#include <iostream>

void Button::DoNothing() const {}

void Button::DrawMe() const
{
    std::cout << "I am a button!\n";
}