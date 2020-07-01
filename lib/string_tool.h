/**************************************************************************
*                                                                         *
*   PROJECT     : ARM port for UCOS-II                                    *
*                                                                         *
*   MODULE      : STRING_TOOL.h                                           *
*                                                                         *
*	AUTHOR		: HanRunyu												  *
*				  URL  : http://github.com/HanRunyu 					  *
*																		  *
*	PROCESSOR	: s3c2440  (32 bit ARM920T RISC core from Samsung)		  *
*																		  *
*   TOOLCHAIN   : gcc version 8.3.0 (crosstool-NG 1.24.0)                 *
*                                                                         *
*   DESCRIPTION :                                                         *
*   String tools.                                                         *
*                                                                         *
**************************************************************************/



#include "def.h"

U32 strlen(const S8 *s);
U32 strnlen(const S8 * s, U32 count);
S32 atoi(const S8 *str);
S8 *itoa(U32 i);
