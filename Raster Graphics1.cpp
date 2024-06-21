#include "PortableAnymapFactory.h"
#include "SessionManager.h"
#include "PolymorphicPointer.hpp"
#include "Command.h"
#include "MonochromeCommand.h"
#include "GrayScaleCommand.h"
#include <iostream>
#include <sstream>
int SessionManager::nextId = 1;
void run() {
	MyString command;
	std::cin >> command;
	MyVector<SessionManager> sessions;
	int activeSessionIndex = 0;
	while (true) {

		if (strcmp(command.c_str(), "load") == 0) {
			std::cin.ignore();
			char buff[128];
			std::cin.getline(buff, 128);
			std::stringstream ss(buff);
			char filename[128];
			MyVector<MyString> filenames;
			while (!ss.eof()) {
				ss.getline(filename, 128, ' ');
				filenames.addItem(filename);
			}
			MyVector<Polymorphic_Ptr<PortableAnymap>> curImages;
			for (size_t i = 0; i < filenames.getSize(); i++)
			{
				PortableAnymap* map = PortableAnymapFactroy::create(filenames[i].c_str());
				map->print();
				curImages.addItem(map);
			}
			SessionManager curSession(std::move(curImages));
			activeSessionIndex = curSession.getId();
			sessions.addItem(std::move(curSession));

		}
		else if(strcmp(command.c_str(), "grayscale") == 0) {
			Command* command = new GrayScaleCommand(sessions[activeSessionIndex-1].images);
			sessions[activeSessionIndex - 1].addCommand(command);

		}
		else if (strcmp(command.c_str(), "save") == 0) {
			sessions[activeSessionIndex - 1].save();
		}
		else if (strcmp(command.c_str(), "undo") == 0) {
			
			sessions[activeSessionIndex - 1].undo();
		}else if (strcmp(command.c_str(), "monochrome") == 0) {
			Command* command = new MonochromeCommand(sessions[activeSessionIndex - 1].images);
			sessions[activeSessionIndex - 1].addCommand(command);
		}
		else if (strcmp(command.c_str(), "exit") == 0) {
			for (size_t i = 0; i < sessions[activeSessionIndex-1].getSize(); i++)
			{
				sessions[activeSessionIndex - 1][i]->print();
			}
		}
		else {
			std::cout << "Invalid Command" << std::endl;
			
		}
		std::cin >> command;
	}




}
int main()
{
	run();
	//PortableAnymap* map = PortableAnymapFactroy::create("imagePPM.ppm");
	//map->print();


	//PortableAnymap* mapBinaryPpm = PortableAnymapFactroy::create("imagePPMbinary.ppm");
	//mapBinaryPpm->print();
	
	/*PortableAnymap* mapBinaryPgm = PortableAnymapFactroy::create("imagePGMbinary.pgm");
	mapBinaryPgm->print();*/
	/*std::cout << std::endl;
	PortableAnymap* mapBinaryPbm = PortableAnymapFactroy::create("imagePBMbinary.pbm");
	mapBinaryPbm->print();*/
	/*std::cout << std::endl;
	mapBinaryPbm->negative();
	mapBinaryPbm->print();
	std::cout << std::endl;
	mapBinaryPbm->rotate("left");
	mapBinaryPbm->print();
	std::cout << std::endl;*/
	

}


