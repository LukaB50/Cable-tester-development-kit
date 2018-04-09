#include "LPC43xx.h"
#include "timers.h"
#include "config_pin.h"
#include <stdbool.h>

#define MAXRED 4
#define MAXSTUPAC	16
#define MAXPINS 16

#define LED1 		LPC_GPIO_PORT->B[5*32+17]
#define LED2 		LPC_GPIO_PORT->B[4*32+15]
#define LED3 		LPC_GPIO_PORT->B[6*32+10]
#define LED4 		LPC_GPIO_PORT->B[3*32+15]

#define IN1			LPC_GPIO_PORT->B[2*32+12]		//P5_3
#define IN2 		LPC_GPIO_PORT->B[2*32+13]		//P5_4
#define IN3 		LPC_GPIO_PORT->B[2*32+14]		//P5_5
#define IN4 		LPC_GPIO_PORT->B[2*32+15]		//P5_6

#define OUT1		LPC_GPIO_PORT->B[1*32+0]		//P1_7
#define OUT2 		LPC_GPIO_PORT->B[1*32+1]		//P1_8
#define OUT3 		LPC_GPIO_PORT->B[1*32+2]		//P1_9
#define OUT4 		LPC_GPIO_PORT->B[1*32+3]		//P1_10

void GPIO0_IRQHandler(void){					//naziv prekida pise u startup.s
	LPC_GPIO_PIN_INT->FALL |= (1<<0);		//clear falling detection
	
	//prekidni potp.
	
	LPC_GPIO_PIN_INT->SIENF |= (0<<0);	//enable falling detection
	return;
}

void read_inputs(int aktivni_pin, bool *p){
	int i;
	i=0;
	
	for(i=0;i<MAXPINS;i++)
		*(p+aktivni_pin*MAXPINS+i)=LPC_GPIO_PORT->B[2*32+i];		//citaj input od gpio2,12 nadalje, Pretp: ako su svi pinovi u istom portu2
	return;
}

void greska (int pin){
	switch(pin+1){
		case 1:	LED1=1; break;
		case 2: LED2=1; break;
		case 3: LED3=1; break;
		case 4: LED4=1; break;
		
		default: break;
	}
}

//UART
void uart_init(void){
	
	LPC_UART1->FCR |= 0x07;		// rx & tx buffer reset
	LPC_UART1->LCR |= 0x83;		//8bit character, 1 stop bit, DLAB enabled
	LPC_UART1->FDR |= 0x10;		//Set Multiple=1 & Divisor=0
	LPC_UART1->DLL &= 0x0;		//set DLL to zero
	LPC_UART1->DLL |= 0x30;		//DLL=48
	LPC_UART1->DLM |= 0x5;		//DLM=5
	LPC_UART1->LCR &= ~(1<<7);	//clear DLAB
	
	//prepare NVIC for uart interupts
	
	//enable uart interrupts
	
}

void uart_sendChar(char ch){
	while(!(LPC_UART1->LSR & 0x20));
		LPC_UART1->THR=ch;
}
// MAIN: Test 4pina u istom portu, prvo ocitanje je ispravno, ostala se usporedjuju s njim, pale se ledice kad postoji razlika
//				pale se poznata 4 pina koja su definirani kao izlazni, a provjerava se 16pinova u portu2
int main()
{
	int i,j;
	
	bool ispravan_pinout[MAXRED][MAXSTUPAC]={false};
	bool *ispravan;
	bool ocitani_pinout[MAXRED][MAXSTUPAC]={false};
	bool *ocitani;
	
	i=j=0;
	ispravan=&ispravan_pinout[0][0];
	ocitani=&ocitani_pinout[0][0];
	
	config_pin();
	timers_init();
	uart_init();
	
	// interrupt
//	LPC_SCU->PINTSEL0 |= (0x3)<<0 | (0x6)<<5;	//Gpio6[3] je odabran za interrupt0
//	LPC_GPIO_PIN_INT->ISEL |= (0<<0);					//1=low level sensitive, 0=edge sesititve; interrupt0 u PINTSEL0 registru
//	LPC_GPIO_PIN_INT->IENF |= (1<<0);					//enable interrupt on falling edge
//	NVIC_ClearPendingIRQ(PIN_INT0_IRQn);			//brise pending da ne bi nakon Enable-a odmah usao u prekid ako je slucajno pending postavljen
//	NVIC_SetPriority(PIN_INT0_IRQn, 2);				//priority moraju biti parni brojevi, 0 najjaci
//	NVIC_EnableIRQ(PIN_INT0_IRQn);
	
	
	//nadji ispravni pinout, postavlja samo izlazne pinove u 1 ili 0
	for(i=0;i<MAXRED;i++){
		LPC_GPIO_PORT->B[1*32+(i+0)]=true;
		read_inputs(i,ispravan);
		LPC_GPIO_PORT->B[1*32+(i+0)]=false;
	}
	
	while(1){
		
		uart_sendChar('a');
		ms_delay(500);
		uart_sendChar('b');
		ms_delay(500);
		uart_sendChar('c');
		ms_delay(500);
		
	}
}
