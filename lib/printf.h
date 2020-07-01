/**************************************************************************
*                                                                         *
*   PROJECT     : ARM port for UCOS-II                                    *
*                                                                         *
*   MODULE      : PRINTF.h                                                *
*                                                                         *
*	AUTHOR		: HanRunyu												  *
*				  URL  : http://github.com/HanRunyu 					  *
*																		  *
*	PROCESSOR	: s3c2440  (32 bit ARM920T RISC core from Samsung)		  *
*																		  *
*	TOOLCHAIN	: gcc version 8.3.0 (crosstool-NG 1.24.0)				  *
*                                                                         *
*   DESCRIPTION :                                                         *
*   printf function group.                                                *
*                                                                         *
**************************************************************************/



#include "stdarg.h"

#define CONFIG_SYS_PBSIZE		1024

/* ********************************************************************* */
/* Interface function definition */

int vsnprintf(char *buf, U32 size, const char *fmt, va_list args);
int vscnprintf(char *buf, U32 size, const char *fmt, va_list args);
int snprintf(char *buf, U32 size, const char *fmt, ...);
int scnprintf(char *buf, U32 size, const char *fmt, ...);
int vsprintf(char *buf, const char *fmt, va_list args);
int sprintf(char *buf, const char *fmt, ...);
int printf(const char *fmt, ...);
int vprintf(const char *fmt, va_list args);
