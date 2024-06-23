#include "SessionManager.h"
#include <fstream>


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
    remainingTransformationsCount++;
}

void SessionManager::addTransformation(MyString&& transformation)
{
    remainingTransformations.addItem(transformation);
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
    std::cout << std::endl;
    std::cout << "Session ID: " << id << std::endl;
    std::cout << "Loaded images in session: ";
    for (size_t i = 0; i < getSize(); i++)
    {
        std::cout << images[i]->getFileName() << std::endl;
    }
    std::cout << "Remaining transformations in session: ";
    for (size_t i = 0; i < remainingTransformationsCount; i++)
    {
        std::cout << remainingTransformations[i]<<std::endl;
    }
}

int SessionManager::getSize() const
{
    return images.getSize();
}

int SessionManager::getId() const
{
    return id;
}

const Polymorphic_Ptr<PortableAnymap> SessionManager::getImageByFile(const MyString& fileName) const
{
    for (size_t i = 0; i < getSize(); i++)
    {
        if (images[i]->getFileName() == fileName) {
            return images[i];
        }
    }
}

void SessionManager::save() 
{
    while (!commands.isEmpty()) {
        Polymorphic_Ptr<Command> temp = commands.peek();
        temp->execute();
        history.push(std::move(temp));
        commands.pop();   
    }
    remainingTransformations = MyVector<MyString>();
    for (size_t i = 0; i < images.getSize(); i++)
    {
        
        images[i]->save(images[i]->getFileName());
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

void SessionManager::saveas(const MyString& fileName) const
{
    if (!commands.isEmpty()) {
        MyQueue<Polymorphic_Ptr<Command>> commandsCopy = MyQueue<Polymorphic_Ptr<Command>>(commands);
        Polymorphic_Ptr<PortableAnymap> firstImage = Polymorphic_Ptr<PortableAnymap>(images[0]);
        while (!commandsCopy.isEmpty()) {
            Polymorphic_Ptr<Command> temp = commandsCopy.peek();
            temp->execute(firstImage);
            commandsCopy.pop();
        }
        firstImage->save(fileName);
    }
    else {
        images[0]->save(fileName);
    }
    
   
    
}


