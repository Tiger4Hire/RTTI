#include "Renderer.h"

void Renderer::RenderThing(Object& thing)
{
    thing.DrawMe();
}

void Renderer::RenderAndTranslateThing(Object& thing)
{
    thing.Translate();
    thing.DrawMe();
}