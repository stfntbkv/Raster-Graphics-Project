#include "Engine.h"

int SessionManager::nextId = 1;
 void Engine::run()
{
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
			std::cout << "Session with ID: " << activeSessionIndex << " started" << std::endl;
			sessions.addItem(std::move(curSession));

		}
		else if (strcmp(command.c_str(), "grayscale") == 0) {
			Command* command = new GrayScaleCommand(sessions[activeSessionIndex - 1].images);
			sessions[activeSessionIndex - 1].addCommand(command);
			sessions[activeSessionIndex - 1].addTransformation("grayscale");

		}
		else if (strcmp(command.c_str(), "negative") == 0) {
			Command* command = new NegativeCommand(sessions[activeSessionIndex - 1].images);
			sessions[activeSessionIndex - 1].addCommand(command);
			sessions[activeSessionIndex - 1].addTransformation("negative");

		}
		else if (strcmp(command.c_str(), "save") == 0) {
			sessions[activeSessionIndex - 1].save();
		}
		else if (strcmp(command.c_str(), "undo") == 0) {
			sessions[activeSessionIndex - 1].undo();
		}
		else if (strcmp(command.c_str(), "monochrome") == 0) {
			Command* command = new MonochromeCommand(sessions[activeSessionIndex - 1].images);
			sessions[activeSessionIndex - 1].addCommand(command);
			sessions[activeSessionIndex - 1].addTransformation("monochrome");
		}
		else if (strcmp(command.c_str(), "rotate") == 0) {
			std::cin.ignore();
			char buff[128];
			std::cin.getline(buff, 128);
			if (strcmp(buff, "right") == 0) {
				Command* command = new RotateCommand(sessions[activeSessionIndex - 1].images, "right");
				sessions[activeSessionIndex - 1].addCommand(command);
				sessions[activeSessionIndex - 1].addTransformation("rotate right");
			}
			else if (strcmp(buff, "left") == 0) {
				Command* command = new RotateCommand(sessions[activeSessionIndex - 1].images, "left");
				sessions[activeSessionIndex - 1].addCommand(command);
				sessions[activeSessionIndex - 1].addTransformation("rotate left");
			}
			else {
				std::cout << "Invalid direction" << std::endl;
			}
		}
		else if (strcmp(command.c_str(), "print") == 0) {
			for (size_t i = 0; i < sessions[activeSessionIndex - 1].getSize(); i++)
			{
				sessions[activeSessionIndex - 1][i]->print();
			}
		}
		else if (strcmp(command.c_str(), "add") == 0) {
			std::cin.ignore();
			MyString str;
			std::cin >> str;
			PortableAnymap* map = PortableAnymapFactroy::create(str.c_str());
			sessions[activeSessionIndex - 1].add(map);

		}
		else if (strcmp(command.c_str(), "session") == 0) {
			std::cin.ignore();
			MyString str;
			std::cin >> str;
			if (strcmp(str.c_str(), "info") == 0) {
				sessions[activeSessionIndex - 1].sessionInfo();
			}
		}
		else if (strcmp(command.c_str(), "exit") == 0) {
			break;
		}
		else if (strcmp(command.c_str(), "switch") == 0) {
			int sesIndex;
			std::cin >> sesIndex;
			if (sesIndex > sessions.getSize()) {
				throw std::logic_error("Invalid index");
			}
			activeSessionIndex = sesIndex;
		}
		else if (strcmp(command.c_str(), "saveas") == 0) {
			std::cin.ignore();
			MyString str;
			std::cin >> str;
			sessions[activeSessionIndex - 1].saveas(str);
		}
		else if (strcmp(command.c_str(), "collage") == 0) {
			std::cin.ignore();
			MyString direction;
			std::cin >> direction;
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
			if (filenames.getSize() != 3) { throw std::logic_error("Invalid number of filenames"); }
			Polymorphic_Ptr<PortableAnymap> firstImage = sessions[activeSessionIndex - 1].getImageByFile(filenames[0]);
			Polymorphic_Ptr<PortableAnymap> secondImage = sessions[activeSessionIndex - 1].getImageByFile(filenames[1]);
			firstImage->makeCollage(*secondImage, filenames[2], direction);
		}
		else {
			std::cout << "Invalid Command" << std::endl;
		}
		std::cin >> command;
	}
}
