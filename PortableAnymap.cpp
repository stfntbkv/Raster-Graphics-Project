
#include "PortableAnymap.h"

PortableAnymap::PortableAnymap(const MyString& fileName) : fileName(fileName)
{
}

PortableAnymap::PortableAnymap(const MyString& fileName, size_t height, size_t width):
	fileName(fileName),height(height),width(width)
{

}

PortableAnymap::PortableAnymap(const MyString& fileName, size_t height, size_t width, const MyVector<MyString>& comments) :
	fileName(fileName),height(height),width(width),comments(comments)
{
}

const MyString& PortableAnymap::getFileName() const
{
	return fileName;
}
