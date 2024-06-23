#pragma once
#include "Command.h"
class NegativeCommand : public Command
{
    MyVector<Polymorphic_Ptr<PortableAnymap>>* snapshot = nullptr;
public:
    NegativeCommand(MyVector<Polymorphic_Ptr<PortableAnymap>>& images);
    void execute() override;
    void execute(Polymorphic_Ptr<PortableAnymap>& image) override;
    void undo() override;
    Command* clone() const override;
};

