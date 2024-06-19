#pragma once
#include "MyString.h"
#include "MyVector.hpp"
class PortableAnymap{
protected:
    MyString fileName;
    size_t height;
    size_t width;
    
public:
    PortableAnymap(const MyString& fileName);
    PortableAnymap(const MyString& fileName, size_t height,size_t width);
    virtual ~PortableAnymap() = default;
    virtual PortableAnymap* clone() const = 0;
    virtual void save() const = 0;
    virtual void print() const = 0 ;
    virtual void grayscale() = 0;
    virtual void monochrome() = 0;
    virtual void negative() = 0;
    virtual void rotate(const MyString& direction) = 0;
  //  virtual void undo() = 0;

};