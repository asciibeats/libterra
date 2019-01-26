#ifndef TERRA_H
#define TERRA_H

#include <map>
#include <vector>

using namespace std;

class SquareMap
{
	public:
		int size;
		map<int, int> tiles;
		void generate(int seed, int size, float frequency, int octaves, float lacunarity, float persistence, float erosion, float water, float heat);
		void print();
};

#endif
