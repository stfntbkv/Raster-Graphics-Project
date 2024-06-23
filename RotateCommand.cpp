#include "RotateCommand.h"

RotateCommand::RotateCommand(MyVector<Polymorphic_Ptr<PortableAnymap>>& images, const MyString& direction) :
	Command(images),direction(direction)
{

}

void RotateCommand::execute()
{
	if (snapshot) {
		delete snapshot;
	}
	snapshot = new MyVector<Polymorphic_Ptr<PortableAnymap>>(images);
	for (size_t i = 0; i < images.getSize(); i++)
	{
		images[i]->rotate(direction);
	}
}

void RotateCommand::undo()
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

void RotateCommand::execute(Polymorphic_Ptr<PortableAnymap>& image)
{
	image->rotate(direction);
}

Command* RotateCommand::clone() const
{
	return new RotateCommand(*this);
}
