//
// Created by Stefan Tabakov on 18.06.24.
//

#include "PortableAnymapFactory.h"
void printBinaryRepresentation(const unsigned char* data, size_t dataSize) {
    for (size_t i = 0; i < dataSize; ++i) {
        unsigned char byte = static_cast<unsigned char>(data[i]);
        for (int bit = 7; bit >= 0; --bit) {
            std::cout << ((byte >> bit) & 1);
        }
        std::cout << ' ';
    }
    std::cout << std::endl;
}
PortableAnymap *PortableAnymapFactroy::createP4(const MyString& filename,std::ifstream& ifs, size_t height, size_t width) {
    size_t curPos = ifs.tellg();
    ifs.close();
    std::ifstream ifsBinary(filename.c_str(), std::ios::binary);
    ifsBinary.seekg(curPos);

    int rowBytes = (width + 7) / 8;
    int dataSize = rowBytes * height;
    char* arr = new char[dataSize];
    ifsBinary.read(arr,dataSize);

    MyVector<MyVector<bool>> image;
    int byteIndex = 0;
    for (size_t i = 0; i < height; i++)
    {
        MyVector<bool> curRow;
        unsigned char mask = 1;
        mask <<= 7;
        for (size_t j = 0; j < width; j++)
        {
            bool pixel = mask & arr[byteIndex];
            curRow.addItem(pixel);
            if (mask == 1) {
                mask <<= 7;
                byteIndex++;
            }
            else {
                mask >>= 1;
            }
        }
        byteIndex++;
        image.addItem(curRow);
    }
    delete[] arr;
    return new PortableBitmap(filename, height, width,std::move(image),true);


}
PortableAnymap* PortableAnymapFactroy::createP5(const MyString& filename, std::ifstream& ifs, size_t height, size_t width)
{
    unsigned short int maxValue;
    ifs >> maxValue;
    ifs.ignore();
    size_t curPos = ifs.tellg();
    ifs.close();
    std::ifstream ifsBinary(filename.c_str(), std::ios::binary);
    ifsBinary.seekg(curPos);

    if (maxValue <= 255) {
        unsigned char* data = new unsigned char[height * width];
        ifsBinary.read((char*)data, height * width);;
        int dataIndex = 0;
        MyVector<MyVector<unsigned short int>> image;
        for (size_t i = 0; i < height; i++)
        {
            MyVector<unsigned short int> curRow;
            for (size_t j = 0; j < width; j++)
            {
               
                curRow.addItem(data[dataIndex++]);
            }
            image.addItem(std::move(curRow));
        }
        return new PortableGrayMap(filename, height, width, std::move(image), true, maxValue);
    }
    else {
        unsigned short int* data = new unsigned short int[height * width];
        ifsBinary.read((char*)data, height * width);;
        int dataIndex = 0;
        MyVector<MyVector<unsigned short int>> image;
        for (size_t i = 0; i < height; i++)
        {
            MyVector<unsigned short int> curRow;
            for (size_t j = 0; j < width; j++)
            {
                curRow.addItem(data[dataIndex++]);
            }
            image.addItem(std::move(curRow));
        }
        return new PortableGrayMap(filename, height, width, std::move(image), true, maxValue);
    }
}
PortableAnymap* PortableAnymapFactroy::createP6(const MyString& filename, std::ifstream& ifs, size_t height, size_t width)
{
    unsigned short int maxValue;
    ifs >> maxValue;
    ifs.ignore();
    size_t curPos = ifs.tellg();
    ifs.close();
    std::ifstream ifsBinary(filename.c_str(), std::ios::binary);
    ifsBinary.seekg(curPos);
    int dataSize = height * width * 3;
    if (maxValue <= 255) {
        unsigned char* data = new unsigned char[dataSize];
        ifsBinary.read((char*)data,dataSize);
        int dataIndex = 0;
        MyVector<MyVector<Triple<unsigned short int>>> image;
        for (size_t i = 0; i < height; i++)
        {
            MyVector<Triple<unsigned short int>> curRow;
            for (size_t j = 0; j < width; j++)
            {
                unsigned short int r = (data[dataIndex++]);
                unsigned short int g = (data[dataIndex++]);
                unsigned short int b = (data[dataIndex++]);
              //  std::cout << "Triple values: " << r << " " << g << " " << b << std::endl;
                Triple<unsigned short int> curTriple(r, g, b);
                curRow.addItem(std::move(curTriple));
            }
            image.addItem(std::move(curRow));
        }
        return new PortablePixMap(filename, height, width, std::move(image), true, maxValue);
    }
    else {
        unsigned short int * data = new unsigned short int[dataSize];
        ifsBinary.read((char*)data, sizeof(unsigned short int)*dataSize);
        int dataIndex = 0;
        MyVector<MyVector<Triple<unsigned short int>>> image;
        for (size_t i = 0; i < height; i++)
        {
            MyVector<Triple<unsigned short int>> curRow;
            for (size_t j = 0; j < width; j++)
            {
                Triple<unsigned short int> curTriple(data[dataIndex++], data[dataIndex++], data[dataIndex++]);
                curRow.addItem(std::move(curTriple));
            }
            image.addItem(std::move(curRow));
        }
        return new PortablePixMap(filename, height, width, std::move(image), true, maxValue);
    }


}


PortableAnymap* PortableAnymapFactroy::createP1(const MyString& filename, std::ifstream& ifs, size_t height, size_t width)
{
    MyVector<MyVector<bool>> image;
    for (int i = 0; i < height; ++i) {
        MyVector<bool> curRow;
        for (int j = 0; j < width; ++j) {
            bool pixel;
            ifs >> pixel;
            curRow.addItem(pixel);
        }
        image.addItem(std::move(curRow));
    }
    return new PortableBitmap(filename, height, width, std::move(image),false);
}
PortableAnymap* PortableAnymapFactroy::createP2(const MyString& filename, std::ifstream& ifs, size_t height, size_t width)
{
    unsigned short int maxValue;
    ifs >> maxValue;
    ifs.ignore();
    MyVector<MyVector<unsigned short int>> image;
    for (int i = 0; i < height; ++i) {
        MyVector<unsigned short int> curRow;
        for (int j = 0; j < width; ++j) {
            unsigned short int pixel;
            ifs >> pixel;
            curRow.addItem(pixel);
        }
        image.addItem(std::move(curRow));
    }
    return new PortableGrayMap(filename, height, width, std::move(image), false, maxValue);

}
PortableAnymap* PortableAnymapFactroy::createP3(const MyString& filename, std::ifstream& ifs, size_t height, size_t width)
{
    unsigned short int maxValue;
    ifs >> maxValue;
    ifs.ignore();
    MyVector<MyVector<Triple<unsigned short int>>> image;
    for (size_t i = 0; i < height; i++)
    {
        MyVector<Triple<unsigned short int>> curRow;
        for (size_t j = 0; j < width; j++)
        {
            unsigned short int red;
            unsigned short int green;
            unsigned short int blue;
            ifs >> red;
            ifs >> green;
            ifs >> blue;
            Triple<unsigned short int> curTriple (red, green, blue);
            curRow.addItem(std::move(curTriple));
        }
        image.addItem(std::move(curRow));
    }
    return new PortablePixMap(filename, height, width, std::move(image), false, maxValue);
}


PortableAnymap *PortableAnymapFactroy::create(const MyString& filename) {
    std::ifstream ifs(filename.c_str());
    if (!ifs.is_open()) {
        throw std::exception("File couldn't be oppened!");
    }
    MyVector<MyString> comments;
    MyString str;
    ifs >> str;
    ifs.ignore();
    char curCom[64];
    while (true) {  
        ifs.getline(curCom,64);
        if (curCom[0] == '#') {
            comments.addItem(curCom);
        }
        else {
            break;
        }
    }
    size_t height, width;
    std::stringstream ss(curCom);
    ss >> width;
    ss >> height;

    for (size_t i = 0; i < comments.getSize(); i++)
    {
        std::cout << comments[i];
    }
    PortableAnymap* map = nullptr;
    if(strcmp(str.c_str(), "P1") == 0) {
        map = createP1(filename, ifs,height,width);
    }else if (strcmp(str.c_str(), "P2") == 0) {
        map = createP2(filename, ifs, height, width);
    }
    else if (strcmp(str.c_str(), "P3") == 0) {
        map = createP3(filename, ifs, height, width);
    }
    else if (strcmp(str.c_str(), "P4") == 0) {
        map = createP4(filename, ifs, height, width);
    }else if (strcmp(str.c_str(), "P5") == 0) {
        map = createP5(filename, ifs, height, width);
    }
    else if (strcmp(str.c_str(), "P6") == 0) {
        map = createP6(filename, ifs, height, width);
    }
    return map;
}
