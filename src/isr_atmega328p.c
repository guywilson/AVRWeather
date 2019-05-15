#include <avr/interrupt.h>
#include <avr/io.h>

#include "sched/scheduler.h"
#include "taskdef.h"

#include "rtc_atmega328p.h"
#include "serial_atmega328p.h"
#include "adc_atmega328p.h"

/*
** Vector Num	Interrupt Definition					Vector Name
** ==========	====================================	==================
**  1			Reset									RESET_vect
**  2			External Interrupt Request 0			INT0_vect
**  3			External Interrupt Request 1			INT1_vect
**  4			Pin Change Interrupt Request 0			PCINT0_vect
**  5			Pin Change Interrupt Request 1			PCINT1_vect
**  6			Pin Change Interrupt Request 2			PCINT2_vect
**  7			Watchdog Time-out Interrupt				WDT_vect
**  8			Timer/Counter2 Compare Match A			TIMER2_COMPA_vect
**  9			Timer/Counter2 Compare Match B			TIMER2_COMPB_vect
** 10			Timer/Counter2 Overflow					TIMER2_OVF_vect
** 11			Timer/Counter1 Capture Event			TIMER1_CAPT_vect
** 12			Timer/Counter1 Compare Match A			TIMER1_COMPA_vect
** 13			Timer/Counter1 Compare Match B			TIMER1_COMPB_vect
** 14			Timer/Counter1 Overflow					TIMER1_OVF_vect
** 15			Timer/Counter0 Compare Match A			TIMER0_COMPA_vect
** 16			Timer/Counter0 Compare Match B			TIMER0_COMPB_vect
** 17			Timer/Counter0 Overflow					TIMER0_OVF_vect
** 18			SPI Serial Transfer Complete			SPI_STC_vect
** 19			USART Rx Complete						USART_RX_vect
** 20			USART Data Register Empty				USART_UDRE_vect
** 21			USART Tx Complete						USART_TX_vect
** 22			ADC Conversion Complete					ADC_vect
** 23			EEPROM Ready							EE_READY_vect
** 24			Analog Comparator						ANALOG_COMP_vect
** 25			Two-wire Serial Interface				TWI_vect
** 26			Store Program Memory Read				SPM_READY_vect
*/

/*
 * The 'do nothing' handler...
 */
void __defaultHandler() {
	// Do nowt...
}

/*
 * External Interrupt Request 0
 */
ISR(INT0_vect, ISR_BLOCK) {
	__defaultHandler();
}

/*
 * External Interrupt Request 1
 */
ISR(INT1_vect, ISR_BLOCK) {
	__defaultHandler();
}

/*
 * Pin Change Interrupt Request 0
 */
ISR(PCINT0_vect, ISR_BLOCK) {
	__defaultHandler();
}

/*
 * Pin Change Interrupt Request 1
 */
ISR(PCINT1_vect, ISR_BLOCK) {
	__defaultHandler();
}

/*
 * Pin Change Interrupt Request 2
 */
ISR(PCINT2_vect, ISR_BLOCK) {
	__defaultHandler();
}

/*
 * Watchdog Time-out Interrupt
 */
ISR(WDT_vect, ISR_BLOCK) {
	__defaultHandler();
}

/*
 * Timer/Counter2 Compare Match A
 */
ISR(TIMER2_COMPA_vect, ISR_BLOCK) {
	__defaultHandler();
}

/*
 * Timer/Counter2 Compare Match B
 */
ISR(TIMER2_COMPB_vect, ISR_BLOCK) {
	__defaultHandler();
}

/*
 * Timer/Counter2 Overflow
 */
ISR(TIMER2_OVF_vect, ISR_BLOCK) {
	__defaultHandler();
}

/*
 * Timer/Counter1 Capture Event
 */
ISR(TIMER1_CAPT_vect, ISR_BLOCK) {
	__defaultHandler();
}

/*
 * Timer/Counter1 Compare Match A
 */
ISR(TIMER1_COMPA_vect, ISR_BLOCK) {
	handleTimer1Compare();
}

/*
 * Timer/Counter1 Compare Match B
 */
ISR(TIMER1_COMPB_vect, ISR_BLOCK) {
	__defaultHandler();
}

/*
 * Timer/Counter1 Overflow
 */
ISR(TIMER1_OVF_vect, ISR_BLOCK) {
	__defaultHandler();
}

/*
 * Timer/Counter0 Compare Match A
 */
ISR(TIMER0_COMPA_vect, ISR_BLOCK) {
	__defaultHandler();
}

/*
 * Timer/Counter0 Compare Match B
 */
ISR(TIMER0_COMPB_vect, ISR_BLOCK) {
	__defaultHandler();
}

/*
 * Timer/Counter0 Overflow
 */
ISR(TIMER0_OVF_vect, ISR_BLOCK) {
	__defaultHandler();
}

/*
 * SPI Serial Transfer Complete
 */
ISR(SPI_STC_vect, ISR_BLOCK) {
	__defaultHandler();
}

/*
 * USART Rx Complete
 */
ISR(USART_RX_vect, ISR_BLOCK) {
	handleRxComplete(UDR0);
}

/*
 * USART Data Register Empty
 */
ISR(USART_UDRE_vect, ISR_BLOCK) {
	handleDRE();
}

/*
 * USART Tx Complete
 */
ISR(USART_TX_vect, ISR_BLOCK) {
	__defaultHandler();
}

/*
 * ADC Conversion Complete
 */
ISR(ADC_vect, ISR_BLOCK) {
	handleADConversionComplete();
}

/*
 * EEPROM Ready
 */
ISR(EE_READY_vect, ISR_BLOCK) {
	__defaultHandler();
}

/*
 * Analog Comparator
 */
ISR(ANALOG_COMP_vect, ISR_BLOCK) {
	__defaultHandler();
}

/*
 * Two-wire Serial Interface
 */
ISR(TWI_vect, ISR_BLOCK) {
	__defaultHandler();
}

/*
 * Store Program Memory Read
 */
ISR(SPM_READY_vect, ISR_BLOCK) {
	__defaultHandler();
}
