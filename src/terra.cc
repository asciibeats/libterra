#include "terra.h"
#include <iostream>
#include <cmath>
#include <random>
//#include <queue>
//#include <set>
#include <list>
#include <cfloat>
#include <ringnoise.h>

using namespace std;

static const int nmap[][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
//static const int xmap[][6][2] = {{{0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}}, {{1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, 0}, {0, 1}}};

static inline int adjacent(int size, int position, int crumb)
{
  int width = 1 << size;
  int x = ((position % width) + nmap[crumb][0] + width) % width;
  int y = ((position >> size) + nmap[crumb][1] + width) % width;
  return y * width + x;
}

void SquareMap::generate(int seed, int size, float frequency, int octaves, float lacunarity, float persistence, float erosion, float water, float heat)
{
  this->size = size;
  width = 1 << size;
  int length = width * width;

  mt19937_64 rng(seed);
  uniform_real_distribution<float> uni(FLT_MIN, 100.0f);

  tiles.clear();

  float offset = uni(rng);
  map<float, int, greater<float>> heights;
  map<int, float> heights2;
  float iwidth = 1.0f / width;

  for (int y = 0, i = 0; y < width; y++)
  {
    for (int x = 0; x < width; x++, i++)
    {
      float h = rn_perlinringsum2((0.5f + x) * iwidth, (0.5f + y) * iwidth, offset, frequency, octaves, lacunarity, persistence);
      heights[h] = i;
      heights2[i] = h;
    }
  }

  int cutoff = length - length * water;
  float level = 1.0f;
  int n = 0;

  for (map<float, int>::iterator it = heights.begin(); it != heights.end(); it++)
  {
    if (n == cutoff)
    {
      level = it->first + (level - it->first) * 0.5f;
      break;
    }
    else
    {
      level = it->first;
      n++;
    }
  }

  for (int i = 0; i < 1; i++)
  {
    vector<float> deposits (length, 0);

    for (map<int, float>::iterator it = heights2.begin(); it != heights2.end(); it++)
    {
      float volume = 0;

      for (int crumb = 0; crumb < 4; crumb++)
      {
        int position = adjacent(size, it->first, crumb);
        float delta = it->second - heights2[position];

        if (delta > 0)
        {
          float deposit = delta * 0.5f * erosion;
          volume += deposit;
          deposits[position] += deposit;
        }
      }

      deposits[it->first] -= volume;
    }

    for (int j = 0; j < length; j++)
    {
      heights2[j] += deposits[j];
    }
  }

  for (map<int, float>::iterator it = heights2.begin(); it != heights2.end(); ++it)
  {
    if (it->second > level)
    {
      tiles[it->first] = 2;
    }
    else
    {
      tiles[it->first] = 1;
    }
  }

  /*int width = 1 << size;

  for (int y = 0, i = 0; y < width; y++)
  {
    for (int x = 0; x < width; x++, i++)
    {
      for (vector<float>::size_type i = elevations.size() - 1; i >= 0; i--)
      {
        if (heights[i] > elevations[0])
        {
          //s.type = i + 1;
          break;
        }
      }
    }
  }*/
}

void SquareMap::print()
{
  int width = 1 << size;
  //int length = width * width;
  char chars[6] = {' ', '~', '.', '"', '*', 'A'};
  int colors[6][2] = {{30, 44}, {30, 46}, {30, 43}, {30, 42}, {37, 40}, {30, 47}};

  for (map<int, int>::iterator it = tiles.begin(); it != tiles.end();)
  {
    int type = it->second;
    char c = chars[type];
    int* col = colors[type];
    cout << "\033[21;" << col[1] << "m\033[1;" << col[0] << "m" << c << c << c;
    it++;

    if (it->first % width == 0)
    {
      cout << "\033[0m" << endl;
    }
  }

  /*for (int y = 0, i = 0; y < rows; y++)
  {
    for (int x = 0; x < cols; x++, i++)
    {
      ctile current = neighbors[i];
      tile terrain = tiles[current.center];
      //cout << "tile " << i << " " << current.center << " " << terrain.type << endl;
    }
  }*/

  /*cout << "elevations:" << endl;

  for (vector<float>::size_type i = 0; i < elevations.size(); i++)
  {
    cout << i << ": " << elevations[i] << endl;
  }

  cout << "noises:" << endl;
  cout << ns_perlin4r(0.3f, 0.7f, 0.66f, 0) << endl;
  cout << ns_perlin4r(0.1f, 0.1f, 0.36f, 0) << endl;
  cout << ns_perlin4r(0.0f, 0.0f, 0.16f, 0) << endl;
  cout << "Offset: " << offset << endl;*/
}
