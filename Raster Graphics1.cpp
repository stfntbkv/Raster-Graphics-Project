#include "PortableAnymapFactory.h"
#include <iostream>

int main()
{
	//PortableAnymap* map = PortableAnymapFactroy::create("imagePPM.ppm");
	//map->print();


	PortableAnymap* mapBinaryPpm = PortableAnymapFactroy::create("imagePPMbinary.ppm");
	mapBinaryPpm->print();
	mapBinaryPpm->negative();
	std::cout << std::endl;
	mapBinaryPpm->print();
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


