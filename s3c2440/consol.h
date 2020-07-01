/**************************************************************************
*                                                                         *
*   PROJECT     : ARM port for UCOS-II                                    *
*                                                                         *
*   MODULE      : CONSOL.h                                                *
*                                                                         *
*   AUTHOR      : HanRunyu                                                *
*                 URL  : http://github.com/HanRunyu                       *
*                                                                         *
*   PROCESSOR   : s3c2440  (32 bit ARM920T RISC core from Samsung)        *
*                                                                         *
*   TOOLCHAIN   : gcc version 8.3.0 (crosstool-NG 1.24.0)                 *
*                                                                         *
*   DESCRIPTION :                                                         *
*   External interface for CONSOL.                                        *
**************************************************************************/



#ifndef __CONSOL_H__
#define __CONSOL_H__

#ifdef __cplusplus
extern "C" {
#endif


/* ********************************************************************* */
/* Interface function definition */

/*
*********************************************************************************************
*                                       CONSOL_Select
*
* Description: This routine selects the consol port for active usage.
*
* Arguments  : wCh - UART channel number.
*                    1 - UART1.
*                    2 - UART2.
*
* Return     : none.
*
* Note(s)    : 
*********************************************************************************************
*/
void CONSOL_Select(S8 ch);

/*
*********************************************************************************************
*                                       CONSOL_Init
*
* Description: This routine initializes the consol port by setting its baud rate & FIFO
*              buffer.
*
* Arguments  : wBaud     - Baud Rate in bit/sec.
*              bFifoFlag - FIFO 
*                          True  - FIFO enabled.
*                          False - FIFO disabled.
*
* Return     : none.
*
* Note(s)    : Before calling this, CONSOL_Select needs to be called for selecting the consol
*              port.
*********************************************************************************************
*/
void CONSOL_Init(U32 wBaud);

/*
*********************************************************************************************
*                                       CONSOL_GetCh
*
* Description: This routine waits for a character from the CONSOL port & returns it.
*
* Arguments  : none.
*
* Return     : Returns the character read from the consol port.
*
* Note(s)    : 
*********************************************************************************************
*/
S8 CONSOL_GetCh(void);

/*
*********************************************************************************************
*                                       CONSOL_GetChar
*
* Description: This routine reads a character from the consol port if available.
*
* Arguments  : pbData - Pointer to return the received data.
*
* Return     : The status of the RX buffer.
*              True  - Data returned is valid.
*              False - Data returned is invalid.
*
* Note(s)    : 
*********************************************************************************************
*/
S8 CONSOL_GetChar(S8 *pbData);

/*
*********************************************************************************************
*                                       CONSOL_GetString
*
* Description: This routine waits for a string from the CONSOL port & returns it.
*
* Arguments  : pbString - Pointer to return the received string.
*
* Return     : none.
*
* Note(s)    : 
*********************************************************************************************
*/
void CONSOL_GetString(S8 *pbString);

/*
*********************************************************************************************
*                                       CONSOL_GetIntNum
*
* Description: This routine waits for a Integer from the CONSOL port & returns it.
*
* Arguments  : none.
*
* Return     : Returns the received Integer value.
*
* Note(s)    : 
*********************************************************************************************
*/
S32 CONSOL_GetIntNum(void);

/*
*********************************************************************************************
*                                       CONSOL_SendCh
*
* Description: This routine waits till the character is sent. It also sends an extra carriage
*              return character when sending a new line character
*
* Arguments  : bData - Data to be sent.
*
* Return     : none.
*
* Note(s)    : 
*********************************************************************************************
*/
void CONSOL_SendCh(S8 bData);

/*
*********************************************************************************************
*                                       CONSOL_SendChar
*
* Description: This routine waits till the character is sent.
*
* Arguments  : bData - Data to be sent.
*
* Return     : none.
*
* Note(s)    : 
*********************************************************************************************
*/
void CONSOL_SendChar(S8 bData);

/*
*********************************************************************************************
*                                       CONSOL_SendString
*
* Description: This routine waits till the string is sent.
*
* Arguments  : pbString - String to be sent.
*
* Return     : none.
*
* Note(s)    : 
*********************************************************************************************
*/
void CONSOL_SendString(S8 *pbString);

/*
*********************************************************************************************
*                                       CONSOL_Scanf
*
* Description: Reads input from the consol stream, under control of the string pointed to by
*              format that specifies the admissible input sequences and how they are to be
*              converted for assignment, using subsequent arguments as pointers to the
*              objects to receive the converted input. If there are insufficient arguments
*              for the format, the behavior is undefined. If the format is exhausted while
*              arguments remain, the excess arguments are ignored.
*
* Arguments  : pcFmt - Format string. It can contain only the following format specifiers:
*                      %s - String.
*                      %c - character.
*                      %i - Integer.
*              ...   - Are the passed parameters (pointers to the objects to receive the
*                      converted input).
*
* Return     : none.
*
* Note(s)    : 
*********************************************************************************************
*/
void CONSOL_Scanf(S8 *pcFmt,...);

/*
*********************************************************************************************
*                                       CONSOL_Printf
*
* Description: Writes output to the consol stream, under control of the string pointed to by
*              format that specifies how subsequent arguments are converted for output. If 
*              there are insufficient arguments for the format, the behavior is undefined.
*              If the format is exhausted while arguments remain, the excess arguments are
*              ignored.
*
* Arguments  : pcFmt - Format string. It can contain all the format specifies.
*              ...   - Are the passed parameters (pointers to the objects to receive the
*                      converted input).
*
* Return     : none.
*
* Note(s)    : 
*********************************************************************************************
*/
void CONSOL_Printf(S8 *pcFmt,...);


/* ********************************************************************* */

#ifdef __cplusplus
}
#endif

#endif /*__CONSOL_H__*/
