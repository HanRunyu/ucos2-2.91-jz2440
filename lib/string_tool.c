/**************************************************************************
*                                                                         *
*   PROJECT     : ARM port for UCOS-II                                    *
*                                                                         *
*   MODULE      : STRING_TOOL.c                                           *
*                                                                         *
*	AUTHOR		: HanRunyu												  *
*				  URL  : http://github.com/HanRunyu 					  *
*																		  *
*	PROCESSOR	: s3c2440  (32 bit ARM920T RISC core from Samsung)		  *
*																		  *
*	TOOLCHAIN	: arm-linux-gnueabi-gcc(Linaro 7.5.0)					  *
*                                                                         *
*   DESCRIPTION :                                                         *
*   String tools.                                                         *
*                                                                         *
**************************************************************************/



#include "def.h"

#define NULL	0

U32 strlen(const S8 *s)
{
    const S8 *sc;
	
    for(sc = s; *sc != '\0'; ++sc);
    return (sc - s);
}

U32 strnlen(const S8 *s, U32 count)
{
	const S8 *sc;

	for (sc = s; count-- && *sc != '\0'; ++sc);
	return (sc - s);
}

S32 atoi(const S8 *str)
{	
	S32 flag = 1;	
	S32 result = 0;		
	
	if(str == NULL)		
		return 0;

	while(*str == ' ' || *str == '\t')
		str++;	
	
	if(*str == '+' || *str == '-')
	{
		if(*str == '-')
			flag = -1;               
		str++;        
	}
	
	while(*str != '\0')	
	{		
		if(*str >= 0 && *str <= '9')		
			result = result*10 + (*str - '0');			
		else
			break;
		str++;	
	}		
	
	return result * flag;
}

S8 *itoa(U32 i)
{
	/* 21 digits plus null terminator, good for 64-bit or smaller ints */
	static S8 local[22];
	S8 *p = &local[21];

	*p-- = '\0';
	do {
		*p-- = '0' + i % 10;
		i /= 10;
	} while (i > 0);
	return p + 1;
}

