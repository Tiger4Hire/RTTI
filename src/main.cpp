/**************************************************************
 * We have destroyed all knowledge of actual type (type-erasure)
 * of our objects, so we may now enjoy the benifit. An easy to write
 * loop.
 * ************************************************************/

#include "Button.h"
#include "ObjectList.h"
#include "Renderer.h"
#include "TextLabel.h"

/***************************************************************
 * Another benifit is that this could a "factory", but it's not
 ***************************************************************/

ObjectList MakeSomeObject()
{
    ObjectList retval;
    retval.emplace_back(Button());
    retval.emplace_back(Button());
    retval.emplace_back(TextLabel("Fred"));
    return retval;
}

int main()
{
    auto my_list = MakeSomeObject();
    Renderer renderer;
    my_list.visit([&](auto val) { renderer.Render(val); });
}