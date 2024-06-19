
#include "PortableAnymap.h"

PortableAnymap::PortableAnymap(const MyString& fileName) : fileName(fileName)
{
}

PortableAnymap::PortableAnymap(const MyString& fileName, size_t height, size_t width):
	fileName(fileName),height(height),width(width)
{

}
