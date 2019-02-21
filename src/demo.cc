#include "terra.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
  if (argc == 1)
  {
    SquareMap smap;
    smap.generate(7, 4, 0.8f, 3, 0.6f, 0.3f, 0.5f, 0.5f, 0.5f);
    smap.print();
  }
  else if (argc == 10)
  {
    SquareMap smap;
    smap.generate(atoi(argv[1]), atoi(argv[2]), atof(argv[3]), atoi(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), atof(argv[9]));
    smap.print();
  }
  else
  {
    cout << "syntax: ./demo <seed> <size> <frequency> <octaves> <lacunarity> <persistence> <erosion> <water> <heat>" << endl;
  }

  return 0;
}
