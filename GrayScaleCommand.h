#pragma once
#include "Command.h"
class GrayScaleCommand : public Command
{
    MyVector<Polymorphic_Ptr<PortableAnymap>>* snapshot = nullptr;
public:
    GrayScaleCommand(MyVector<Polymorphic_Ptr<PortableAnymap>>& images);
    void execute() override;
    void execute(Polymorphic_Ptr<PortableAnymap>& image) override;
    void undo() override;
    Command* clone() const override;
};

