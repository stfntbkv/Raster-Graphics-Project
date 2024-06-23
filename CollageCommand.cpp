#include "CollageCommand.h"

CollageCommand::CollageCommand(MyVector<Polymorphic_Ptr<PortableAnymap>>& images, int firstImageIndex, int secondImageIndex, const MyString& direction, const MyString& fileName) :
	Command(images),firstImageIndex(firstImageIndex),secondImageIndex(secondImageIndex),direction(direction),fileName(fileName)
{
	
}
#include <fstream>
void CollageCommand::execute()
{
	std::ifstream ifs1(images[firstImageIndex]->getFileName().c_str());
	MyString firstImageType;
	ifs1 >> firstImageType;
	std::ifstream ifs2(images[secondImageIndex]->getFileName().c_str());
	MyString secondImageType;
	ifs2 >> secondImageType;
	if (firstImageType != secondImageType) {
		throw std::logic_error("The types of the two images should be the same");
	}
	else if ((images[firstImageIndex]->getHeight() != images[secondImageIndex]->getHeight()) ||
		(images[firstImageIndex]->getWidth() != images[secondImageIndex]->getWidth())) {
		throw std::logic_error("The images should have the same sizes");
	}

	if (strcmp(direction.c_str(), "vertical")) {
		int newheight = images[firstImageIndex]->getHeight() + images[secondImageIndex]->getHeight();
		
		
	}

}
