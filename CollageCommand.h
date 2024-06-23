#pragma once
#include "Command.h"
class CollageCommand : public Command
{
    int firstImageIndex;
    int secondImageIndex;
    MyString direction;
    MyString fileName;
    

public:
    CollageCommand(MyVector<Polymorphic_Ptr<PortableAnymap>>& images, int firstImageIndex, int secondImageIndex,const MyString& direction,const MyString& fileName);
    virtual void execute() = 0;
    virtual void execute(Polymorphic_Ptr<PortableAnymap>& image) = 0;
    virtual void undo() = 0;
    virtual Command* clone() const = 0;
};

