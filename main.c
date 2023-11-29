/*
 * 			main.c
 *
 *  Created on: Nov 27, 2023
 *  Author: Ebrahim mostafa
 */
#include "lBIT_math.h"
#include "lSTD_types.h"

#include <util/delay.h>
#include "MDIO_interface.h"
#include "MGIE_interface.h"
#include "MEXTI_interface.h"
#include "MTIM_interface.h"

#define PORTA  *((volatile u8*)0x3B)
#define PORTB  *((volatile u8*)0x38)
#define PORTC  *((volatile u8*)0x35)
#define PORTD  *((volatile u8*)0x32)

void GISR (void);
void EISR1 (void);
void EISR2 (void);
void EISR3(void);
void display_7seg(void);

u8 sec1=0,sec2=0,counter=0, min1=0,min2=0,hour1=0,hour2=0;
int main(void)
{
	MDIO_voidSetPortDirection(MDIO_PORTA,0xff);
	MDIO_voidSetPortDirection(MDIO_PORTC,0xff);

	MDIO_voidSetPortValue(MDIO_PORTA,0x00);
	MDIO_voidSetPortValue(MDIO_PORTC,0x00);

	MDIO_voidSetPinDirection(MDIO_PORTD,2,MDIO_INPUT_PULLUP);
	MDIO_voidSetPinDirection(MDIO_PORTD,3,MDIO_INPUT_PULLUP);
	MDIO_voidSetPinDirection(MDIO_PORTB,2,MDIO_INPUT_PULLUP);

	MGIE_voidEnableGI();
	MEXTI_voidInit(MEXTI_INT0,MEXTI_MODE_FALLING);
	MEXTI_voidInit(MEXTI_INT1,MEXTI_MODE_FALLING);
	MEXTI_voidInit(MEXTI_INT2,MEXTI_MODE_FALLING);

	MEXTI_voidEnableInterrupt(MEXTI_INT0);
	MEXTI_voidEnableInterrupt(MEXTI_INT1);
	MEXTI_voidEnableInterrupt(MEXTI_INT2);

		// Initialize Timer0 with the desired settings
	    MTIM_voidInit(MTIM_TIMER0, MTIM_MODE_NORMAL, MTIM_CS_PRESCALER_1024, MTIM_HWPIN_NONINVERTING_PWM);

	    // Enable the Timer0 Overflow interrupt
	    MTIM_voidEnableInterrupt(MTIM_INTERRUPT_T0_OVF);

	    // Start Timer0
	    MTIM_voidStartTimer(MTIM_TIMER0);

	    // Call MTIM_voidTimerDelay with the desired delay (1 second)
	    MTIM_voidTimerDelay(MTIM_TIMER0, 770);

	    // Set the callback function to be executed on Timer0 Overflow
	    MTIM_voidSetCallback(GISR, MTIM_INTERRUPT_T0_OVF);

		MEXTI_voidSetCallback(EISR1,MEXTI_INT0);
		MEXTI_voidSetCallback(EISR2,MEXTI_INT1);
		MEXTI_voidSetCallback(EISR3,MEXTI_INT2);

	while(1)
	{
		display_7seg();
	}

	return 0;
}
void GISR()
{
	sec1++;
	if(sec1==10)
	{
		sec1=0;
		sec2++;
		if(sec2==6 && sec1==0)
		{
			sec2=0;
			min1++;
		}
	}
	if(min1==10)
	{
		min1=0;
		min2++;
		if(min2==6 && min1==0)
		{
			min2=0;
			hour1++;
		}
	}
	if(hour1==10)
	{
		hour1=0;
		hour2++;
		if(hour2==2&&hour1==4)
		{
			hour1=0;
			hour2=0;
		}
	}
}

void EISR1 (void)
{
		MTIM_voidResetTimer(MTIM_TIMER0);
		sec1=0;
		sec2=0;
		min1=0;
		min2=0;
		hour1=0;
		hour2=0;
}
void EISR2 (void)
{
		MTIM_voidStopTimer(MTIM_TIMER0);
}
void EISR3(void)
{
		MTIM_voidStartTimer(MTIM_TIMER0);
}

void display_7seg(void){

	/* enable PA0 7 seg to display  sec1 */
	PORTA = (PORTA & 0xC0) | (1<<0);
	/*then display sec1 on decoder */
	PORTC = (PORTC & 0xF0) | (sec1 & 0x0F);

	/* delay 3 mili */
	_delay_ms(3);

	/* enable PA1 7 seg to display  sec2 */
	PORTA = (PORTA & 0xC0) | (1<<1);
	/*then display sec2 on decoder */
	PORTC = (PORTC & 0xF0) | (sec2 & 0x0F);

	_delay_ms(3);

	/* enable PA2 7 seg to display  min1 */
	PORTA = (PORTA & 0xC0) | (1<<2);
	/*then display min1 on decoder */
	PORTC = (PORTC & 0xF0) | (min1 & 0x0F);

	_delay_ms(3);

	/* enable PA3 7 seg to display  min2 */
	PORTA = (PORTA & 0xC0) | (1<<3);
	/*then display min2 on decoder */
	PORTC = (PORTC & 0xF0) | (min2 & 0x0F);

	_delay_ms(3);

	/* enable PA4 7 seg to display  hour1 */
	PORTA = (PORTA & 0xC0) | (1<<4);
	/*then display hour1 on decoder */
	PORTC = (PORTC & 0xF0) | (hour1 & 0x0F);

	_delay_ms(3);

	/* enable PA5 7 seg to display  hour2 */
	PORTA = (PORTA & 0xC0) | (1<<5);
	/*then display hour2 on decoder */
	PORTC = (PORTC & 0xF0) | (hour2 & 0x0F);

	_delay_ms(3);
}
