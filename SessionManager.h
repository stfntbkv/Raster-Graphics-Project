#pragma once
#include "MyVector.hpp"
#include "PolymorphicPointer.hpp"
#include "PortableAnymap.h"
#include "MyQueue.hpp"
#include "MyStack.hpp"
#include "Command.h"
class SessionManager
{
	static int nextId;
	int id = 0;
	int remainingTransformationsCount = 0;
	MyQueue<Polymorphic_Ptr<Command>> commands;
	MyVector<MyString> remainingTransformations;
	MyStack<Polymorphic_Ptr<Command>, 64> history;
	
public:
	MyVector<Polymorphic_Ptr<PortableAnymap>> images;
	SessionManager();
	SessionManager(MyVector<Polymorphic_Ptr<PortableAnymap>>&& images);
	SessionManager(const MyVector<Polymorphic_Ptr<PortableAnymap>>& images);
	void add(PortableAnymap* image);
	void addCommand(Command* command);
	void addTransformation(MyString&& transformation);
	Polymorphic_Ptr<PortableAnymap>& operator[](size_t index);
	const Polymorphic_Ptr<PortableAnymap>& operator[](size_t index) const;
	void sessionInfo() const;
	int getSize() const;
	int getId() const;
	void save();
	void undo();
	void saveas(const MyString& fileName) const;
};

