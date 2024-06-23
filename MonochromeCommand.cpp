#include "MonochromeCommand.h"

MonochromeCommand::MonochromeCommand(MyVector<Polymorphic_Ptr<PortableAnymap>>& images) : Command(images)
{
}

void MonochromeCommand::execute()
{
	if (snapshot) {
		delete snapshot;
	}
	snapshot = new MyVector<Polymorphic_Ptr<PortableAnymap>>(images);
	for (size_t i = 0; i < images.getSize(); i++)
	{
		images[i]->monochrome();
	}
}
void MonochromeCommand::execute(Polymorphic_Ptr<PortableAnymap>& image)
{
	image->monochrome();
}
void MonochromeCommand::undo() {
	if (snapshot) {
		for (size_t i = 0; i < snapshot->getSize(); i++)
		{
			images[i] = (*snapshot)[i];

		}
	}
	delete snapshot;
	snapshot = nullptr;
}

Command* MonochromeCommand::clone() const
{
	return new MonochromeCommand(*this);
}