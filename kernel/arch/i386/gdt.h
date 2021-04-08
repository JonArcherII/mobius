#pragma once

#include <libcore/types.h>

#define GDT_MAX_ENTRIES 8

namespace kernel {

namespace gdt {

typedef struct __attribute__((packed)) {
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_mid;
  uint8_t access;
  uint8_t gran;
  uint8_t base_upp;
} entry_t;

typedef struct __attribute__((packed)) {
  uint16_t limit;
  uint32_t base;
} ptr_t;

void flush();
void set_gate(size_t, uint32_t, uint32_t, uint8_t, uint8_t);
entry_t entry_at_index(size_t);

} // namespace gdt

} // namespace kernel
