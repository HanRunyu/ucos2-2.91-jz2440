/**************************************************************************
*                                                                         *
*   PROJECT     : ARM port for UCOS-II                                    *
*                                                                         *
*   MODULE      : DEF.h                                                   *
*                                                                         *
*   AUTHOR      : HanRunyu                                                *
*                 URL  : http://github.com/HanRunyu                       *
*                                                                         *
*   PROCESSOR   : s3c2440  (32 bit ARM920T RISC core from Samsung)        *
*                                                                         *
*   TOOLCHAIN   : ANY								                      *
*                                                                         *
*   DESCRIPTION :                                                         *
*   Common data type definition header file.                              *
*                                                                         *
**************************************************************************/



#ifndef __DEF_H__
#define __DEF_H__

#ifdef __cplusplus
extern "C" {
#endif


/* ********************************************************************* */
/* Interface macro & data definition */

#define	U64 unsigned long long
#define S64 long long 
#define U32 unsigned int
#define S32 int
#define U16 unsigned short
#define S16 short int
#define U8  unsigned char
#define S8  char

#define False 0
#define True !False

/* Sets the result on bPort */
#define BIT_SET(bPort,bBitMask)        (bPort |= bBitMask)
#define BIT_CLR(bPort,bBitMask)        (bPort &= ~bBitMask)

/* Returns the result */
#define GET_BIT_SET(bPort,bBitMask)    (bPort | bBitMask)
#define GET_BIT_CLR(bPort,bBitMask)    (bPort & ~bBitMask)

/* Returns 0 if the condition is False & a non-zero value if it is True */
#define TEST_BIT_SET(bPort,bBitMask)   (bPort & bBitMask)
#define TEST_BIT_CLR(bPort,bBitMask)   ((~bPort) & bBitMask)


/* ********************************************************************* */

#ifdef __cplusplus
}
#endif

#endif /*__DEF_H__*/
