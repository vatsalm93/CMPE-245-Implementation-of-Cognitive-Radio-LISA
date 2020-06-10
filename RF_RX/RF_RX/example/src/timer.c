/*
 * @brief Blinky example using timers
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include <cr_section_macros.h>
#include "board.h"
#include <stdio.h>
#include <math.h>
#include "syncField.h"
#include "myLisa.h"
#include <string.h>
#include <stdbool.h>

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
#define TICKRATE_HZ1 				(11)	/* 11 ticks per second */

#define DATA_TX_RX_PORT	0
#define TX_PIN		2
#define RX_PIN 		3

#define GREEN_LED_PORT	3
#define GREEN_LED_PIN	25

char sync_field[SYNC_FIELD_BYTES] = {0};
char data_sync_bits[SYNC_BITS] = {0};
char data_in_bits[1024] = {0};
char rx_buff[1024] = {0};

unsigned int oversampling_count = 0;
unsigned int bit_count = 0;
int sum = 0;
bool process_data = false;
static int flag, sampling_rate=100, oversampling_rate = 1;


/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/
int tx_bit_index = 0;
int start_tx = 0;
bool start_bit = false;

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/
/**
 * @brief	Handle interrupt from 32-bit timer
 * @return	Nothing
 */
void TIMER0_IRQHandler(void)
{
	if (Chip_TIMER_MatchPending(LPC_TIMER0, 1)) {
#if 1
		if (LPC_GPIO->PIN & (1 << RX_PIN)) {
				start_bit = true;
			}

			if (start_bit == true) {
				if (LPC_GPIO->PIN & (1 << RX_PIN)) {
					sum += 1;
				} else {
					sum += 0;
				}
				oversampling_count += 1;
			}
			if (oversampling_count == oversampling_rate) {
				oversampling_count = 0;
				float avg = sum/oversampling_rate;
				if (avg < 0.5) {
					rx_buff[bit_count] = '0';
				} else {
					rx_buff[bit_count] = '1';
				}
				bit_count += 1;
				sum = 0;
			}

			if (bit_count == 1024) {
				bit_count = 0;
				process_data = true;
			}

#endif
		Chip_TIMER_ClearMatch(LPC_TIMER0, 1);
	}
}

void process_received_data(void) {
	if (process_data == true) {
		start_bit = false;
		process_data = false;
		strncpy(data_in_bits, rx_buff, sizeof(rx_buff));
		int confidence_level = 10;
		int corrupt_percentage = 0;

		int start_of_payload = get_start_location_of_payload(data_in_bits, sizeof(data_in_bits), data_sync_bits, SYNC_BITS, confidence_level, corrupt_percentage);
		printf("Payload Starts at %d\n", start_of_payload);
		if (start_of_payload != -1) {
			char temp[8] = {0};
			int count = 0;
			for (int i = start_of_payload; i < sizeof(data_in_bits); i++) {
				temp[count++] = data_in_bits[i];
				if (count == 8) {
					printf("%c", convert_8_bits_to_char(temp));
					count = 0;
				}
			}
		}
		flag = 0;
	}
}

/**
 * @brief	main routine for blinky example
 * @return	Function should not exit.
 */
int main(void)
{
	uint32_t timerFreq;

	/* Generic Initialization */
	SystemCoreClockUpdate();
	Board_Init();

    strncpy(sync_field, lisaSyncField, SYNC_FIELD_BYTES);
	convert_bytes_to_bits(sync_field, SYNC_FIELD_BYTES, data_sync_bits);

	/* Enable timer 1 clock */
	Chip_TIMER_Init(LPC_TIMER0);

	/* Timer rate is system clock rate */
	timerFreq = Chip_Clock_GetSystemClockRate();	// 96Mhz
	LPC_GPIO3->DIR |= (1 << GREEN_LED_PIN);
	LPC_GPIO->DIR |= (1 << TX_PIN);					// Set as output
	LPC_GPIO->DIR &= ~(1 << RX_PIN);				// Set as input

	/* Timer setup for match and interrupt at TICKRATE_HZ */
	Chip_TIMER_Reset(LPC_TIMER0);
	Chip_TIMER_MatchEnableInt(LPC_TIMER0, 1);
	Chip_TIMER_SetMatch(LPC_TIMER0, 1, (timerFreq / (TICKRATE_HZ1 * sampling_rate * oversampling_rate)));
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER0, 1);
	Chip_TIMER_Enable(LPC_TIMER0);

	/* Enable timer interrupt */
	NVIC_ClearPendingIRQ(TIMER0_IRQn);
	NVIC_EnableIRQ(TIMER0_IRQn);

	/* LEDs toggle in interrupt handlers */
	while (1) {
		if (flag == 0) {
			printf("Press 2 to Receive\n");
			scanf("%d", &flag);
		}
			if(flag==2) break;
		__WFI();
	}
			process_received_data();

	return 0;
}

