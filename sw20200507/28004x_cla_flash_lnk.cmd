
MEMORY
{
PAGE 0 :
   /* BEGIN is used for the "boot to SARAM" bootloader mode   */

   BEGIN            : origin = 0x080000, length = 0x000002
   RAMM0            : origin = 0x0000F3, length = 0x00030D

   RAMLS0_CLAProg   : origin = 0x008000, length = 0x000800
   RAMLS1           : origin = 0x008800, length = 0x000800
   RAMLS2_C28Prog   : origin = 0x009000, length = 0x000800
   RAMLS3           : origin = 0x009800, length = 0x000800

   RESET            : origin = 0x3FFFC0, length = 0x000002

/* Flash sectors */
   /* BANK 0 */
   FLASH_BANK0_SEC0  : origin = 0x080002, length = 0x000FFE	/* on-chip Flash */
   FLASH_BANK0_SEC1  : origin = 0x081000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC2  : origin = 0x082000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC3  : origin = 0x083000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC4  : origin = 0x084000, length = 0x001000	/* on-chip Flash */
//   FLASH_BANK0_SEC5  : origin = 0x085000, length = 0x001000	/* on-chip Flash */
//   FLASH_BANK0_SEC6  : origin = 0x086000, length = 0x001000	/* on-chip Flash */
//   FLASH_BANK0_SEC7  : origin = 0x087000, length = 0x001000	/* on-chip Flash */
//   FLASH_BANK0_SEC8  : origin = 0x088000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC5_8  : origin = 0x085000, length = 0x004000	/* on-chip Flash */
   FLASH_BANK0_SEC9_10  : origin = 0x089000, length = 0x002000	/* on-chip Flash */
//   FLASH_BANK0_SEC10 : origin = 0x08A000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC11 : origin = 0x08B000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC12 : origin = 0x08C000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC13 : origin = 0x08D000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC14 : origin = 0x08E000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC15 : origin = 0x08F000, length = 0x001000	/* on-chip Flash */

   /* BANK 1 */
   FLASH_BANK1_SEC0  : origin = 0x090000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC1  : origin = 0x091000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC2  : origin = 0x092000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC3  : origin = 0x093000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC4  : origin = 0x094000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC5  : origin = 0x095000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC6  : origin = 0x096000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC7  : origin = 0x097000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC8  : origin = 0x098000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC9  : origin = 0x099000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC10 : origin = 0x09A000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC11 : origin = 0x09B000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC12 : origin = 0x09C000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC13 : origin = 0x09D000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC14 : origin = 0x09E000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC15 : origin = 0x09F000, length = 0x000FF0	/* on-chip Flash */

//   FLASH_BANK1_SEC15_RSVD : origin = 0x09FFF0, length = 0x000010  /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

PAGE 1 :

   BOOT_RSVD       : origin = 0x000002, length = 0x0000F1     /* Part of M0, BOOT rom will use this for stack */
   RAMM1           : origin = 0x000400, length = 0x0003F8     /* on-chip RAM block M1 */
//   RAMM1_RSVD      : origin = 0x0007F8, length = 0x000008     /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */



   RAMLS4_CLAData   : origin = 0x00A000, length = 0x000800
   RAMLS5           : origin = 0x00A800, length = 0x000800
   RAMLS6_C28Data   : origin = 0x00B000, length = 0x000800
   RAMLS7_C28Data   : origin = 0x00B800, length = 0x000800

   RAMGS0           : origin = 0x00C000, length = 0x002000
   RAMGS1           : origin = 0x00E000, length = 0x002000
   RAMGS2           : origin = 0x010000, length = 0x002000
   RAMGS3           : origin = 0x012000, length = 0x001FF8
//   RAMGS3_RSVD      : origin = 0x013FF8, length = 0x000008     /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   CLA1_MSGRAMLOW   : origin = 0x001480, length = 0x000080
   CLA1_MSGRAMHIGH  : origin = 0x001500, length = 0x000080
}


SECTIONS
{
   /* Allocate program areas: */
   .cinit           : > FLASH_BANK0_SEC9_10,     PAGE = 0, ALIGN(4)
   .text            : >>FLASH_BANK0_SEC2 | FLASH_BANK0_SEC3 | FLASH_BANK0_SEC4 | FLASH_BANK0_SEC5_8 ,   PAGE = 0, ALIGN(4)
   codestart        : > BEGIN       PAGE = 0, ALIGN(4)
   
   .stack           : > RAMM1        PAGE = 1
   .switch          : > FLASH_BANK0_SEC1,     PAGE = 0, ALIGN(4)
   .farconst           : > FLASH_BANK0_SEC5_8,       PAGE = 0,       ALIGN(4)

#if defined(__TI_EABI__)
   .init_array      : > FLASH_BANK0_SEC1,       PAGE = 0,       ALIGN(4)
   .bss             : > RAMLS6_C28Data,       PAGE = 1
   .bss:output      : > RAMLS6_C28Data,       PAGE = 1
   .bss:cio         : > RAMLS6_C28Data,       PAGE = 1
   .data            : > RAMLS7_C28Data,       PAGE = 1
   .sysmem          : > RAMLS7_C28Data,       PAGE = 1
   .const           : > FLASH_BANK0_SEC5_8,       PAGE = 0,       ALIGN(4)
   .c28xabi.exidx	: > FLASH_BANK0_SEC5_8,       PAGE = 0,       ALIGN(4)
   .c28xabi.extab	: > FLASH_BANK0_SEC5_8,       PAGE = 0,       ALIGN(4)
   .fardata           : > FLASH_BANK0_SEC5_8,       PAGE = 0,       ALIGN(4)
#else
   .pinit           : > FLASH_BANK0_SEC1,       PAGE = 0,       ALIGN(4)
   .ebss            : >>RAMLS6_C28Data | RAMLS7_C28Data,       PAGE = 1
   .esysmem         : > RAMLS7_C28Data,       PAGE = 1
   .cio             : > RAMLS6_C28Data,       PAGE = 1
   .econst          : > FLASH_BANK0_SEC4,    PAGE = 0, ALIGN(4)
#endif

   ramgs0           : > RAMGS0,    PAGE = 1
   ramgs1           : > RAMGS1,    PAGE = 1
    
   .reset           : > RESET,     PAGE = 0, TYPE = DSECT /* not used, */
   

#if defined(__TI_EABI__)
    /* CLA specific sections */
    Cla1Prog        : LOAD = FLASH_BANK0_SEC4,
                      RUN =  RAMLS0_CLAProg,
                      LOAD_START(Cla1ProgLoadStart),
                      RUN_START(Cla1ProgRunStart),
                      LOAD_SIZE(Cla1ProgLoadSize),
                      PAGE = 0, ALIGN(4)
#else
    /* CLA specific sections */
    Cla1Prog        : LOAD = FLASH_BANK0_SEC4,
                      RUN = RAMLS0_CLAProg,
                      LOAD_START(_Cla1ProgLoadStart),
                      RUN_START(_Cla1ProgRunStart),
                      LOAD_SIZE(_Cla1ProgLoadSize),
                      PAGE = 0, ALIGN(4)
#endif
  
    
    Cla1ToCpuMsgRAM  : > CLA1_MSGRAMLOW,   PAGE = 1
    CpuToCla1MsgRAM  : > CLA1_MSGRAMHIGH,  PAGE = 1

#if defined(__TI_EABI__)
   .TI.ramfunc      : LOAD = FLASH_BANK0_SEC1,
                      RUN = RAMLS2_C28Prog
                      LOAD_START(RamfuncsLoadStart),
                      LOAD_SIZE(RamfuncsLoadSize),
                      LOAD_END(RamfuncsLoadEnd),
                      RUN_START(RamfuncsRunStart),
                      RUN_SIZE(RamfuncsRunSize),
                      RUN_END(RamfuncsRunEnd),
                      PAGE = 0, ALIGN(4)
#else
   .TI.ramfunc      : LOAD = FLASH_BANK0_SEC1,
                      RUN = RAMLS2_C28Prog
                      LOAD_START(_RamfuncsLoadStart),
                      LOAD_SIZE(_RamfuncsLoadSize),
                      LOAD_END(_RamfuncsLoadEnd),
                      RUN_START(_RamfuncsRunStart),
                      RUN_SIZE(_RamfuncsRunSize),
                      RUN_END(_RamfuncsRunEnd),
                      PAGE = 0, ALIGN(4)
#endif

   .scratchpad      : > RAMLS4_CLAData,           PAGE = 1
   .bss_cla         : > RAMLS4_CLAData,           PAGE = 1

   Cla1DataRam      : > RAMLS4_CLAData,           PAGE = 1

#if defined(__TI_EABI__)
   .const_cla      : LOAD = FLASH_BANK0_SEC2,
                      RUN = RAMLS0_CLAProg,
                      RUN_START(Cla1ConstRunStart),
                      LOAD_START(Cla1ConstLoadStart),
                      LOAD_SIZE(Cla1ConstLoadSize),
                      PAGE = 0, ALIGN(4)
#else
   .const_cla      : LOAD = FLASH_BANK0_SEC2,
                      RUN = RAMLS0_CLAProg,
                      RUN_START(_Cla1ConstRunStart),
                      LOAD_START(_Cla1ConstLoadStart),
                      LOAD_SIZE(_Cla1ConstLoadSize),
                      PAGE = 0, ALIGN(4)
#endif
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
