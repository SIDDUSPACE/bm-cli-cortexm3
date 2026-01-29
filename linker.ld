/* ================= ENTRY POINT ================= */
ENTRY(Reset_Handler)

/* ================= MEMORY MAP ================= */
MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 128K
  SRAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

/* ================= SECTIONS ================= */
SECTIONS
{
  /* -------- Vector Table (FLASH) -------- */
  .isr_vector :
  {
    KEEP(*(.isr_vector))
  } > FLASH

  /* -------- Code + Read-only data -------- */
  .text :
  {
    *(.text*)
    *(.rodata*)
    _etext = .;
  } > FLASH

  /* -------- Initialized Data (SRAM) -------- */
  .data : AT (_etext)
  {
    _sdata = .;
    *(.data*)
    _edata = .;
  } > SRAM

  /* Source address of .data in FLASH */
  _sidata = LOADADDR(.data);

  /* -------- Uninitialized Data -------- */
  .bss :
  {
    _sbss = .;
    *(.bss*)
    *(COMMON)
    _ebss = .;
  } > SRAM

  /* -------- Stack Pointer -------- */
  _estack = ORIGIN(SRAM) + LENGTH(SRAM);
}
