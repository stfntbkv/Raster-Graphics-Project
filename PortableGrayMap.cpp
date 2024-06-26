#include "PortableGrayMap.h"
#include <fstream>
#include <iomanip>
void PortableGrayMap::makeBitmapCollage(const PortableAnymap& other, const MyString& fileName, const MyString& direction) const
{
	throw std::logic_error("Invalid images types");
}
void PortableGrayMap::makeGraymapCollage(const PortableAnymap& other, const MyString& newFileName, const MyString& direction) const
{
	if (newFileName.substr(newFileName.getSize() - 4, 4) != ".pgm") {
		throw std::logic_error("Invalid file name for the new image");
	}
	const PortableGrayMap& otherImage = dynamic_cast<const PortableGrayMap&>(other);
	if (strcmp(direction.c_str(), "vertical") == 0) {

		int newHeight = height + other.getHeight();
		MyVector<MyVector<unsigned short int>> newImage;
		for (size_t i = 0; i < height; i++)
		{
			MyVector<unsigned short int> curRow;
			for (size_t j = 0; j < width; j++)
			{
				curRow.addItem(image[i][j]);
			}
			newImage.addItem(std::move(curRow));
		}
		for (size_t i = 0; i < other.getHeight(); i++)
		{
			MyVector<unsigned short int> curRow;
			for (size_t j = 0; j < width; j++)
			{
				curRow.addItem(otherImage.image[i][j]);
			}
			newImage.addItem(std::move(curRow));
		}
		PortableAnymap* curImage = new PortableGrayMap(newFileName, newHeight,width, std::move(newImage), isBinary, maxValue);
		curImage->save(newFileName);
	}
	else if (strcmp(direction.c_str(), "horizontal") == 0) {
		int newWidth = width + other.getWidth();
		MyVector<MyVector<unsigned short int >> newImage;
		for (size_t i = 0; i < height; i++)
		{
			MyVector<unsigned short int > curRow;
			for (size_t j = 0; j < width; j++)
			{
				curRow.addItem(image[i][j]);
			}
			for (size_t j = 0; j < other.getWidth(); j++)
			{
				curRow.addItem(otherImage.image[i][j]);
			}
			newImage.addItem(curRow);
		}
		PortableAnymap* curImage = new PortableGrayMap(newFileName, height, newWidth, std::move(newImage), isBinary,maxValue);
		curImage->save(newFileName);
	}
	else {
		throw std::logic_error("Invalid direction");
	}
}
void PortableGrayMap::makePixmapCollage(const PortableAnymap& other, const MyString& fileName, const MyString& direction) const
{
	throw std::logic_error("Invalid images types");
}
PortableGrayMap::PortableGrayMap(const MyString& filename, size_t height, size_t width, MyVector<MyVector<unsigned short int>>&& image, bool isBinary, unsigned short int maxValue) :
	PortableAnymap(filename,height,width),image(std::move(image)), isBinary(isBinary), maxValue(maxValue)
{
}
PortableGrayMap::PortableGrayMap(const MyString& filename, size_t height, size_t width, MyVector<MyVector<unsigned short int>>&& image, bool isBinary, unsigned short int maxValue, const MyVector<MyString>& comments)
	: PortableAnymap(filename, height, width,comments), image(std::move(image)), isBinary(isBinary), maxValue(maxValue)
{
}
static void printBinaryRepresentation(const char* data, size_t dataSize) {
	for (size_t i = 0; i < dataSize; ++i) {
		unsigned char byte = static_cast<unsigned char>(data[i]);
		for (int bit = 7; bit >= 0; --bit) {
			std::cout << ((byte >> bit) & 1);
		}
		std::cout << ' ';
	}
	std::cout << std::endl;
}
void PortableGrayMap::print() const
{
	unsigned short int maxWidth = (std::floor(std::log10(maxValue) + 1));
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			std::cout << std::setw(maxWidth) << image[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void PortableGrayMap::makeCollage(const PortableAnymap& other, const MyString& fileName, const MyString& direction) const
{
	other.makeGraymapCollage(*this,fileName,direction);
}

void PortableGrayMap::save(const MyString& fileName) const
{
	if (isBinary) {
		std::ofstream ofs(fileName.c_str());
		if (!ofs.is_open()) {
			throw std::logic_error("Couldn't open file");
		}
		ofs << "P5\n";
		for (size_t i = 0; i < comments.getSize(); i++)
		{
			ofs << comments[i] << std::endl;
		}
		ofs << width << " " << height << "\n";
		ofs << maxValue << '\n';

		int curPos = ofs.tellp();
		ofs.close();

		std::ofstream ofsBinary(fileName.c_str(), std::ios::binary | std::ios::in);
		if (!ofsBinary.is_open()) {
			throw std::logic_error("Couldn't open file");
		}
		ofsBinary.seekp(curPos);

		int pixelBytes = maxValue <= 255 ? 1 : 2;
		int dataSize =  width * height;
		
		if (pixelBytes == 2) {
			unsigned short int* data = new unsigned short int[dataSize];
			int index = 0;
			for (size_t i = 0; i < height; i++)
			{
				for (size_t j = 0; j < width; j++)
				{
					data[index++] = image[i][j];
				}

			}
			ofsBinary.write((const char*)data, sizeof(unsigned short int) * dataSize);
			delete[] data;
		}
		else {
			unsigned char* data = new unsigned char[dataSize];
			int index = 0;
			for (size_t i = 0; i < height; i++)
			{
				for (size_t j = 0; j < width; j++)
				{
					data[index++] = image[i][j];
				}

			}
			ofsBinary.write((const char*)data, dataSize);
			delete[] data;
		}
		
	}

	else {
		std::ofstream ofs(fileName.c_str());
		if (!ofs.is_open()) {
			throw std::logic_error("Couldn't open file");
		}
		ofs << "P2\n";
		for (size_t i = 0; i < comments.getSize(); i++)
		{
			ofs << comments[i] << std::endl;
		}
		ofs << width << " " << height << '\n';
		ofs << maxValue << '\n';
		for (size_t i = 0; i < height; i++)
		{
			for (size_t j = 0; j < width; j++)
			{ 
				ofs  << image[i][j];
				if (j != width - 1) {
					ofs << " ";
				}
			}
			ofs << '\n';
		}

	}
}


PortableAnymap* PortableGrayMap::clone() const
{
	return new PortableGrayMap(*this);
}

void PortableGrayMap::grayscale()
{

}

void PortableGrayMap::monochrome()
{
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			if (image[i][j] < maxValue / 2) {
				image[i][j] = 0;
			}
			else {
				image[i][j] = maxValue;
			}
		}
	}
}

void PortableGrayMap::negative()
{
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			image[i][j] = maxValue - image[i][j];
		}
	}
}

void PortableGrayMap::rotate(const MyString& direction)
{
		if (direction == "left") {
			MyVector<MyVector<unsigned short int>> newImage;

			size_t newWidth = height;
			size_t newHeight = width;

			for (size_t i = 0; i < width; i++) {
				MyVector<unsigned short int> curNewRow;
				for (size_t j = 0; j < height; j++) {
					curNewRow.addItem(image[j][width - 1 - i]);
				}
				newImage.addItem(std::move(curNewRow));
			}
			height = newHeight;
			width = newWidth;
			image = std::move(newImage);
		}
		else if (direction == "right") {
			MyVector<MyVector<unsigned short int>> newImage;

			size_t newWidth = height;
			size_t newHeight = width;

			for (size_t i = 0; i < width; i++) {
				MyVector<unsigned short int> curNewRow;
				for (size_t j = 0; j < height; j++) {
					curNewRow.addItem(image[height - j - 1][i]);
				}
				newImage.addItem(std::move(curNewRow));
			}
			height = newHeight;
			width = newWidth;
			image = std::move(newImage);
		}
}
