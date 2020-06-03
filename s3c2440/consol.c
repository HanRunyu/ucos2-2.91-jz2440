/**************************************************************************
*                                                                         *
*   PROJECT     : ARM port for UCOS-II                                    *
*                                                                         *
*   MODULE      : CONSOL.c                                                *
*                                                                         *
*   AUTHOR      : HanRunyu                                                *
*                 URL  : http://github.com/HanRunyu                       *
*                                                                         *
*   PROCESSOR   : s3c2440  (32 bit ARM920T RISC core from Samsung)        *
*                                                                         *
*   TOOLCHAIN   : arm-linux-gnueabi-gcc(Linaro 7.5.0)                     *
*                                                                         *
*   DESCRIPTION :                                                         *
*   This is the CONSOL Driver module. Supports multiple RS232 console     *
*   interfaces.                                                           *
*                                                                         *
**************************************************************************/



#include "def.h"
#include "s3c2440.h"
#include "consol.h"
#include "printf.h"
#include "string_tool.h"

#include <stdarg.h>


/* ********************************************************************* */
/* File local definitions */

static S8 __wChannel = 0;

#define __isalpha(c) (c >'9')
#define __isupper(c) !(c & 0x20)


/* ********************************************************************* */
/* Global functions */

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

void CONSOL_Select(S8 wCh)
{
	__wChannel = wCh;
}

/*
*********************************************************************************************
*                                       CONSOL_Init
*
* Description: This routine initializes the consol port by setting its baud rate & FIFO
*              buffer.
*
* Arguments  : wBaud     - Baud Rate in bit/sec.
*
* Return     : none.
*
* Note(s)    : Before calling this, CONSOL_Select needs to be called for selecting the consol
*              port.
*********************************************************************************************
*/

void CONSOL_Init(U32 wBaud)
{
	switch(__wChannel)
	{
		case 0:
			rUFCON0 = (3<<6) | (3<<4) | (1<<2) | (1<<1) | (1<<0);   // UART channel 0 FIFO control register
            rUMCON0 = 0;
            rULCON0 = 0x3;   // Line control register : Normal,No parity,1 stop,8 bits
            rUCON0  = 0x245; // Control register
            rUBRDIV0=((U32)(PCLK/16.0/wBaud+0.5) - 1);   // Baud rate divisior register 0
            break;
        case 1:
            rUFCON1 = (3<<6) | (3<<4) | (1<<2) | (1<<1) | (1<<0);   // UART channel 1 FIFO control register
            rUMCON1 = 0;
            rULCON1 = 0x3;   // Line control register : Normal,No parity,1 stop,8 bits
            rUCON1  = 0x245; // Control register
            rUBRDIV1=((U32)(PCLK/16.0/wBaud+0.5) - 1);   // Baud rate divisior register 0
            break;
        case 2:
            rUFCON2 = (3<<6) | (3<<4) | (1<<2) | (1<<1) | (1<<0);   // UART channel 2 FIFO control register
			rUMCON2 = 0;
			rULCON2 = 0x3;   // Line control register : Normal,No parity,1 stop,8 bits
            rUCON2  = 0x245; // Control register
            rUBRDIV2=((U32)(PCLK/16.0/wBaud+0.5) - 1);   // Baud rate divisior register 0
            break;
	}
}

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

S8 CONSOL_GetCh(void)
{
    switch(__wChannel)
    {
    	case 0:
            while(!(rUFSTAT0 & 0x0f)); //Receive data ready
            return rURXH0;

    	case 1:
            while(!(rUFSTAT1 & 0x0f)); //Receive data ready
            return rURXH1;

    	case 2:
            while(!(rUFSTAT2 & 0x0f)); //Receive data ready
            return rURXH2;
    }
	return rURXH0;
}

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

S8 CONSOL_GetChar(S8 *pbData)
{
	switch(__wChannel)
	{
        case 0:
			if(rUFSTAT0 & 0x0f)
            {
				*pbData = rURXH0;
				return True;
            }
            return False;
        case 1:
            if(rUFSTAT1 & 0x0f)
            {
				*pbData = rURXH1;
				return True;
            }
            return False;
        case 2:
           	if(rUFSTAT2 & 0x0f)
            {
				*pbData = rURXH2;
				return True;
            }
            return False;
	}
	return False;
}

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

void CONSOL_GetString(S8 *pbString)
{
	S8 *pbString2=pbString;
	S8 bC;

    while((bC=CONSOL_GetCh())!='\r')
    {
		if(bC=='\b')
		{
			if((U32)pbString2<(U32)pbString)
			{
				CONSOL_Printf("\b \b");
				pbString--;
			}
        }
        else
        {
			*pbString++=bC;
			CONSOL_SendCh(bC);
        }
    }
    *pbString='\0';
    CONSOL_SendCh('\n');
}

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

S32 CONSOL_GetIntNum(void)
{
	S8 	abStr[30];
    S8 	*pbString=abStr;
    U32 wBase=10;
    U32 wMinus=0;
    U32 wLastIndex;
    S32 wResult=0;
    U32 wI;
    
    CONSOL_GetString(pbString);
    
    if(pbString[0]=='-'){wMinus=1;pbString++;}
    
    if(pbString[0]=='0' && (pbString[1]=='x' || pbString[1]=='X'))
    {
		wBase=16;
		pbString+=2;
    }
    
    wLastIndex=strlen(pbString)-1;
    if( pbString[wLastIndex]=='h' || pbString[wLastIndex]=='H' )
    {
		wBase=16;
		pbString[wLastIndex]=0;
		wLastIndex--;
    }

    if(wBase==10)
    {
		wResult=atoi(pbString);
		wResult=wMinus ? (-1*wResult):wResult;
    }
    else
    {
		for(wI=0; wI<=wLastIndex; wI++)
        {
			if(__isalpha(pbString[wI]))
            {
				if(__isupper(pbString[wI]))
					wResult=(wResult<<4)+pbString[wI]-'A'+10;
                else
					wResult=(wResult<<4)+pbString[wI]-'a'+10;
            }
            else
            {
				wResult=(wResult<<4)+pbString[wI]-'0';
            }
        }
        wResult=wMinus ? (-1*wResult):wResult;
    }
    return wResult;
}

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

void CONSOL_SendChar(S8 bData)
{
	switch(__wChannel)
    {
    	case 0:
            while(rUFSTAT0 & 0x200); //Wait until THR is empty.
            rUTXH0 = bData;
            break;

    	case 1:
            while(rUFSTAT1 & 0x200); //Wait until THR is empty.
            rUTXH1 = bData;
            break;

    	case 2:
            while(rUFSTAT2 & 0x200); //Wait until THR is empty.
            rUTXH2 = bData;
            break;
    }        
}

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

void CONSOL_SendCh(S8 bData)
{
	if(bData == '\n')
	{
		CONSOL_SendChar('\r');
	}

	CONSOL_SendChar(bData);
}

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

void CONSOL_SendString(S8 *pbString)
{
	while(*pbString)
		CONSOL_SendCh(*pbString++);
}

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

void CONSOL_Scanf(S8 *pcFmt,...)
{
	va_list pArg;
    S8 cChar;
    S32 *pwInt;
    S8 *pbChar;
    
    va_start(pArg, pcFmt);
    while((cChar=*pcFmt++) != '\0')
    {
		if(cChar != '%')continue;
        switch(*pcFmt)
        {
			case 's':
            case 'S':
				pbChar = va_arg (pArg, S8 *);
                CONSOL_GetString(pbChar);
                break;
            case 'i':
            case 'I':
				pwInt = va_arg (pArg, S32 *);
				*pwInt = CONSOL_GetIntNum();
				break;
            case 'c':
            case 'C':
				pbChar = va_arg (pArg, S8 *);
				*pbChar = CONSOL_GetCh();
				break;
        }
    }
    va_end(pArg);
}

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

void CONSOL_Printf(S8 *pcFmt,...)
{
	va_list ap;
    S8 pbString[CONFIG_SYS_PBSIZE];

    va_start(ap,pcFmt);
    vsprintf(pbString,pcFmt,ap);
    CONSOL_SendString(pbString);
    va_end(ap);
}


/* ********************************************************************* */
