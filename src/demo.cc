#include "terra.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
  if (argc == 1)
  {
    SquareMap smap;
    smap.generate(7, 40, 6, 1.0f, 2, 0.5f, 2.0f, 0.5f);
    smap.print();
  }
  else if (argc == 9)
  {
    SquareMap smap;
    smap.generate(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atof(argv[4]), atoi(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]));
    smap.print();
  }
  else
  {
    cout << "usage: demo [seed width height depth frequency octaves lacunarity persistence erosion]" << endl;
  }

  return 0;
}
