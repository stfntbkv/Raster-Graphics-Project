#pragma once
#include "MyVector.hpp"
#include "PolymorphicPointer.hpp"
#include "PortableAnymap.h"
class SessionManager
{
	static int id;
	int remaingTransformations;
	MyVector<Polymorphic_Ptr<PortableAnymap>> images;
public:
	void add(PortableAnymap* image);
	Polymorphic_Ptr<PortableAnymap>& operator[](size_t index);
	const Polymorphic_Ptr<PortableAnymap>& operator[](size_t index) const;
	void sessionInfo() const;
	void save() const;
	void saveas(const MyString* fileName) const;
};

