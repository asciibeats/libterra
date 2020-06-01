#ifndef terra_h
#define terra_h

#include <map>

using namespace std;

class SquareMap
{
  public:
    int seed;
    float offset;
    int size;
    int depth;
    float frequency;
    int octaves;
    float lacunarity;
    float persistence;

    map<int, int> tiles;

    SquareMap(int seed, int size, int depth, float frequency, int octaves, float lacunarity, float persistence);
    int generate(int position);
    void generate();
    void print();
};

#endif
