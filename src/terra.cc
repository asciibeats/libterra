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

void SquareMap::generate(int seed, float size, float depth, float frequency, int octaves, float lacunarity, float persistence, float erosion)
{
  this->seed = seed;
  this->size = size;
  this->depth = depth;
  int length = size * size;

  mt19937_64 rng(seed);
  uniform_real_distribution<float> uni(FLT_MIN, 100.0f);

  float offset = uni(rng);
  map<int, float> heights;
  float isize = 1.0f / size;

  float min = 1.0f;
  float max = 0.0f;

  for (int y = 0, i = 0; y < size; y++)
  {
    for (int x = 0; x < size; x++, i++)
    {
      float h = rn_perlinringsum2((0.5f + x) * isize, (0.5f + y) * isize, offset, frequency, octaves, lacunarity, persistence);
      heights[i] = h;

      if (h < min)
      {
        min = h;
      }

      if (h > max)
      {
        max = h;
      }
    }
  }

  vector<float> deposits (length, 0);

  for (map<int, float>::iterator it = heights.begin(); it != heights.end(); it++)
  {
    map<int, float> deltas;

    for (int crumb = 0; crumb < 4; crumb++)
    {
      int position = adjacent(size, it->first, crumb);
      float delta = it->second - heights[position];

      if (delta > 0)
      {
        deltas[position] = delta * 0.5f * erosion;
      }
    }

    int size = deltas.size();

    if (size > 0)
    {
      float isize = 1.0f / size;

      for (map<int, float>::iterator it2 = deltas.begin(); it2 != deltas.end(); it2++)
      {
        float delta = it2->second * isize;
        deposits[it->first] -= delta;
        deposits[it2->first] += delta;
      }
    }
  }

  for (int j = 0; j < length; j++)
  {
    heights[j] += deposits[j];
  }

  for (map<int, float>::iterator it = heights.begin(); it != heights.end(); ++it)
  {
    tiles[it->first] = (it->second - min) * (1.0f / (max - min + FLT_EPSILON)) * depth;
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
