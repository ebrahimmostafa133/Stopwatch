/************************************/
/*  Author 	   : Ebrahim Mostafa	*/
/*	SWC		   : Global Interrupt 	*/
/*  Layer 	   : MCAL				*/
/*  Date	   : Oct. 23	2023	*/
/*  version    : 1.0				*/
/*  Last Edit  : N/A 				*/
/************************************/

#include "lSTD_types.h"
#include "lBIT_math.h"

#include "MGIE_private.h"
#include "MGIE_interface.h"

void MGIE_voidEnableGI(void)
{
	SET_BIT(SREG,I);
}

void MGIE_voidDisableGI(void)
{
	CLEAR_BIT(SREG,I);
}