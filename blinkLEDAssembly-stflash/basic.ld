ENTRY(main)

MEMORY {
  FLASH (rx) : ORIGIN = 0x8000000,  LENGTH = 1024K
  RAM (rw)  : ORIGIN = 0x20000000, LENGTH = 128K
}

_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS {
  .int_vector_table : {
    *(.int_vector_table)
  } > FLASH
  .text : {
    *(.text)
  } > FLASH
}
