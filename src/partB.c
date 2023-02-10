#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL


// PART B

// Onboard-LED : PB5

void Initialize() {
    cli(); // disable all global interrupts
    // set PB5 to be output
    DDRB |= (1 << DDB5);

    // 8 : PB0
    // set PB0 to be input
    DDRB &= ~(1<<DDB0);

    // Timer1 Setup
    // Set Timer 1 clock to be internal div 8
    // 2MHz timer clock, 1 tick = (1/2M) second
    TCCR1B &= ~(1<<CS10);
    TCCR1B |= (1<<CS11);
    TCCR1B &= ~(1<<CS12);

    // set Timer 1 to Normal
    TCCR1A &= ~(1<<WGM10);
    TCCR1A &= ~(1<<WGM11);
    TCCR1B &= ~(1<<WGM12);
    TCCR1B &= ~(1<<WGM13);

    // Looking for rising edge
    TCCR1B |= (1<<ICES1);
    // Looking for a falling edge


    // clear interrupt flag
    TIFR1 |= (1<<ICF1);

    // enable input capture interrupt
    TIMSK1 |= (1<<ICIE1);

    sei(); // enable global interrupts
}

ISR(TIMER1_CAPT_vect) {
        // if button is pressed down turn the LED on
        if (PINB & (1 << PINB0)) {
            // button is pressed turn LED on
            PORTB |= (1 << PORTB5);
            cli();
            // now look for a falling edge
            TCCR1B &= ~(1<<ICES1);
            sei();
        } else {
            // turn LED off
            PORTB &= ~(1 << PORTB5);
            cli();
            // now look for a rising edge
            TCCR1B |= (1<<ICES1);
            sei();
        }
}

int main () {
    // turn PB5 off initially
    PORTB &= ~(1 << PORTB5);
    Initialize();
    while (1);
}