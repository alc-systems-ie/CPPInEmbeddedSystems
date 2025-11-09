#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "lib/alc_ui.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

#define BUFFER_SIZE 5

typedef struct 
{
  int intArray[BUFFER_SIZE]; // Array to store integer values.
  size_t writeIndex;
  size_t readIndex;
  size_t count;
} int_ring_buffer;

void initRingBuffer(int_ring_buffer* rb)
{
  rb->writeIndex = 0;
  rb->readIndex = 0;
  rb->count = 0;
}

void ringBufferPush(int_ring_buffer* rb, int value)
{
  rb->intArray[rb->writeIndex] = value;
  rb->writeIndex = (++rb->writeIndex % BUFFER_SIZE);
  if (rb->count < BUFFER_SIZE) {
    ++rb->count;
    return;
  }
  // Buffer is full.
  rb->readIndex = (++rb->readIndex % BUFFER_SIZE);
}

int ringBufferPop(int_ring_buffer* rb)
{
  if (rb->count ==  0) { return 0; };
  int value = rb->intArray[rb->readIndex];
  rb->readIndex = (++rb->readIndex % BUFFER_SIZE);
  --rb->count;
  return value;
}

void printBuffer(int_ring_buffer* rb)
{
  for (int i = 0; i < BUFFER_SIZE; i++)
  {
    LOG_INF("%d, %d", i, rb->intArray[i]);
  }
  LOG_INF("Read Index: %d, Write Index: %d, Count: %d", rb->readIndex, rb->writeIndex, rb->count);
}

alc::ui::Ui ui;

int counter = 0;

int main(void)
{
  // Page 8.  Example of C implementation of simple ring buffer.

  // C.
  int_ring_buffer rb;
  initRingBuffer(&rb);

  // Initialse buffer;
  for (int i = 0; i < BUFFER_SIZE; i++)
  {
    ringBufferPush(&rb, 0);
  }

  // while (rb.count > 0)
  // {
  //   int value = ringBufferPop(&rb);
  //   LOG_INF("%d ", value);
  //   LOG_INF("Read Index: %d, Write Index: %d, Count: %d", rb.readIndex, rb.writeIndex, rb.count);
  // }
  //
  while (true)
  {
    if (ui.GetButton1()) {
      LOG_INF("Push.");
      ringBufferPush(&rb, counter++);
      printBuffer(&rb);
      ui.ClearButton1();
    }
    if (ui.GetButton2()) {
      LOG_INF("Pop.");
      int value = ringBufferPop(&rb);
      LOG_INF("%d ", value);
      printBuffer(&rb);
      ui.ClearButton2();
    }
    k_msleep(20);
  }

  return 0;
}
