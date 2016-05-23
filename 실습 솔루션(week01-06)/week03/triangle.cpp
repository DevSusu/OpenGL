#include "triangle.h"
#include <fstream>

void readFile(float** position)
{
	std::ifstream ifs("input.txt");
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			ifs >> position[i][j];
		}
	}
}