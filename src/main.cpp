#include <array>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

#define N 10

int main(void)
{
  // Page 6.  A comparison of C loop with C++ range-based loop.

  // C.
  int buffer1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

  for (int i = 0; i < N; i++)
  {
    LOG_INF("%d ", buffer1[i]);
  }

  //C++
  std::array<int, 10> buffer2 { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

  for (const auto& element : buffer2)
  {
    LOG_INF("%d ", element);
  }
  
}
