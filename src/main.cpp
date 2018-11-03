/**************************************************************
 * We have destroyed all knowledge of actual type (type-erasure)
 * of our objects, so we may now enjoy the benifit. An easy to write
 * loop.
 * ************************************************************/

#include "Button.h"
#include "ObjectList.h"
#include "Renderer.h"
#include "RenderPolicy.h"
#include "TextLabel.h"

/***************************************************************
 * Another benifit is that this could a "factory", but it's not
 ***************************************************************/

ObjectList MakeSomeObject()
{
    ObjectList retval;
    retval.push_back(std::make_unique<Button>());
    retval.push_back(std::make_unique<Button>());
    retval.push_back(std::make_unique<TextLabel>("Fred"));
    return retval;
}

RenderPolicy GetPolicy(ObjectType type)
{
    switch (type)
    {
        case ObjectType::TextLabel:
            return RenderPolicy::TranslateAndRender;
        default:
            return RenderPolicy::Render;
    }
}

int main()
{
    auto my_bag_of_shit = MakeSomeObject();
    Renderer renderer;
    for (auto& thing : my_bag_of_shit)
        renderer.RenderAndTranslateThing(*thing, GetPolicy(thing->GetType()));
}