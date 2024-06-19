#pragma once
#include "PortableBitmap.h"
#include "PortableGrayMap.h"
#include "PortablePixMap.h"
#include "MyString.h"
#include <fstream>
#include "MyVector.hpp"



class PortableAnymapFactroy{
public:
    PortableAnymapFactroy() = default;
    static PortableAnymap* create(const MyString& filename);
private:
    static PortableAnymap* createP1(const MyString& filename,std::ifstream& ifs);
    static PortableAnymap* createP2(const MyString& filename,std::ifstream& ifs);
    static PortableAnymap* createP3(const MyString& filename,std::ifstream& ifs);
    static PortableAnymap* createP4(const MyString& filename,std::ifstream& ifs);
    static PortableAnymap* createP5(const MyString& filename,std::ifstream& ifs);
    static PortableAnymap* createP6(const MyString& filename,std::ifstream& ifs);
};