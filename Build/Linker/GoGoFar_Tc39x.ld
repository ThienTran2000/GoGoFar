/**************************************************************************************************
 * FILE: GoGoFar_Tc39x.ld
 *
 * UC ARCHITECTURE:
 *
 *    TC3xx
 *
 * UC FAMILY:
 *
 *    TC39xB
 *
 * DESCRIPTION:
 *
 *    uC family memory region definition file.
 *    Not all available memory regions are defined, only those used in BSP example.
 *    It includes the application linker files locating sections to memory regions at the end.
 *
 * FILE HISTORY:
 *
 *    V1  05.2020  RO
 *    - Base reference example
 *
 **************************************************************************************************
 * Copyright (C) 2015-2020 HighTec EDV-Systeme GmbH.  All rights reserved.
 * This is proprietary software. Any use of the software requires a written
 * license agreement with HighTec EDV-Systeme GmbH. Please contact for
 * detailed license information: info@hightec-rt.com.
 *************************************************************************************************/
 
OUTPUT_FORMAT("elf32-tricore")
OUTPUT_ARCH(tricore)
ENTRY(_START)


/* ================================================================================================
 * TC39XB MEMORY REGIONS
 * ==============================================================================================*/

MEMORY
{
  /* User configuration block - BMHD headers only */
  ucb_bmhd_orig (rx):  org = 0xaf400000, len = 2K
  ucb_bmhd_copy (rx):  org = 0xaf401000, len = 2K

  /* Program Flash memory - cached region */
  int_flash0 (rx):     org = 0x80000000, len = 3M
  int_flash1 (rx):     org = 0x80300000, len = 3M
  int_flash2 (rx):     org = 0x80600000, len = 3M
  int_flash3 (rx):     org = 0x80900000, len = 3M
  int_flash4 (rx):     org = 0x80C00000, len = 3M
  int_flash5 (rx):     org = 0x80F00000, len = 1M

  /* Program scratchpad memories */
  pspr_cpu0 (rx):      org = 0x70100000, len = 64K
  pspr_cpu1 (rx):      org = 0x60100000, len = 64K
  pspr_cpu2 (rx):      org = 0x50100000, len = 64K
  pspr_cpu3 (rx):      org = 0x40100000, len = 64K
  pspr_cpu4 (rx):      org = 0x30100000, len = 64K
  pspr_cpu5 (rx):      org = 0x10100000, len = 64K

  /* Data scratchpad memories */
  dspr_cpu0 (w!x):     org = 0x70000000, len = 240K
  dspr_cpu1 (w!x):     org = 0x60000000, len = 240K
  dspr_cpu2 (w!x):     org = 0x50000000, len = 96K
  dspr_cpu3 (w!x):     org = 0x40000000, len = 96K
  dspr_cpu4 (w!x):     org = 0x30000000, len = 96K
  dspr_cpu5 (w!x):     org = 0x10000000, len = 96K

  /* Distributed LMU RAM - Non-Cached regions selected
   * Local core access is always non-cached */
  dlmu_cpu0 (wx):      org = 0xB0000000, len = 64K
  dlmu_cpu1 (wx):      org = 0xB0010000, len = 64K
  dlmu_cpu2 (wx):      org = 0xB0020000, len = 64K
  dlmu_cpu3 (wx):      org = 0xB0030000, len = 64K
  dlmu_cpu4 (wx):      org = 0xB0100000, len = 64K
  dlmu_cpu5 (wx):      org = 0xB0110000, len = 64K

  /* Global LMU - Local memory Unit */
  lmu0_cached (wx):    org = 0x90040000, len = 256K
  lmu1_cached (wx):    org = 0x90080000, len = 256K
  lmu2_cached (wx):    org = 0x900C0000, len = 256K
  lmu0_noncached (wx): org = 0xB0040000, len = 256K
  lmu1_noncached (wx): org = 0xB0080000, len = 256K
  lmu2_noncached (wx): org = 0xB00C0000, len = 256K

  /* Periphery memory space region */
  periphery_base :     org = 0xF0000000, len = 0
  periphery_end  :     org = 0xFFFF0000, len = 0
}

/* memory mirrors describe same physical memory accessible by different addresses */ 
REGION_MIRROR("lmu0_cached", "lmu0_noncached")
REGION_MIRROR("lmu1_cached", "lmu1_noncached")
REGION_MIRROR("lmu2_cached", "lmu2_noncached")


/* ================================================================================================
 * MEMORY REGION SYMBOLS
 * ==============================================================================================*/

/* Internal Flash memory */
INT_FLASH_MEMORY_BASE = ORIGIN(int_flash0);
INT_FLASH_MEMORY_SIZE = 16M;
/* BMHD sections */ 
REGION_ALIAS("BMHD_ORIG", ucb_bmhd_orig)
REGION_ALIAS("BMHD_COPY", ucb_bmhd_copy)

/* CRT0 Boot Code Start */ 
REGION_ALIAS("BOOT", int_flash0)

/* BSP Interrupt handler table in RAM */
REGION_ALIAS("ISR_HANDLERS_CPU0_", pspr_cpu0) 
REGION_ALIAS("ISR_HANDLERS_CPU1_", pspr_cpu1) 
REGION_ALIAS("ISR_HANDLERS_CPU2_", pspr_cpu2) 
REGION_ALIAS("ISR_HANDLERS_CPU3_", pspr_cpu3) 
REGION_ALIAS("ISR_HANDLERS_CPU4_", pspr_cpu4) 
REGION_ALIAS("ISR_HANDLERS_CPU5_", pspr_cpu5) 

/* Core0: Output sections to memory region mapping */
REGION_ALIAS("CODE_CPU0_",      int_flash0)
REGION_ALIAS("RODATA_CPU0_",    int_flash0)
REGION_ALIAS("RAMCODE_CPU0_",   pspr_cpu0)
REGION_ALIAS("DATA_DSPR_CPU0_", dspr_cpu0)
REGION_ALIAS("DATA_DLMU_CPU0_", dlmu_cpu0)

/* Core1: Output sections to memory region mapping */
REGION_ALIAS("CODE_CPU1_",      int_flash1)
REGION_ALIAS("RODATA_CPU1_",    int_flash1)
REGION_ALIAS("RAMCODE_CPU1_",   pspr_cpu1)
REGION_ALIAS("DATA_DSPR_CPU1_", dspr_cpu1)
REGION_ALIAS("DATA_DLMU_CPU1_", dlmu_cpu1)

/* Core2: Output sections to memory region mapping */
REGION_ALIAS("CODE_CPU2_",      int_flash2)
REGION_ALIAS("RODATA_CPU2_",    int_flash2)
REGION_ALIAS("RAMCODE_CPU2_",   pspr_cpu2)
REGION_ALIAS("DATA_DSPR_CPU2_", dspr_cpu2)
REGION_ALIAS("DATA_DLMU_CPU2_", dlmu_cpu2)

/* Core3: Output sections to memory region mapping */
REGION_ALIAS("CODE_CPU3_",      int_flash3)
REGION_ALIAS("RODATA_CPU3_",    int_flash3)
REGION_ALIAS("RAMCODE_CPU3_",   pspr_cpu3)
REGION_ALIAS("DATA_DSPR_CPU3_", dspr_cpu3)
REGION_ALIAS("DATA_DLMU_CPU3_", dlmu_cpu3)

/* Core4: Output sections to memory region mapping */
REGION_ALIAS("CODE_CPU4_",      int_flash4)
REGION_ALIAS("RODATA_CPU4_",    int_flash4)
REGION_ALIAS("RAMCODE_CPU4_",   pspr_cpu4)
REGION_ALIAS("DATA_DSPR_CPU4_", dspr_cpu4)
REGION_ALIAS("DATA_DLMU_CPU4_", dlmu_cpu4)

/* Core5: Output sections to memory region mapping */
REGION_ALIAS("CODE_CPU5_",      int_flash5)
REGION_ALIAS("RODATA_CPU5_",    int_flash5)
REGION_ALIAS("RAMCODE_CPU5_",   pspr_cpu5)
REGION_ALIAS("DATA_DSPR_CPU5_", dspr_cpu5)
REGION_ALIAS("DATA_DLMU_CPU5_", dlmu_cpu5)

/* Common code and data */
REGION_ALIAS("CODE",     int_flash0)
REGION_ALIAS("RODATA",   int_flash0)
REGION_ALIAS("DATA", 	 lmu0_noncached)
REGION_ALIAS("RAM_CODE", lmu0_noncached)
 

/* ================================================================================================
 * PREDEFINED CONSTANTS
 * ==============================================================================================*/

/* Shared Global Stack as defined by AURIX architecture (PSW.IS = 1) 
 * the User stack is left on eventual User or RTOS control (PSW.IS = 0) 
 */
SHARED_STACK_SIZE = 4K;
SHARED_ISTACK_SIZE = 1K;       

/* CSA dedicated memory region size defined as 
 * (Number of CSA regions x CSA entry size) where 256 entries is Maximum 
 */
CSA_REGIONS = 256;
CSA_SIZE    = CSA_REGIONS * 64;  

/* General HEAP is case one uses certain stdlib functions */   
__HEAP_SIZE = DEFINED (__HEAP_SIZE) ? __HEAP_SIZE : 4K;  


/* ================================================================================================
 * SECTIONS: BMHD headers
 * ==============================================================================================*/
 
SECTIONS
{
	/* Boot Mode Header - original values */
	.bmhd_0_orig 0xaf400000 : { KEEP (*(.bmhd_0_orig)) } > BMHD_ORIG
	.bmhd_1_orig 0xaf400200 : { KEEP (*(.bmhd_1_orig)) } > BMHD_ORIG
	.bmhd_2_orig 0xaf400400 : { KEEP (*(.bmhd_2_orig)) } > BMHD_ORIG
	.bmhd_3_orig 0xaf400600 : { KEEP (*(.bmhd_3_orig)) } > BMHD_ORIG

	/* Boot Mode Header - copy values */
	.bmhd_0_copy 0xaf401000 : { KEEP (*(.bmhd_0_copy)) } > BMHD_COPY
	.bmhd_1_copy 0xaf401200 : { KEEP (*(.bmhd_1_copy)) } > BMHD_COPY
	.bmhd_2_copy 0xaf401400 : { KEEP (*(.bmhd_2_copy)) } > BMHD_COPY
	.bmhd_3_copy 0xaf401600 : { KEEP (*(.bmhd_3_copy)) } > BMHD_COPY
}


/* ================================================================================================
 * SECTIONS: Application BOOT code
 * Address pointed by BMHD start address value
 * ==============================================================================================*/

SECTIONS
{
	.crt0_boot : { KEEP (*(.start)) } > BOOT
	.crt0_boot : { KEEP (*(.start_cpu*)) } > BOOT 
}


/* ================================================================================================
 * SECTIONS: Reset Default TRAP handlers provided by BSP 
 * the TRAP table is shared across cores
 * BTV register value after reset is 0xA0000100 (0x80000100)
 * ==============================================================================================*/

SECTIONS
{
	.trap_reset :
	{
		
		KEEP (*(.trap_vector_table*))
		KEEP (*(.trap_handlers))
	} > CODE_CPU0_
}
	
	
/* ================================================================================================
 * SECTIONS: Interrupt tables
 * Provided Interrupt vector table and ISR Handler tables for each core
 * Code set BIV register to core corresponding Base address 
 * ==============================================================================================*/

SECTIONS
{
	.CPU0.isr_vector_table : { KEEP (*(.isr_vector_table_cpu0)) } > CODE_CPU0_
	.CPU1.isr_vector_table : { KEEP (*(.isr_vector_table_cpu1)) } > CODE_CPU1_
	.CPU2.isr_vector_table : { KEEP (*(.isr_vector_table_cpu2)) } > CODE_CPU2_
	.CPU3.isr_vector_table : { KEEP (*(.isr_vector_table_cpu3)) } > CODE_CPU3_
	.CPU4.isr_vector_table : { KEEP (*(.isr_vector_table_cpu4)) } > CODE_CPU4_
	.CPU5.isr_vector_table : { KEEP (*(.isr_vector_table_cpu5)) } > CODE_CPU5_
}

SECTIONS
{
    .CPU0.isr_ram_table (NOLOAD) : { *(.IsrRamTable_Cpu0) } > ISR_HANDLERS_CPU0_ 
    .CPU1.isr_ram_table (NOLOAD) : { *(.IsrRamTable_Cpu1) } > ISR_HANDLERS_CPU1_
    .CPU2.isr_ram_table (NOLOAD) : { *(.IsrRamTable_Cpu2) } > ISR_HANDLERS_CPU2_
    .CPU3.isr_ram_table (NOLOAD) : { *(.IsrRamTable_Cpu3) } > ISR_HANDLERS_CPU3_
    .CPU4.isr_ram_table (NOLOAD) : { *(.IsrRamTable_Cpu4) } > ISR_HANDLERS_CPU4_
    .CPU5.isr_ram_table (NOLOAD) : { *(.IsrRamTable_Cpu5) } > ISR_HANDLERS_CPU5_
}


/* ================================================================================================
 * SECTIONS: Cores' CSA regions 
 * Each core has its own CSA region list
 * ==============================================================================================*/

SECTIONS
{
	.CPU0.csa (NOLOAD) : { . = ALIGN(64); __CSA0 = .; . +=  CSA_SIZE; __CSA0_END = .;} > DATA_DSPR_CPU0_
	.CPU1.csa (NOLOAD) : { . = ALIGN(64); __CSA1 = .; . +=  CSA_SIZE; __CSA1_END = .;} > DATA_DSPR_CPU1_
    .CPU2.csa (NOLOAD) : { . = ALIGN(64); __CSA2 = .; . +=  CSA_SIZE; __CSA2_END = .;} > DATA_DSPR_CPU2_
    .CPU3.csa (NOLOAD) : { . = ALIGN(64); __CSA3 = .; . +=  CSA_SIZE; __CSA3_END = .;} > DATA_DSPR_CPU3_
    .CPU4.csa (NOLOAD) : { . = ALIGN(64); __CSA4 = .; . +=  CSA_SIZE; __CSA4_END = .;} > DATA_DSPR_CPU4_
    .CPU5.csa (NOLOAD) : { . = ALIGN(64); __CSA5 = .; . +=  CSA_SIZE; __CSA5_END = .;} > DATA_DSPR_CPU5_
}


/* ================================================================================================
 * SECTIONS: Cores' Shared Stacks 
 * Each core has its own Shared stack area (PSW.IS = 1)
 * ==============================================================================================*/

SECTIONS
{
	.CPU0.ustack : { . = ALIGN(8); __STACK_BASE_CPU0_ = .; . += SHARED_STACK_SIZE; __USTACK0 = .;} > DATA_DSPR_CPU0_ 
	.CPU1.ustack : { . = ALIGN(8); __STACK_BASE_CPU1_ = .; . += SHARED_STACK_SIZE; __USTACK1 = .;} > DATA_DSPR_CPU1_ 
	.CPU2.ustack : { . = ALIGN(8); __STACK_BASE_CPU2_ = .; . += SHARED_STACK_SIZE; __USTACK2 = .;} > DATA_DSPR_CPU2_ 
	.CPU3.ustack : { . = ALIGN(8); __STACK_BASE_CPU3_ = .; . += SHARED_STACK_SIZE; __USTACK3 = .;} > DATA_DSPR_CPU3_ 
	.CPU4.ustack : { . = ALIGN(8); __STACK_BASE_CPU4_ = .; . += SHARED_STACK_SIZE; __USTACK4 = .;} > DATA_DSPR_CPU4_ 
	.CPU5.ustack : { . = ALIGN(8); __STACK_BASE_CPU5_ = .; . += SHARED_STACK_SIZE; __USTACK5 = .;} > DATA_DSPR_CPU5_ 

	.CPU0.istack : { . = ALIGN(8); __ISTACK_BASE_CPU0_ = .; . += SHARED_ISTACK_SIZE; __ISTACK0 = .;} > DATA_DSPR_CPU0_ 
	.CPU1.istack : { . = ALIGN(8); __ISTACK_BASE_CPU1_ = .; . += SHARED_ISTACK_SIZE; __ISTACK1 = .;} > DATA_DSPR_CPU1_ 
	.CPU2.istack : { . = ALIGN(8); __ISTACK_BASE_CPU2_ = .; . += SHARED_ISTACK_SIZE; __ISTACK2 = .;} > DATA_DSPR_CPU2_ 
	.CPU3.istack : { . = ALIGN(8); __ISTACK_BASE_CPU3_ = .; . += SHARED_ISTACK_SIZE; __ISTACK3 = .;} > DATA_DSPR_CPU3_ 
	.CPU4.istack : { . = ALIGN(8); __ISTACK_BASE_CPU4_ = .; . += SHARED_ISTACK_SIZE; __ISTACK4 = .;} > DATA_DSPR_CPU4_ 
	.CPU5.istack : { . = ALIGN(8); __ISTACK_BASE_CPU5_ = .; . += SHARED_ISTACK_SIZE; __ISTACK5 = .;} > DATA_DSPR_CPU5_ 
}


/* ================================================================================================
 * SECTIONS: CORE 0 dedicated sections
 * In the example they are Empty, but user might used them to play
 * with core specific placement
 * ==============================================================================================*/

SECTIONS
{
	.CPU0.code     : {  } > CODE_CPU0_
	.CPU0.ramcode  : {  } > RAMCODE_CPU0_ AT > RODATA_CPU0_
	.CPU0.rodata   : {  } > RODATA_CPU0_
	.CPU0.data     : {  } > DATA_DSPR_CPU0_ AT > RODATA_CPU0_
	.CPU0.bss      : {  } > DATA_DSPR_CPU0_
}


/* ================================================================================================
 * SECTIONS: CORE 1 dedicated sections
 * In the example they are Empty, but user might used them to play
 * with core specific placement
 * ==============================================================================================*/

SECTIONS
{
	.CPU1.code     : {  } > CODE_CPU1_
	.CPU1.ramcode  : {  } > RAMCODE_CPU1_ AT > RODATA_CPU1_
	.CPU1.rodata   : {  } > RODATA_CPU1_
	.CPU1.data     : {  } > DATA_DSPR_CPU1_ AT > RODATA_CPU1_
	.CPU1.bss      : {  } > DATA_DSPR_CPU1_
}


/* ================================================================================================
 * SECTIONS: CORE 2 dedicated sections
 * In the example they are Empty, but user might used them to play
 * with core specific placement
 * ==============================================================================================*/

SECTIONS
{
	.CPU2.code     : {  } > CODE_CPU2_
	.CPU2.ramcode  : {  } > RAMCODE_CPU2_ AT > RODATA_CPU2_
	.CPU2.rodata   : {  } > RODATA_CPU2_
	.CPU2.data     : {  } > DATA_DSPR_CPU2_ AT > RODATA_CPU2_
	.CPU2.bss      : {  } > DATA_DSPR_CPU2_
}


/* ================================================================================================
 * SECTIONS: CORE 3 dedicated sections
 * In the example they are Empty, but user might used them to play
 * with core specific placement
 * ==============================================================================================*/

SECTIONS
{
	.CPU3.code     : {  } > CODE_CPU3_
	.CPU3.ramcode  : {  } > RAMCODE_CPU3_ AT > RODATA_CPU3_
	.CPU3.rodata   : {  } > RODATA_CPU3_
	.CPU3.data     : {  } > DATA_DSPR_CPU3_ AT > RODATA_CPU3_
	.CPU3.bss      : {  } > DATA_DSPR_CPU3_
}


/* ================================================================================================
 * SECTIONS: CORE 4 dedicated sections
 * In the example they are Empty, but user might used them to play
 * with core specific placement
 * ==============================================================================================*/

SECTIONS
{
	.CPU4.code     : {  } > CODE_CPU4_
	.CPU4.ramcode  : {  } > RAMCODE_CPU4_ AT > RODATA_CPU4_
	.CPU4.rodata   : {  } > RODATA_CPU4_
	.CPU4.data     : {  } > DATA_DSPR_CPU4_ AT > RODATA_CPU4_
	.CPU4.bss      : {  } > DATA_DSPR_CPU4_
}


/* ================================================================================================
 * SECTIONS: CORE 5 dedicated sections
 * In the example they are Empty, but user might used them to play
 * with core specific placement
 * ==============================================================================================*/

SECTIONS
{
	.CPU5.code    : {  } > CODE_CPU5_
	.CPU5.ramcode : {  } > RAMCODE_CPU5_ AT > RODATA_CPU5_
	.CPU5.rodata  : {  } > RODATA_CPU5_
	.CPU5.data    : {  } > DATA_DSPR_CPU5_ AT > RODATA_CPU5_
	.CPU5.bss     : {  } > DATA_DSPR_CPU5_
}


/* ================================================================================================
 * SECTIONS: COMMON (shared) sections
 * by default, all example sections are located here
 * ==============================================================================================*/

SECTIONS
{
	/* Code sections */
	.code :	
	{ 
	    *(.text*) 
	} > CODE
	
	/* code to execute from RAM */
	.ramcode :
	{
	    *(.ramcode*)
	} > RAM_CODE AT > RODATA
	
	/* read-only data, constants */
	.rodata : 
	{
	    *(.rodata*)
	} > RODATA

	/* C++ constructors */
	.ctors : ALIGN(4) FLAGS(arl) 
	{
		__CTOR_LIST__ = .;
		LONG((__CTOR_END__ - __CTOR_LIST__) / 4 - 2)
		KEEP (*(.ctors));
		LONG(0);
		__CTOR_END__ = .;	
	} > RODATA
	
	/* Short-addressable read-only data */
	.sdata2 : 
	{
	    *(.sdata2*)
	} > RODATA
	
	/* Short-addresable read-write data - initialized */
	.sdata : 
	{
	    *(.sdata*)
	} > DATA AT > RODATA
	
	/* Short-addresable read-write data - non-initialized (zeroed) */
	.sbss : 
	{
	    *(.sbss*)
	} > DATA
	
	/* read-write data - initialized */
	.data : 
	{
	    *(.data*)
	} > DATA AT > RODATA

	/* read-write data - non-initialized */
	.bss : 
	{
	     *(.bss*); 
	     *(COMMON);
	} > DATA
	
	/* HEAP area for stdlib functions */
	.heap : ALIGN(8) 
	{ 
	    . += __HEAP_SIZE;
	} > DATA
}


/* ================================================================================================
 * SECTIONS: CLEAR & COPY TABLES with END delimiter to support crt0 init
 * clear_table: 
 *    data memory ranges to clear to zero
 * copy_table:  
 *    data memory ranges that needs to be value initialized
 *    (init values are stored in FLASH and copied to RAM)
 * Each core has its own table to process during its init to allow multicore execution. 
 * Shared resources are inserted to Core[0] tables (the RESET core)
 * ==============================================================================================*/
SECTIONS
{
    /*-------------------------------------------------------------------------------------------*/

	.CPU0.clear_sec :
	{
		LONG(ADDR(.CPU0.bss)); LONG(SIZEOF(.CPU0.bss));
		LONG(ADDR(.sbss)); LONG(SIZEOF(.sbss)); 
		LONG(ADDR(.bss)); LONG(SIZEOF(.bss));
		LONG(ADDR(.heap)); LONG(SIZEOF(.heap));
		LONG(-1); LONG(-1);
	} > RODATA_CPU0_

	.CPU0.copy_sec :
	{
		LONG(LOADADDR(.CPU0.ramcode)); LONG(ADDR(.CPU0.ramcode)); LONG(SIZEOF(.CPU0.ramcode));
		LONG(LOADADDR(.CPU0.data)); LONG(ADDR(.CPU0.data)); LONG(SIZEOF(.CPU0.data));
		LONG(LOADADDR(.ramcode)); LONG(ADDR(.ramcode)); LONG(SIZEOF(.ramcode));
		LONG(LOADADDR(.sdata)); LONG(ADDR(.sdata)); LONG(SIZEOF(.sdata));
		LONG(LOADADDR(.data)); LONG(ADDR(.data)); LONG(SIZEOF(.data));
		LONG(-1); LONG(-1); LONG(-1);
	} > RODATA_CPU0_

	/*-------------------------------------------------------------------------------------------*/

	.CPU1.clear_sec :
	{
		LONG(ADDR(.CPU1.bss)); LONG(SIZEOF(.CPU1.bss));
		LONG(-1); LONG(-1);
	} > RODATA_CPU1_
	
	.CPU1.copy_sec :
	{
		LONG(LOADADDR(.CPU1.ramcode)); LONG(0 + ADDR(.CPU1.ramcode)); LONG(SIZEOF(.CPU1.ramcode));
		LONG(LOADADDR(.CPU1.data)); LONG(ADDR(.CPU1.data)); LONG(SIZEOF(.CPU1.data));
		LONG(-1); LONG(-1); LONG(-1);
	} > RODATA_CPU1_

	/*-------------------------------------------------------------------------------------------*/

	.CPU2.clear_sec :
	{
		LONG(ADDR(.CPU2.bss)); LONG(SIZEOF(.CPU2.bss));
		LONG(-1); LONG(-1);
	} > RODATA_CPU2_
	
	.CPU2.copy_sec :
	{
		LONG(LOADADDR(.CPU2.ramcode)); LONG(0 + ADDR(.CPU2.ramcode)); LONG(SIZEOF(.CPU2.ramcode));
		LONG(LOADADDR(.CPU2.data)); LONG(0 + ADDR(.CPU2.data)); LONG(SIZEOF(.CPU2.data));
		LONG(-1); LONG(-1); LONG(-1);
	} > RODATA_CPU2_

	/*-------------------------------------------------------------------------------------------*/

	.CPU3.clear_sec :
	{
		LONG(ADDR(.CPU3.bss)); LONG(SIZEOF(.CPU3.bss));
		LONG(-1); LONG(-1);
	} > RODATA_CPU3_
	
	.CPU3.copy_sec :
	{
		LONG(LOADADDR(.CPU3.ramcode)); LONG(0 + ADDR(.CPU3.ramcode)); LONG(SIZEOF(.CPU3.ramcode));
		LONG(LOADADDR(.CPU3.data)); LONG(0 + ADDR(.CPU3.data)); LONG(SIZEOF(.CPU3.data));
		LONG(-1); LONG(-1); LONG(-1);
	} > RODATA_CPU3_

	/*-------------------------------------------------------------------------------------------*/

	.CPU4.clear_sec :
	{
		LONG(ADDR(.CPU4.bss)); LONG(SIZEOF(.CPU4.bss));
		LONG(-1); LONG(-1);
	} > RODATA_CPU4_
	
	.CPU4.copy_sec :
	{
		LONG(LOADADDR(.CPU4.ramcode)); LONG(0 + ADDR(.CPU4.ramcode)); LONG(SIZEOF(.CPU4.ramcode));
		LONG(LOADADDR(.CPU4.data)); LONG(0 + ADDR(.CPU4.data)); LONG(SIZEOF(.CPU4.data));
		LONG(-1); LONG(-1); LONG(-1);
	} > RODATA_CPU4_

	/*-------------------------------------------------------------------------------------------*/

	.CPU5.clear_sec :
	{
		LONG(ADDR(.CPU5.bss)); LONG(SIZEOF(.CPU5.bss));
		LONG(-1); LONG(-1);
	} > RODATA_CPU5_
	
	.CPU5.copy_sec :
	{
		LONG(LOADADDR(.CPU5.ramcode)); LONG(0 + ADDR(.CPU5.ramcode)); LONG(SIZEOF(.CPU5.ramcode));
		LONG(LOADADDR(.CPU5.data)); LONG(0 + ADDR(.CPU5.data)); LONG(SIZEOF(.CPU5.data));
		LONG(-1); LONG(-1); LONG(-1);
	} > RODATA_CPU5_
}


/* ================================================================================================
 * Linker Symbols
 * ==============================================================================================*/

/* Read only small address pointer */
__A1_MEM = ADDR(.sdata2) + 0x8000;

/* Volatile data short address pointer (.sdata before .sbss) */
__A0_MEM = ADDR(.sdata) + 0x8000;

__A8_MEM = 0;

__A9_MEM = 0;

/* Expected HEAP SYMBOLS */
__HEAP     = ADDR(.heap);
__HEAP_END = ADDR(.heap) + SIZEOF(.heap);


/* ================================================================================================
 * CRT0 CONFIG STRUCTURE
 * Initialization structure for uC Cores used in crt0 startup code
 * Each core has itw one table entry.
 * ==============================================================================================*/

SECTIONS
{
	.crt0_config : ALIGN(4)
	{
		PROVIDE(__crt0_config = .);        /* base of the crt0 config table */
		
		/* Core[0] */
		LONG(ADDR(.CPU0.ustack));          /* USTACK address */ 
		LONG(SIZEOF(.CPU0.ustack));        /* USTACK size */
		LONG(ADDR(.CPU0.csa));             /* CSA address */ 
		LONG(SIZEOF(.CPU0.csa));           /* CSA size */
		LONG(__A0_MEM);                /* SDATA address */
		LONG(__A1_MEM);               /* SDATA2 address */
		LONG(0);                           /* SDATA3 address */
		LONG(0);                           /* SDATA4 address */
		LONG(ADDR(.CPU0.clear_sec));       /* CLEAR table */
		LONG(ADDR(.CPU0.copy_sec));        /* COPY table */
		LONG(ADDR(.CPU0.istack));          /* ISTACK address */ 
		LONG(SIZEOF(.CPU0.istack));        /* ISTACK size */
		
		/* Core[1] */
		LONG(ADDR(.CPU1.ustack));           /* STACK address */ 
		LONG(SIZEOF(.CPU1.ustack));         /* STACK size */
		LONG(ADDR(.CPU1.csa));             /* CSA address */ 
		LONG(SIZEOF(.CPU1.csa));           /* CSA size */
		LONG(__A0_MEM);                /* SDATA address */
		LONG(__A1_MEM);               /* SDATA2 address */
		LONG(0);                           /* SDATA3 address */
		LONG(0);                           /* SDATA4 address */
		LONG(ADDR(.CPU1.clear_sec) );      /* CLEAR table */
		LONG(ADDR(.CPU1.copy_sec));        /* COPY table */
		LONG(ADDR(.CPU1.istack));          /* ISTACK address */ 
		LONG(SIZEOF(.CPU1.istack));        /* ISTACK size */
		
		/* Core[2] */
		LONG(ADDR(.CPU2.ustack));           /* STACK address */ 
		LONG(SIZEOF(.CPU2.ustack));         /* STACK size */
		LONG(ADDR(.CPU2.csa));             /* CSA address */ 
		LONG(SIZEOF(.CPU2.csa));           /* CSA size */
		LONG(__A0_MEM);                /* SDATA address */
		LONG(__A1_MEM);               /* SDATA2 address */
		LONG(0);                           /* SDATA3 address */
		LONG(0);                           /* SDATA4 address */
		LONG(ADDR(.CPU2.clear_sec));       /* CLEAR table */
		LONG(ADDR(.CPU2.copy_sec));        /* COPY table */
		LONG(ADDR(.CPU2.istack));          /* ISTACK address */ 
		LONG(SIZEOF(.CPU2.istack));        /* ISTACK size */

		/* Core[3] */
		LONG(ADDR(.CPU3.ustack));           /* STACK address */ 
		LONG(SIZEOF(.CPU3.ustack));         /* STACK size */
		LONG(ADDR(.CPU3.csa));             /* CSA address */ 
		LONG(SIZEOF(.CPU3.csa));           /* CSA size */
		LONG(__A0_MEM);                /* SDATA address */
		LONG(__A1_MEM);               /* SDATA3 address */
		LONG(0);                           /* SDATA3 address */
		LONG(0);                           /* SDATA4 address */
		LONG(ADDR(.CPU3.clear_sec));       /* CLEAR table */
		LONG(ADDR(.CPU3.copy_sec));        /* COPY table */
		LONG(ADDR(.CPU3.istack));          /* ISTACK address */ 
		LONG(SIZEOF(.CPU3.istack));        /* ISTACK size */

		/* Core[4] */
		LONG(ADDR(.CPU4.ustack));           /* STACK address */ 
		LONG(SIZEOF(.CPU4.ustack));         /* STACK size */
		LONG(ADDR(.CPU4.csa));             /* CSA address */ 
		LONG(SIZEOF(.CPU4.csa));           /* CSA size */
		LONG(__A0_MEM);                /* SDATA address */
		LONG(__A1_MEM);               /* SDATA3 address */
		LONG(0);                           /* SDATA3 address */
		LONG(0);                           /* SDATA4 address */
		LONG(ADDR(.CPU4.clear_sec));       /* CLEAR table */
		LONG(ADDR(.CPU4.copy_sec));        /* COPY table */
		LONG(ADDR(.CPU4.istack));          /* ISTACK address */ 
		LONG(SIZEOF(.CPU4.istack));        /* ISTACK size */

		/* Dummy entry due to CoreId index gap in TC39x */
		LONG(0);                           /* STACK address */ 
		LONG(0);                           /* STACK size */
		LONG(0);                           /* CSA address */ 
		LONG(0);                           /* CSA size */
		LONG(0);                           /* SDATA address */
		LONG(0);                           /* SDATA3 address */
		LONG(0);                           /* SDATA3 address */
		LONG(0);                           /* SDATA4 address */
		LONG(0);                           /* CLEAR table */
		LONG(0);                           /* COPY table */
		LONG(0);          					/* ISTACK address */ 
		LONG(0);        					/* ISTACK size */

		/* Core[5] */
		LONG(ADDR(.CPU5.ustack));           /* STACK address */ 
		LONG(SIZEOF(.CPU5.ustack));         /* STACK size */
		LONG(ADDR(.CPU5.csa));             /* CSA address */ 
		LONG(SIZEOF(.CPU5.csa));           /* CSA size */
		LONG(__A0_MEM);                /* SDATA address */
		LONG(__A1_MEM);               /* SDATA3 address */
		LONG(0);                           /* SDATA3 address */
		LONG(0);                           /* SDATA4 address */
		LONG(ADDR(.CPU5.clear_sec));       /* CLEAR table */
		LONG(ADDR(.CPU5.copy_sec));        /* COPY table */
		LONG(ADDR(.CPU5.istack));          /* ISTACK address */ 
		LONG(SIZEOF(.CPU5.istack));        /* ISTACK size */

	} > RODATA 
}


/* ================================================================================================
 * DWARF debug sections and others
 * Symbols in the DWARF debugging sections are relative to the
 * beginning of the section, so we begin them at 0.
 * ==============================================================================================*/

SECTIONS
{	
	/* DWARF 1 */
	.comment            0 : { *(.comment) }
	.debug              0 : { *(.debug) }
	.line               0 : { *(.line) }
	
	/* GNU DWARF 1 extensions */
	.debug_srcinfo      0 : { *(.debug_srcinfo) }
	.debug_sfnames      0 : { *(.debug_sfnames) }
	
	/* DWARF 1.1 and DWARF 2 */
	.debug_aranges      0 : { *(.debug_aranges) }
	.debug_pubnames     0 : { *(.debug_pubnames) }
	
	/* DWARF 2 */
	.debug_info         0 : { *(.debug_info) }
	.debug_abbrev       0 : { *(.debug_abbrev) }
	.debug_line         0 : { *(.debug_line) }
	.debug_frame        0 : { *(.debug_frame) }
	.debug_str          0 : { *(.debug_str) }
	.debug_loc          0 : { *(.debug_loc) }
	.debug_macinfo      0 : { *(.debug_macinfo) }
	.debug_ranges       0 : { *(.debug_ranges) }
	
	/* DWARF 2 control flow extension */
	.debug_control_flow 0 : { *(.debug_control_flow) }
	
	/* SGI/MIPS DWARF 2 extensions */
	.debug_weaknames    0 : { *(.debug_weaknames) }
	.debug_funcnames    0 : { *(.debug_funcnames) }
	.debug_typenames    0 : { *(.debug_typenames) }
	.debug_varnames     0 : { *(.debug_varnames) }
	
	.version_info       0 : { *(.version_info) }
}
