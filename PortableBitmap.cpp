#include "PortableBitmap.h"


PortableBitmap::PortableBitmap(const MyString& filename, size_t height, size_t width, MyVector<MyVector<bool>> &&image,bool isBinary)
	:PortableAnymap(filename, height,width),image(std::move(image)), isBinary(isBinary)
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


void PortableBitmap::print() const
{
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			std::cout << image[i][j] << " ";
		}
		std::cout <<std::endl;
	}
}

void PortableBitmap::save() const
{
	if (isBinary) {
		std::ofstream ofs(fileName.c_str());
		if (!ofs.is_open()) {
			throw std::exception("Couldn't open file");
		}
		ofs << "P4\n";
		ofs << width << " " << height << "\n";
		int curPos = ofs.tellp();
		ofs.close();

		std::ofstream ofsBinary(fileName.c_str(), std::ios::binary | std::ios::in | std::ios::out);
		if (!ofsBinary.is_open()) {
			throw std::exception("Couldn't open file");
		}
		ofsBinary.seekp(curPos);

		int rowBytes = (width + 7) / 8;
		int dataSize = rowBytes * height;

		char* data = new char[dataSize];
		for (size_t i = 0; i < dataSize; i++)
		{
			data[i] = 0;
		}
		int byteIndex = 0;
		for (size_t i = 0; i < height; i++)
		{
			for (size_t j = 0; j < width; j++)
			{
				if (j % 8 == 0 && j != 0) {
					byteIndex++;
				}
				int shiftSteps = j % 8;

				data[byteIndex] ^= (image[i][j]<<(7-shiftSteps));
			}
			byteIndex++;
		}
		ofsBinary.write((const char*)data, dataSize);
		delete[] data;
	}

	else {
		std::ofstream ofs(fileName.c_str() );
		if (!ofs.is_open()) {
			throw std::exception("Couldn't open file");
		}
		ofs << "P1\n";
		ofs << width << " " << height << '\n';
		for (size_t i = 0; i < height; i++)
		{
			for (size_t j = 0; j < width; j++)
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

PortableAnymap* PortableBitmap::clone() const
{
	return new PortableBitmap(*this);
}

void PortableBitmap::grayscale()
{

}

void PortableBitmap::monochrome()
{
}

void PortableBitmap::negative()
{
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			image[i][j] = !image[i][j];
		}
	}
}

void PortableBitmap::rotate(const MyString& direction)
{
	if (direction == "left") {
		MyVector<MyVector<bool>> newImage;

		size_t newWidth = height;
		size_t newHeight = width;

		for (size_t i = 0; i < width; i++) {
			MyVector<bool> curNewRow;
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
		MyVector<MyVector<bool>> newImage;

		size_t newWidth = height;
		size_t newHeight = width;

		for (size_t i = 0; i < width; i++) {
			MyVector<bool> curNewRow;
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

