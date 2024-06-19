#include "SessionManager.h"

void SessionManager::add(PortableAnymap* image)
{
    images.addItem(image);
}

Polymorphic_Ptr<PortableAnymap>& SessionManager::operator[](size_t index)
{
    return images[index];
}

const Polymorphic_Ptr<PortableAnymap>& SessionManager::operator[](size_t index) const
{
    return images[index];
}

void SessionManager::sessionInfo() const
{

}

void SessionManager::save() const
{
    for (size_t i = 0; i < images.getSize(); i++)
    {
        images[i]->save();
    }
}
