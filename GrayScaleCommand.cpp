#include "GrayScaleCommand.h"

GrayScaleCommand::GrayScaleCommand(MyVector<Polymorphic_Ptr<PortableAnymap>>& images) : Command(images)
{
}

void GrayScaleCommand::execute()
{
	if (snapshot) {
		delete snapshot;
	}
	snapshot = new MyVector<Polymorphic_Ptr<PortableAnymap>>(images);
	for (size_t i = 0; i < images.getSize(); i++)
	{
		images[i]->grayscale();
	}
}

void GrayScaleCommand::execute(Polymorphic_Ptr<PortableAnymap>& image)
{
	image->grayscale();
}
void GrayScaleCommand::undo() {
	if (snapshot) {
		for (size_t i = 0; i < snapshot->getSize(); i++)
		{
			images[i] = (*snapshot)[i];

		}
	}
	delete snapshot;
	snapshot = nullptr;
}

Command* GrayScaleCommand::clone() const
{
	return new GrayScaleCommand(*this);
}