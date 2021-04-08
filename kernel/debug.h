#pragma once

#include <libcore/logstream.h>

namespace kernel {

class DebugStream final : public LogStream {
public:
  DebugStream() {}

#ifdef QEMU_DEBUGGING
  virtual void write(const char *str, size_t n) const {
    for (size_t i = 0; i < n; i++)
      __asm__ __volatile__("outb %%al, %%dx" : : "a"(str[i]), "d"(0xE9));
  }
#endif

private:
};

DebugStream dbg();

}
