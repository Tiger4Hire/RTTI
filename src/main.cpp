/**************************************************************
 * We have destroyed all knowledge of actual type (type-erasure)
 * of our objects, so we may now enjoy the benifit. An easy to write
 * loop.
 * ************************************************************/

#include "ObjectList.h"
#include "TextLabel.h"
#include "Button.h"

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

int main()
{
    auto my_bag_of_shit = MakeSomeObject();
    for (auto& thing : my_bag_of_shit)
    {
        if (thing->GetType() == ObjectType::TextLabel)
            thing->Translate();
        thing->DrawMe();
    }
}