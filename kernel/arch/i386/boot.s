.extern init
.extern kernel_image_start
.extern kernel_image_end

.section .multiboot

header_start:
    .int     0xe85250d6
    .int     0x0
    .int     header_end - header_start
    .int     0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))

    .align   8, 0x90

    .short   0x0
    .short   0x0
    .int     0x8

header_end:

.section .bss

stack_bottom:
    .skip 32768
stack_top:

boot_page_directory:
    .skip 4096
boot_page_table_0:
    .skip 4096

.section .text

.global start
start:
    cli
    movl $(boot_page_table_0 - 0xC0000000), %edi
	movl $0, %esi
	movl $1023, %ecx
1:
	cmpl $kernel_image_start, %esi
	jl 2f
	cmpl $(kernel_image_end - 0xC0000000), %esi
	jge 3f
	movl %esi, %edx
	orl $0x003, %edx
	movl %edx, (%edi)
2:
	addl $4096, %esi
	addl $4, %edi
	loop 1b
3:
	movl $(0x000B8000 | 0x003), boot_page_table_0 - 0xC0000000 + 1023 * 4
	movl $(boot_page_table_0 - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000 + 0
	movl $(boot_page_table_0 - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000 + 768 * 4
	movl $(boot_page_directory - 0xC0000000), %ecx
	movl %ecx, %cr3
	movl %cr0, %ecx
	orl $0x80010000, %ecx
	movl %ecx, %cr0
	lea 4f, %ecx
	jmp *%ecx
4:
	movl $0, boot_page_directory + 0
	movl %cr3, %ecx
	movl %ecx, %cr3
	mov $stack_top, %esp
    xorl %ebp, %ebp
    pushl %ebp
    pushl %eax
    pushl %ebx
	call init
	cli
5:	hlt
	jmp 5b
