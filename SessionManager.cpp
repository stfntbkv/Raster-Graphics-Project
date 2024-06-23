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

void SessionManager::makeCollage(int firstIndex, int secondIndex, const MyString& direction, const MyString& fileName)
{
    std::ifstream ifs1(images[firstIndex]->getFileName().c_str());
    MyString firstImageType;
    ifs1 >> firstImageType;
    std::ifstream ifs2(images[secondIndex]->getFileName().c_str());
    MyString secondImageType;
    ifs2 >> secondImageType;
    if (firstImageType != secondImageType) {
        throw std::logic_error("The types of the two images should be the same");
    }
    else if ((images[firstIndex]->getHeight() != images[secondIndex]->getHeight()) ||
        (images[firstIndex]->getWidth() != images[secondIndex]->getWidth())) {
        throw std::logic_error("The images should have the same sizes");
    }
    if (strcmp(direction.c_str(), "vertical")) {
        if (firstImageType == "P1") {
            
        }
    }

}
