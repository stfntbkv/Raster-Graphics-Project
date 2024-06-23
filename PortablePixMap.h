#pragma once
#include "PortableAnymap.h"
#include "Triple.hpp"
class PortablePixMap : public PortableAnymap
{
	MyVector<MyVector<Triple<short unsigned int>>> image;
	short unsigned int maxValue;
	bool isBinary;
protected:
	void makeBitmapCollage(const PortableAnymap& other, const MyString& fileName, const MyString& direction) const override;
	void makeGraymapCollage(const PortableAnymap& other, const MyString& fileName, const MyString& direction) const override;
	void makePixmapCollage(const PortableAnymap& other, const MyString& fileName, const MyString& direction) const override;
public:
	PortablePixMap(const MyString& filename, size_t height, size_t width, MyVector<MyVector<Triple<short unsigned int>>>&& image,
	bool isBinary, short unsigned int maxValue);
	PortablePixMap(const MyString& filename, size_t height, size_t width, MyVector<MyVector<Triple<short unsigned int>>>&& image,
	bool isBinary, short unsigned int maxValue,const MyVector<MyString>& comments);
	void print() const override;
	void makeCollage(const PortableAnymap& other, const MyString& fileName, const MyString& direction) const override;
	void save(const MyString& fileName) const override;
	PortableAnymap* clone() const override;


	void grayscale() override;
	void monochrome() override;
	void negative() override;
	void rotate(const MyString& direction) override;


};

