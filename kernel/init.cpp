#include <debug.h>
// #include <gdt.h>
#include <libcore/types.h>
#include <memory.h>
#include <multiboot2.h>

using namespace kernel;

extern "C" GenericPointer kernel_image_start;
extern "C" GenericPointer kernel_image_end;

// auto terminal_buffer = (unsigned char *)0xC03FF000;

namespace kernel {

[[noreturn]] void halt() {
  dbg() << "System halted.\n";
  __asm__("cli");
  while (1)
    __asm__("hlt");
}

extern "C" [[noreturn]] void init(GenericPointer multiboot2_pointer,
                                  uint32_t multiboot2_magic_number) {
  dbg() << "Hello, higher-half kernel world!\n";

  const uint64_t kernel_size = &kernel_image_end - &kernel_image_start;

  dbg() << "Kernel is " << kernel_size / KiB << " KiB in size.\n";

  if (kernel_size >= 1 * MiB) {
    dbg() << "Kernel too big! add another page table.\n";
    halt();
  }

  if (multiboot2_magic_number != MULTIBOOT2_BOOTLOADER_MAGIC) {
    dbg() << "Multiboot magic number is invalid!\n";
    halt();
  }

  PhysicalAddress multiboot2_physical_address(multiboot2_pointer);

  // // NULL descriptor
  // gdt::set_gate(0, 0, 0, 0, 0);

  // // Kernel code segment
  // gdt::set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

  // // Data segment
  // gdt::set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

  // gdt::flush();

  halt();
}

} // namespace kernel
