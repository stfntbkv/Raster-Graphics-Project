#include "PortablePixMap.h"
#include <fstream>
#include <iomanip>
#include <cmath>
void PortablePixMap::makeBitmapCollage(const PortableAnymap& other, const MyString& fileName, const MyString& direction) const
{
	throw std::logic_error("Invalid file types");
}
void PortablePixMap::makeGraymapCollage(const PortableAnymap& other, const MyString& fileName, const MyString& direction) const
{
	throw std::logic_error("Invalid file types");
}
void PortablePixMap::makePixmapCollage(const PortableAnymap& other, const MyString& newFileName, const MyString& direction) const
{
	const PortablePixMap& otherImage = dynamic_cast<const PortablePixMap&>(other);
	if (strcmp(direction.c_str(), "vertical") == 0) {

		int newHeight = height + other.getHeight();
		MyVector<MyVector<Triple<unsigned short int>>> newImage;
		for (size_t i = 0; i < height; i++)
		{
			MyVector<Triple<unsigned short int>> curRow;
			for (size_t j = 0; j < width; j++)
			{
				curRow.addItem(image[i][j]);
			}
			newImage.addItem(std::move(curRow));
		}
		for (size_t i = 0; i < other.getHeight(); i++)
		{
			MyVector<Triple<unsigned short int>> curRow;
			for (size_t j = 0; j < width; j++)
			{
				curRow.addItem(otherImage.image[i][j]);
			}
			newImage.addItem(std::move(curRow));
		}
		PortableAnymap* curImage = new PortablePixMap(newFileName, newHeight, width, std::move(newImage), isBinary, maxValue);
		curImage->save(newFileName);
	}
	else if (strcmp(direction.c_str(), "horizontal") == 0) {
		int newWidth = width + other.getWidth();
		MyVector<MyVector<Triple<unsigned short int>>> newImage;
		for (size_t i = 0; i < height; i++)
		{
			MyVector<Triple<unsigned short int>> curRow;
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
		PortableAnymap* curImage = new PortablePixMap(newFileName, newWidth, height, std::move(newImage), isBinary, maxValue);
		curImage->save(newFileName);
	}
}
PortablePixMap::PortablePixMap(const MyString& filename, size_t height, size_t width, MyVector<MyVector<Triple<short unsigned int>>>&& image, bool isBinary, short unsigned int maxValue) :
	PortableAnymap(filename,height,width),image(std::move(image)),isBinary(isBinary),maxValue(maxValue)
{
}
PortablePixMap::PortablePixMap(const MyString& filename, size_t height, size_t width, MyVector<MyVector<Triple<short unsigned int>>>&& image, bool isBinary, short unsigned int maxValue, const MyVector<MyString>& comments) :
	PortableAnymap(filename, height, width,comments), image(std::move(image)), isBinary(isBinary), maxValue(maxValue)
{
}
void PortablePixMap::print() const
{
	unsigned short int maxWidth = (std::floor(std::log10(maxValue) + 1));
	for (size_t i = 0; i < comments.getSize(); i++)
	{
		std::cout << comments[i] << std::endl;
	}
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			std::cout << std::setw(maxWidth) << image[i][j].getFirst() << " "
				<< std::setw(maxWidth) << image[i][j].getSecond() << " "
				<< std::setw(maxWidth) << image[i][j].getThird() << "  ";
		}
		std::cout << std::endl;
	}
}
void PortablePixMap::makeCollage(const PortableAnymap& other, const MyString& fileName, const MyString& direction) const
{
}
static void printBinaryRepresentation(const unsigned char* data, size_t dataSize) {
	for (size_t i = 0; i < dataSize; ++i) {
		unsigned char byte = static_cast<unsigned char>(data[i]);
		for (int bit = 7; bit >= 0; --bit) {
			std::cout << ((byte >> bit) & 1);
		}
		std::cout << ' ';
	}
	std::cout << std::endl;
}
void PortablePixMap::save(const MyString& fileName) const
{
	if (isBinary) {
		std::ofstream ofs(fileName.c_str());
		if (!ofs.is_open()) {
			throw std::exception("Couldn't open file");
		}
		ofs << "P6\n";
		for (size_t i = 0; i < comments.getSize(); i++)
		{
			ofs << comments[i] << std::endl;
		}
		ofs << width << " " << height << "\n";
		ofs << maxValue << '\n';
		int curPos = ofs.tellp();
		ofs.close();

		std::ofstream ofsBinary(fileName.c_str(), std::ios::binary | std::ios::in | std::ios::out);
		if (!ofsBinary.is_open()) {
			throw std::exception("Couldn't open file");
		}
		ofsBinary.seekp(curPos);
		int dataSize = 3*(height * width);
		if (maxValue > 255) {
			unsigned short int* data = new unsigned short int[dataSize];
			int index = 0;
			for (size_t i = 0; i < height; i++)
			{
				for (size_t j = 0; j < width; j++)
				{
					data[index++] = image[i][j].getFirst();
					data[index++] = image[i][j].getSecond();
					data[index++] = image[i][j].getThird();
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
					data[index++] = (image[i][j].getFirst());
					data[index++] = (image[i][j].getSecond());
					data[index++] = (image[i][j].getThird());
				}
			}
			ofsBinary.write((const char*)data,dataSize);
			delete[] data;
		}

	}
	else {
		std::ofstream ofs(fileName.c_str());
		ofs << "P3\n";
		for (size_t i = 0; i < comments.getSize(); i++)
		{
			ofs << comments[i] << std::endl;
		}
		ofs << width << " " << height << '\n';
		ofs << maxValue << '\n';
		for (size_t i = 0; i < height; i++)
		{
			for (size_t j = 0;  j < width;  j++)
			{
				ofs << image[i][j];
				if (j != width - 1) {
					ofs << " ";
				}
			}
			ofs << '\n';
		}
	}
}

PortableAnymap* PortablePixMap::clone() const
{
	return new PortablePixMap(*this);

}

static unsigned short int getGrayScalePixelValue(unsigned short int red, unsigned short int green, unsigned short int blue) {
	return 0.299 * red + 0.587 * green + 0.114 * blue;
}
void PortablePixMap::grayscale()
{
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			unsigned short int curGrayScaleValue = getGrayScalePixelValue
				(image[i][j].getFirst(),
				image[i][j].getSecond(),
				image[i][j].getThird());

			image[i][j].setFirst(curGrayScaleValue);
			image[i][j].setSecond(curGrayScaleValue);
			image[i][j].setThird(curGrayScaleValue);
		}
	}
}

void PortablePixMap::monochrome()
{
	grayscale();
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			unsigned short int grayscaleValue = image[i][j].getFirst(); 
			if (grayscaleValue >= maxValue/2) {
				image[i][j].setFirst(maxValue); 
				image[i][j].setSecond(maxValue);
				image[i][j].setThird(maxValue);
			}
			else {
				image[i][j].setFirst(0);
				image[i][j].setSecond(0);
				image[i][j].setThird(0);     
			}
		}
	}

}

void PortablePixMap::rotate(const MyString& direction)
{

	if (direction == "left") {
		MyVector<MyVector<Triple<unsigned short int>>> newImage;

		size_t newWidth = height;
		size_t newHeight = width;

		for (size_t i = 0; i < width; i++) {
			MyVector<Triple<unsigned short int>> curNewRow;
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
		MyVector<MyVector<Triple<unsigned short int>>> newImage;

		size_t newWidth = height;
		size_t newHeight = width;

		for (size_t i = 0; i < width; i++) {
			MyVector<Triple<unsigned short int>> curNewRow;
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

void PortablePixMap::negative()
{
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			image[i][j].setFirst(maxValue - image[i][j].getFirst());
			image[i][j].setSecond(maxValue - image[i][j].getSecond());
			image[i][j].setThird(maxValue - image[i][j].getThird());
		}
	}
}
