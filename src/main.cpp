#include <array>
#include <algorithm>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

#define N 10

int main(void)
{
  // Page 7.  Example of C++ lamda function to sort numbers below 10.

  // C.
  int arrayA [] = { 1, 2, 30, 4, 50, 60, 7, 8, 90, 100 };
  int arrayB [N];

  int idx { 0 };
  for (int i = 0; i < (sizeof(arrayA) / sizeof(int)); i++)
  {
    if (arrayA[i] < 10)
    {
      arrayB[idx++] = arrayA[i];
      LOG_INF("%d ", arrayB[idx - 1]);
    }
  }

  //C++
  std::array<int, 10> arrayC { 1, 2, 30, 4, 50, 60, 7, 8, 90, 100 };
  std::array<int, 10> arrayD { };

  auto lessThan10 = [](auto x ) -> bool { return x < 10; };
  
  std::copy_if(std::begin(arrayC), std::end(arrayC), std::begin(arrayD), lessThan10);

  for (const auto& element : arrayD)
  {
    if ((element > 0) && (element < 10)) { LOG_INF("%d ", element); }
  }
  
}
