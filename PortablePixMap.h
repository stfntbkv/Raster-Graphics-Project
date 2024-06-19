#pragma once
#include "PortableAnymap.h"
#include "Triple.hpp"
class PortablePixMap : public PortableAnymap
{
	MyVector<MyVector<Triple<short unsigned int>>> image;
	short unsigned int maxValue;
	bool isBinary;
public:
	PortablePixMap(const MyString& filename, size_t height, size_t width, MyVector<MyVector<Triple<short unsigned int>>>&& image,
		bool isBinary, short unsigned int maxValue);
	void print() const override;
	void save() const override;
	PortableAnymap* clone() const override;
	void grayscale() override;
	void monochrome() override;
	void negative() override;
	void rotate(const MyString& direction) override;


};

