/************************************/
/*  Author 	   : Ebrahim Mostafa	*/
/*	SWC		   : PRIVATE            */
/*  Layer 	   : MCAL				*/
/*  Date	   : sep. 9		2023	*/
/*  version    : 1.1				*/
/*  Last Edit  : sep. 16	2023	*/
/************************************/



#ifndef _MDIO_PRIVATE_H
#define _MDIO_PRIVATE_H

typedef struct {
    const u8 PIN;
    u8       DDR;
    u8       PORT;
}GPIO_t;

#define GPIOA ((volatile GPIO_t*)0x39)
#define GPIOB ((volatile GPIO_t*)0x36)
#define GPIOC ((volatile GPIO_t*)0x33)
#define GPIOD ((volatile GPIO_t*)0x30)

#endif // _MDIO_PRIVATE_H
