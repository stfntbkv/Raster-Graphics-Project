#include "NegativeCommand.h"

NegativeCommand::NegativeCommand(MyVector<Polymorphic_Ptr<PortableAnymap>>& images) : Command(images)
{

}

void NegativeCommand::execute()
{
	if (snapshot) {
		delete snapshot;
	}
	snapshot = new MyVector<Polymorphic_Ptr<PortableAnymap>>(images);
	for (size_t i = 0; i < images.getSize(); i++)
	{
		images[i]->negative();
	}
}

void NegativeCommand::execute(Polymorphic_Ptr<PortableAnymap>& image)
{
	image->negative();
}

void NegativeCommand::undo()
{
	if (snapshot) {
		for (size_t i = 0; i < snapshot->getSize(); i++)
		{
			images[i] = (*snapshot)[i];
		}
	}
	delete snapshot;
	snapshot = nullptr;
}

Command* NegativeCommand::clone() const
{
	return new NegativeCommand(*this);
}
