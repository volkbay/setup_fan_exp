/*
 * C code for knob-controlled ...
 * PWM to drive on ATTiny45 chip.
 * 
 * Created: 14.04.2022 22:28:49
 * Author : @volkbay
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile int analogRes = 0;
int value = 0;
int currentVal = 0;
int currentCnt = 0;

ISR(ADC_vect)
{
	value = ADCH;
	if (currentCnt == 10){
		currentCnt = 0;
		OCR0A = currentVal;
		currentVal = 0;
	}
	else{
		currentCnt++;
		if (currentVal < value) currentVal = value;
	}
}

int main(void) {		
	
	DDRB |= (1<<PB0);
	DDRB &= ~(1<<PB3);
	TCCR0A =  1 << COM0A1 | 1 << WGM01 | 1 << WGM00;
	TCCR0B = 1 << CS01;
	// Analog Read
	ADMUX &= ~(1 << REFS1 | 1 << REFS0); //Right align, Vcc ref
	ADMUX |= 1 << MUX1 | 1 << MUX0 | 1 << ADLAR; // PB3 analog input
	ADCSRB &= ~(1 << ADTS2 | 1 << ADTS1 | 1 << ADTS0); // Free running mode
	DIDR0 |= 1 << ADC3D; //reduce power cons.
	ADCSRA |= 1 << ADEN | 1 << ADIE | 1 << ADATE;
	sei();
	ADCSRA |= 1 << ADSC;

	while (1) {	}
	return 0;
}