/**************************************************************************
*                                                                         *
*   PROJECT     : ARM port for UCOS-II                                    *
*                                                                         *
*   MODULE      : RELOCATE.c                                              *
*                                                                         *
*	AUTHOR		: HanRunyu												  *
*				  URL  : http://github.com/HanRunyu 					  *
*																		  *
*	PROCESSOR	: s3c2440  (32 bit ARM920T RISC core from Samsung)		  *
*																		  *
*   TOOLCHAIN   : gcc version 8.3.0 (crosstool-NG 1.24.0)                 *
*                                                                         *
*   DESCRIPTION :                                                         *
*   Nand flash driver and code copy and bss segment clearing program.     *
*                                                                         *
**************************************************************************/



#include "def.h"


void nand_init(void);
void nand_read(U32 addr, S8 *buf, U32 len);

U32 isBootFromNorFlash(void);

void copy2sdram(void);
void clean_bss(void);
