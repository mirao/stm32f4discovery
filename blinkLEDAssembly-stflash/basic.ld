ENTRY(main)

_estack = 0x20020000;

MEMORY {
  FLASH (rx) : ORIGIN = 0x8000000,  LENGTH = 1024K
  RAM (rw)  : ORIGIN = 0x20000000, LENGTH = 192K
}

SECTIONS {
  .int_vector_table : {
    *(.int_vector_table)
  } > FLASH
  .text : {
    *(.text)
  } > FLASH
}
