#include "terra.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
  if (argc == 1)
  {
    cout << "./demo " << 7 << " " << 40 << " " << 6 << " " << 1.0f << " " << 2 << " " << 0.5f << " " << 2.0f << " " << endl;
    SquareMap smap(7, 40, 6, 1.0f, 2, 0.5f, 2.0f);
    smap.generate();
    smap.print();
  }
  else if (argc == 8)
  {
    SquareMap smap(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atof(argv[4]), atoi(argv[5]), atof(argv[6]), atof(argv[7]));
    smap.generate();
    smap.print();
  }
  else
  {
    cout << "usage: demo [seed size depth frequency octaves lacunarity persistence]" << endl;
  }

  return 0;
}
