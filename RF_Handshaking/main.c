/*
===============================================================================
 Name        : RF_Handshaking.c
 Description : RF and PWM code for LPC1769

 CTI One Corporation released for Dr. Harry Li for CMPE 245 Class use ONLY!
===============================================================================
*/


#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>
#include <stdbool.h>
#include "LoRa.h"
#include"common.h"

#define RF_Receive 1
#define TransmittACk 0
#define ack_start_stop 0
int rfInit(void);

char receiveData=0;
int packetSize;



/**************************************************************************************************
* @brief	wait for ms amount of milliseconds
* @param	ms : Time to wait in milliseconds
**************************************************************************************************/
static void delay_ms(unsigned int ms)
{
    unsigned int i,j;
    for(i=0;i<ms;i++)
        for(j=0;j<50000;j++);
}

/**************************************************************************************************
* @brief	wait for delayInMs amount of milliseconds
* @param	delayInMs : Time to wait in milliseconds
**************************************************************************************************/
static void delay(uint32_t delayInMs)
{
	LPC_TIM0->TCR = 0x02;		/* reset timer */
	LPC_TIM0->PR  = 0x00;		/* set prescaler to zero */
	LPC_TIM0->MR0 = delayInMs * (9000000 / 1000-1);
	LPC_TIM0->IR  = 0xff;		/* reset all interrrupts */
	LPC_TIM0->MCR = 0x04;		/* stop timer on match */
	LPC_TIM0->TCR = 0x01;		/* start timer */

	/* wait until delay time has elapsed */
	while (LPC_TIM0->TCR & 0x01);
}

#define MZ 1000000
/**************************************************************************************************
* main : Main program entry
**************************************************************************************************/
int main(void)
{
	int loraFreq = 0;
	int txPower = 0;
	int Spread_factor = 0;

	printf("System clock is %d\n",SystemCoreClock);
	int counter =0;

	printf("\n\nPlease Enter Lora Freq rate(724 MHz to 1040): \n");
    scanf("%ld",&loraFreq);

	printf("\n\nPlease Enter Tx Power(2-17): \n");
    scanf("%d",&txPower);

	printf("\n\nPlease Enter Spreading factor(6-12): \n");
    scanf("%d",&Spread_factor);

    LoRabegin(loraFreq*MZ,txPower,Spread_factor);

	/* If all is well we will never reach here as the scheduler will now be
	running.  If we do reach here then it is likely that there was insufficient
	heap available for the idle task to be created. */
#if RF_Receive
	while(1)
	{

		packetSize = parsePacket(0);
		if (packetSize)
		{
			counter = 0;
			//received a packet
			printf("Received packet '");
			// read packet
			while (available())
			{
				counter = 0;
				receiveData = read();
				printf("%c",receiveData);
				if(receiveData == 'A')
				{
					printf("Received packet '");
					printf("%c",receiveData);
					printf("' with RSSI ");
					printf("%d\n",packetRssi());
				}
				else if(receiveData == 'B')
				{
					printf("Received packet '");
					printf("%c",receiveData);
					printf("' with RSSI ");
					printf("%d\n",packetRssi());
				}
				else if(receiveData == 'C')
				{
					printf("Received packet '");
					printf("%c",receiveData);
					printf("' with RSSI ");
					printf("%d\n",packetRssi());
				}
				else if(receiveData == 'D')
				{
					printf("Received packet '");
					printf("%c",receiveData);
					printf("' with RSSI ");
					printf("%d\n",packetRssi());
				}
				else if(receiveData == 'E')
				{
					printf("Received packet '");
					printf("%c",receiveData);
					printf("' with RSSI ");
					printf("%d\n",packetRssi());
				}
				else if(receiveData == 'F')
				{
					printf("Received packet '");
					printf("%c",receiveData);
					printf("' with RSSI ");
					printf("%d\n",packetRssi());
				}


			}

		}

	}
#endif


#if TransmittACk
	const char buffer[] = "LORA LAB Begin!";
	char Acknowledgement;
	Acknowledgement = 'A';
	while(1)
	{
		printf("Start Sending data \n");
		delay_ms(1000);
		LoRabeginPacket(0);
		//writebyte(Acknowledgement);
		write(buffer, sizeof(buffer));
		LoRaendPacket();
		printf("Data sent \n");

	}

#endif

}

void check_ack()
{
	printf("1 \n");
}

