#pragma once
#include "Command.h"
class RotateCommand : public Command
{
    MyString direction;
    MyVector<Polymorphic_Ptr<PortableAnymap>>* snapshot = nullptr;
public:
    RotateCommand(MyVector<Polymorphic_Ptr<PortableAnymap>>& images,const MyString& direction);
    void execute() override;
    void undo() override;
    Command* clone() const override;
};

