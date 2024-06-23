#pragma once
#include <iostream>
#include <fstream>
#include "PortableAnymap.h"
#include "MyVector.hpp"
#include "PortableBitmap.h"

class PortableBitmap: public PortableAnymap{
    bool isBinary;
    MyVector<MyVector<bool>> image;
    void makeBitmapCollage(const PortableAnymap& other, const MyString& fileName, const MyString& direction) const override;
    void makeGraymapCollage(const PortableAnymap& other, const MyString& fileName, const MyString& direction) const override;
    void makePixmapCollage(const PortableAnymap& other, const MyString& fileName, const MyString& direction) const override;
public:
   
    PortableBitmap(const MyString& filename, size_t height,size_t width,MyVector<MyVector<bool>>&& image,bool isBinary);
    PortableBitmap(const MyString& filename, size_t height,size_t width,MyVector<MyVector<bool>>&& image,bool isBinary,const MyVector<MyString>& comments);
    void print() const override;
    PortableAnymap* clone() const override;

    void save(const MyString& fileName) const override;
    void grayscale() override;
    void monochrome() override;
    void negative() override;
    void rotate(const MyString& direction) override;
    void makeCollage(const PortableAnymap& other, const MyString& fileName, const MyString& direction) const override;
    
};