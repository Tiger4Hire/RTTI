#include "Renderer.h"

void Renderer::Render(const Button& thing)
{
    thing.DrawMe();
}

void Renderer::Render(TextLabel& thing)
{
    thing.Translate();
    thing.DrawMe();
}