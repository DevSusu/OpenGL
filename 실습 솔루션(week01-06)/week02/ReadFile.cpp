#include <fstream>
#include "ReadFile.h"
void readFile(float &cen_x, float &cen_y, float &cen_z, float &radius){
	std::ifstream ifs("data.txt");

	ifs >> cen_x >> cen_y >> cen_z >> radius;
}