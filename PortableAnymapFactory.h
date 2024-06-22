#pragma once
#include "PortableBitmap.h"
#include "PortableGrayMap.h"
#include "PortablePixMap.h"
#include "MyString.h"
#include <fstream>
#include "MyVector.hpp"
#include <iostream>
#include <sstream>

class PortableAnymapFactroy{
public:
    PortableAnymapFactroy() = default;
    static PortableAnymap* create(const MyString& filename);
private:
    static PortableAnymap* createP1(const MyString& filename,std::ifstream& ifs, size_t height,size_t width, const MyVector<MyString>& comments);
    static PortableAnymap* createP2(const MyString& filename,std::ifstream& ifs, size_t height, size_t width, const MyVector<MyString>& comments);
    static PortableAnymap* createP3(const MyString& filename,std::ifstream& ifs, size_t height, size_t width, const MyVector<MyString>& comments);
    static PortableAnymap* createP4(const MyString& filename,std::ifstream& ifs, size_t height, size_t width, const MyVector<MyString>& comments);
    static PortableAnymap* createP5(const MyString& filename,std::ifstream& ifs, size_t height, size_t width, const MyVector<MyString>& comments);
    static PortableAnymap* createP6(const MyString& filename,std::ifstream& ifs, size_t height, size_t width, const MyVector<MyString>& comments);
};