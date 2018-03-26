#include "lpc43xx.h"
#include "config_pin.h"

void config_pin(void){
	
	//SCU GPIO
  /*
	MODE - FUNC0 to FUNC7, 3b
	EPD - 0 disable pull-down, 1 enable
	EPUN - 0 enable pull-up, 1 disable
	EHS - 0 slow speed, 1 fast
	EZI - 0 disable input buffer, 1 enable
	ZIF - 0 enbale input glich filter, 1 disable
	*/	
	
	//LED
	LPC_SCU->SFSP9_4  |= (0x4)<<0 /*MODE*/ | (0x0)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x0)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO5[17]	LED1
	LPC_SCU->SFSP9_3  |= (0x0)<<0 /*MODE*/ | (0x0)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x0)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO4[15]	LED2
	LPC_SCU->SFSPC_11 |= (0x4)<<0 /*MODE*/ | (0x0)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x0)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO6[10]	LED3
	LPC_SCU->SFSP7_7  |= (0x0)<<0 /*MODE*/ | (0x0)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x0)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO3[15]	LED4 
	
	//IN
	LPC_SCU->SFSP5_3  |= (0x0)<<0 /*MODE*/ | (0x1)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x1)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO2[12]  
	LPC_SCU->SFSP5_4  |= (0x0)<<0 /*MODE*/ | (0x1)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x1)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO2[13]  
	LPC_SCU->SFSP5_5  |= (0x0)<<0 /*MODE*/ | (0x1)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x1)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO2[14]  
	LPC_SCU->SFSP5_6  |= (0x0)<<0 /*MODE*/ | (0x1)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x1)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO2[15]  

	//OUT
	LPC_SCU->SFSP1_7  |= (0x0)<<0 /*MODE*/ | (0x0)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x0)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO1[0]  
	LPC_SCU->SFSP1_8  |= (0x0)<<0 /*MODE*/ | (0x0)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x0)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO1[1]  
	LPC_SCU->SFSP1_9  |= (0x0)<<0 /*MODE*/ | (0x0)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x0)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO1[2]  
	LPC_SCU->SFSP1_10 |= (0x0)<<0 /*MODE*/ | (0x0)<<3 /*EPD*/ | (0x1)<<4 /*EPUN*/ | (0x1)<<5 /*EHS*/ | (0x0)<<6 /*EZI*/ | (0x1)<<7 /*ZIF*/; 	// GPIO1[3]  

	// direction, 1 out, 0 in
	LPC_GPIO_PORT->DIR[5] |= 1<<17 ;		//pin17 port5 je izlazni
	LPC_GPIO_PORT->DIR[4] |= 1<<15 ;
	LPC_GPIO_PORT->DIR[6] |= 1<<10 ;
	LPC_GPIO_PORT->DIR[3] |= 1<<15 ;
	
	LPC_GPIO_PORT->DIR[2] &= ~(1<<12);	//pin12 port2 je ulazni
	LPC_GPIO_PORT->DIR[2] &= ~(1<<13);
	LPC_GPIO_PORT->DIR[2] &= ~(1<<14);
	LPC_GPIO_PORT->DIR[2] &= ~(1<<15);
	
	LPC_GPIO_PORT->DIR[1] |= 1<<0 ;			//pin0 port1 je izlazni
	LPC_GPIO_PORT->DIR[1] |= 1<<1 ;
	LPC_GPIO_PORT->DIR[1] |= 1<<2 ;
	LPC_GPIO_PORT->DIR[1] |= 1<<3 ;
}
