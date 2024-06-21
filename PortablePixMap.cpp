#include "PortablePixMap.h"
#include <fstream>
#include <iomanip>
#include <cmath>
PortablePixMap::PortablePixMap(const MyString& filename, size_t height, size_t width, MyVector<MyVector<Triple<short unsigned int>>>&& image, bool isBinary, short unsigned int maxValue) :
	PortableAnymap(filename,height,width),image(std::move(image)),isBinary(isBinary),maxValue(maxValue)
{
}
void PortablePixMap::print() const
{
	unsigned short int maxWidth = (std::floor(std::log10(maxValue) + 1));

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
void PortablePixMap::save() const
{
	if (isBinary) {
		std::ofstream ofs(fileName.c_str());
		if (!ofs.is_open()) {
			throw std::exception("Couldn't open file");
		}
		ofs << "P6\n";
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
					data[index++] = image[i][j].getFirst();
					data[index++] = image[i][j].getSecond();
					data[index++] = image[i][j].getThird();
				}
			}
			ofsBinary.write((const char*)data,dataSize);
			delete[] data;
		}

	}
	else {
		std::ofstream ofs(fileName.c_str());
		ofs << "P3\n";
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
