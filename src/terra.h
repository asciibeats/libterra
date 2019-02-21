#ifndef terra_h
#define terra_h

#include <map>
#include <vector>

using namespace std;

class SquareMap
{
  public:
    int size;
    int width;
    map<int, int> tiles;
    void generate(int seed, int size, float frequency, int octaves, float lacunarity, float persistence, float erosion, float water, float heat);
    void print();
};

#endif
