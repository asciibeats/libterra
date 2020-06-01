#include "terra.h"
#include <iostream>
#include <cmath>
#include <random>
#include <list>
#include <cfloat>
#include <ringnoise.h>

using namespace std;

static const int nmap[][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
//static const int xmap[][6][2] = {{{0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}}, {{1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, 0}, {0, 1}}};

static inline int adjacent(int size, int position, int crumb)
{
  int x = ((position % size) + nmap[crumb][0] + size) % size;
  int y = ((position / size) + nmap[crumb][1] + size) % size;
  return y * size + x;
}

SquareMap::SquareMap(int seed, int size, int depth, float frequency, int octaves, float lacunarity, float persistence)
{
  mt19937_64 rng(seed);
  uniform_real_distribution<float> uni(FLT_MIN, 100.0f);

  this->seed = seed;
  this->offset = uni(rng);
  this->size = size;
  this->depth = depth;
  this->frequency = frequency;
  this->octaves = octaves;
  this->lacunarity = lacunarity;
  this->persistence = persistence;
}

int SquareMap::generate(int position)
{
  float isize = 1.0f / this->size;
  int x = position % this->size;
  int y = position * isize;
  int height = rn_perlinringsum2((0.5f + x) * isize, (0.5f + y) * isize, this->offset, this->frequency, this->octaves, this->lacunarity, this->persistence) * this->depth;

  tiles[position] = height;

  return height;
}

void SquareMap::generate()
{
  float isize = 1.0f / this->size;

  for (int y = 0, position = 0; y < this->size; y++)
  {
    for (int x = 0; x < this->size; x++, position++)
    {
      tiles[position] = rn_perlinringsum2((0.5f + x) * isize, (0.5f + y) * isize, this->offset, this->frequency, this->octaves, this->lacunarity, this->persistence) * this->depth;
    }
  }
}

void SquareMap::print()
{
  char chars[6] = {'#', '~', '.', ',', '+', '*'};
  int colors[6][2] = {{36, 44}, {37, 46}, {32, 43}, {30, 42}, {32, 40}, {36, 47}};

  for (map<int, int>::iterator it = tiles.begin(); it != tiles.end();)
  {
    char c = chars[it->second % 6];
    int* col = colors[it->second % 6];

    cout << "\033[21;" << col[1] << "m\033[1;" << col[0] << "m" << c << c;
    it++;

    if (it->first % size == 0)
    {
      cout << "\033[0m" << endl;
    }
  }
}
