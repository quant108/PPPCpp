#include "swaps.h"
#include "../../../std_lib_facilities.h"

int main()
{
  const int cx = 7;
  const int cy = 9;
  swap_r(cx, cy);
  swap_r(7.7, 9.9);

  cout << "cx: " << cx << ", " << "cy: " << cy << endl;
}
