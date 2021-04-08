#include <gdt.h>

namespace kernel {

namespace gdt {

static entry_t s_gdt_table[GDT_MAX_ENTRIES];
static ptr_t s_gdt_ptr;

void flush() {
  s_gdt_ptr.limit = (sizeof(entry_t) * GDT_MAX_ENTRIES) - 1;
  s_gdt_ptr.base = (uint32_t)&s_gdt_table;

  __asm__ __volatile__("lgdt %0" ::"m"(s_gdt_ptr) : "memory");

  // Set up registers with our data segment offset
  __asm__ __volatile__("mov %%ax, %%ds\n"
                       "mov %%ax, %%es\n"
                       "mov %%ax, %%fs\n"
                       "mov %%ax, %%gs\n"
                       "mov %%ax, %%ss\n" ::"a"(0x10)
                       : "memory");
}

void set_gate(size_t i, uint32_t base, uint32_t limit, uint8_t access,
              uint8_t gran) {
  // verify(i < GDT_MAX_ENTRIES);
  s_gdt_table[i].base_low = (base & 0xFFFF);
  s_gdt_table[i].base_mid = (base >> 16) & 0xFF;
  s_gdt_table[i].base_upp = (base >> 24) & 0xFF;
  s_gdt_table[i].limit_low = (limit & 0xFFFF);
  s_gdt_table[i].gran = ((limit >> 16) & 0x0F);
  s_gdt_table[i].gran |= (gran & 0xF0);
  s_gdt_table[i].access = access;
}

entry_t entry_at_index(size_t i) {
  // verify(i < GDT_MAX_ENTRIES);
  return s_gdt_table[i];
}

} // namespace gdt

} // namespace kernel
