#pragma once
#include "PortableAnymap.h"
class PortableGrayMap: public PortableAnymap {
    bool isBinary;
    unsigned short int maxValue; 
        MyVector<MyVector<unsigned short int>> image;
public:
    PortableGrayMap(const MyString& filename, size_t height, size_t width, MyVector<MyVector<unsigned short int>>&& image, bool isBinary, unsigned short int maxValue);
    PortableGrayMap(const MyString& filename, size_t height, size_t width, MyVector<MyVector<unsigned short int>>&& image, bool isBinary, unsigned short int maxValue,const MyVector<MyString>& comments);
    void print() const override;
    void save(const MyString& fileName) const override;
    PortableAnymap* clone() const override;
    void grayscale() override;
    void monochrome() override;
    void negative() override;
    void rotate(const MyString& direction) override;
};

