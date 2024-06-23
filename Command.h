#pragma once
#include "MyString.h"
#include "PortableAnymap.h"
#include "PolymorphicPointer.hpp"

class Command{
protected:
    MyVector<Polymorphic_Ptr<PortableAnymap>>& images;
public:
    Command(MyVector<Polymorphic_Ptr<PortableAnymap>>& images) : images(images) {  }
    virtual void execute() = 0;
    virtual void execute(Polymorphic_Ptr<PortableAnymap>& image) = 0;
    virtual void undo() = 0;
    virtual Command* clone() const = 0;
    virtual ~Command() = default;
};