#include "ObjectList.h"
#include <algorithm>
#include <gsl/gsl>
using namespace std;
template <class T>
void vector_erase(vector<T>& container, int idx)
{
    container.erase(begin(container) + idx);
}
void ObjectList::emplace_back(Button&& newButton)
{
    buttons.emplace_back(move(newButton));
    typeOrder.push_back(ObjectType::ButtonType);
}

void ObjectList::emplace_back(TextLabel&& newLabel)
{
    labels.emplace_back(std::move(newLabel));
    typeOrder.push_back(ObjectType::TextLabelType);
}
void ObjectList::erase(int idx)
{
    Expects(idx < gsl::narrow<int>(typeOrder.size()));
    ObjectType thisType = gsl::at(typeOrder, idx);
    int objIdx = count(begin(typeOrder), begin(typeOrder) + idx, thisType) + 1;
    switch (thisType)
    {
        case ButtonType:
            vector_erase(buttons, objIdx);
            break;
        case TextLabelType:
            vector_erase(labels, objIdx);
            break;
    }
    vector_erase(typeOrder, idx);
}
