#include "SessionManager.h"

SessionManager::SessionManager()
{
}

SessionManager::SessionManager(MyVector<Polymorphic_Ptr<PortableAnymap>>&& images) : images(std::move(images))
{
    id = nextId++;
}
SessionManager::SessionManager(const MyVector<Polymorphic_Ptr<PortableAnymap>>& images) : images(images)
{
    id = nextId++;
}

void SessionManager::add(PortableAnymap* image)
{
    images.addItem(image);
}

void SessionManager::addCommand(Command* command)
{
    commands.push(command);
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

int SessionManager::getSize() const
{
    return images.getSize();
}

int SessionManager::getId() const
{
    return id;
}

void SessionManager::save() 
{
    while (!commands.isEmpty()) {
        Polymorphic_Ptr<Command> temp = commands.peek();
        temp->execute();
        history.push(std::move(temp));
        commands.pop();
    }
    for (size_t i = 0; i < images.getSize(); i++)
    {
        images[i]->save();
    }
}

void SessionManager::undo()
{
    if (!history.isEmpty()) {
        Polymorphic_Ptr<Command> temp = history.peek();
        temp->undo();

        history.pop();
    }
}
