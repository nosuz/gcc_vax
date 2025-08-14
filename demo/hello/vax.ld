ENTRY(_start)
SECTIONS {
  . = 0x1000;
  .text : { *(.text .text.*) *(.rodata .rodata.*) }
  .data : { *(.data .data.*) }
  .bss (NOLOAD) : {
    __bss_start = .; *(.bss .bss.*) *(COMMON); __bss_end = .;
  }
  _stack_top = 0x20000; /* 環境に合わせて調整 */
}
