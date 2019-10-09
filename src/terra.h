#ifndef terra_h
#define terra_h

#include <map>

using namespace std;

class SquareMap
{
  public:
    int seed;
    int size;
    int depth;
    map<int, int> tiles;
    void generate(int seed, float size, float depth, float frequency, int octaves, float lacunarity, float persistence, float erosion);
    void print();
};

#endif
