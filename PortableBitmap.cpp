#include "PortableBitmap.h"
#include "PortableAnymapFactory.h"

void PortableBitmap::makeBitmapCollage(const PortableAnymap& other, const MyString& newFileName, const MyString& direction) const
{
	if (newFileName.substr(newFileName.getSize() - 4, 4) != ".pgm") {
		throw std::logic_error("Invalid file name for the new image");
	}
	const PortableBitmap& otherImage = dynamic_cast<const PortableBitmap&>(other);
	if (strcmp(direction.c_str(), "vertical") ==0 ) {
		
		int newHeight = height + other.getHeight();
		MyVector<MyVector<bool>> newImage;
		for (size_t i = 0; i < height; i++)
		{
			MyVector<bool> curRow;
			for (size_t j = 0; j < width; j++)
			{
				curRow.addItem(image[i][j]);
			}
			newImage.addItem(std::move(curRow));
		}
		for (size_t i = 0; i < other.getHeight(); i++)
		{
			MyVector<bool> curRow;
			for (size_t j = 0; j < width; j++)
			{
				curRow.addItem(otherImage.image[i][j]);
			}
			newImage.addItem(std::move(curRow));
		}
		PortableAnymap* curImage = new PortableBitmap(newFileName, newHeight, width, std::move(newImage), isBinary);
		curImage->save(newFileName);
	}
	else if(strcmp(direction.c_str(), "horizontal") == 0) {
		int newWidth = width + other.getWidth();
		MyVector<MyVector<bool>> newImage;
		for (size_t i = 0; i < height; i++)
		{
			MyVector<bool> curRow;
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
		PortableBitmap* curImage = new PortableBitmap(newFileName, height, newWidth, std::move(newImage), isBinary);
		curImage->save(newFileName);
	}
	else {
		throw std::logic_error("Invalid direction");
	}

}

void PortableBitmap::makeGraymapCollage(const PortableAnymap& other, const MyString& fileName, const MyString& direction) const
{
	throw std::logic_error("The types of the images are not the same");
}

void PortableBitmap::makePixmapCollage(const PortableAnymap& other, const MyString& fileName, const MyString& direction) const
{
	throw std::logic_error("The types of the images are not the same");
}

void PortableBitmap::makeCollage(const PortableAnymap& other, const MyString& fileName, const MyString& direction) const
{
	other.makeBitmapCollage(*this,fileName,direction);
}

PortableBitmap::PortableBitmap(const MyString& filename, size_t height, size_t width, MyVector<MyVector<bool>> &&image,bool isBinary)
	:PortableAnymap(filename, height,width),image(std::move(image)), isBinary(isBinary)
{
}

PortableBitmap::PortableBitmap(const MyString& filename, size_t height, size_t width, MyVector<MyVector<bool>>&& image, bool isBinary, const MyVector<MyString>& comments)
	: PortableAnymap(filename, height, width,comments), image(std::move(image)), isBinary(isBinary)
{
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

void PortableBitmap::save(const MyString& fileName) const
{
	if (isBinary) {
		std::ofstream ofs(fileName.c_str());
		if (!ofs.is_open()) {
			throw std::logic_error("Couldn't open file");
		}
		ofs << "P4\n";
		for (size_t i = 0; i < comments.getSize(); i++)
		{
			ofs << comments[i] << std::endl;
		}
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
			throw std::logic_error("Couldn't open file");
		}
		ofs << "P1\n";
		for (size_t i = 0; i < comments.getSize(); i++)
		{
			ofs << comments[i] << std::endl;
		}
		
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

