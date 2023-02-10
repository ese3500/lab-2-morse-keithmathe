#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include <util/delay.h>
#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)


// PART C
char String[25];
// stores the binary encoding of a Morse sequence that is a character
char morseBinary[6];
// how many Morse bits have we received
int morseBitCount = 0;

int thirty_ms_ovfs = 7;
int two_hundred_ms_ovfs = 49 * 10; // 2 seconds
int four_hundred_ms_ovfs = 98 * 10; // 4 seconds
volatile int count = 0;

int buttonNotPressed = 1;
int bitstringTerminated = 0;

void Initialize() {
    cli(); // disable all global interrupts
    // set PB5 to be output
    // Onboard-LED : PB5
    DDRB |= (1 << DDB5);

    // 8 : PB0
    // set PB0 to be input
    DDRB &= ~(1<<DDB0);

    // set LED pins as outputs
    DDRB |= (1 << DDB2);
    DDRB |= (1 << DDB3);


    // set Timer 1 to Normal
    // prescale of 1
    TCCR1B |= (1<<CS10);

    // Looking for rising edge
    TCCR1B |= (1<<ICES1);

    // clear interrupt flag
    TIFR1 |= (1<<ICF1);

    // enable input capture interrupt
    TIMSK1 |= (1<<ICIE1);

    // enable timer overflow interrupt
    TIMSK1 |= (1<<TOIE1);
    TIFR1 |= (1<<TOV1);

    sei(); // enable global interrupts
}

void printChar(char bitstring[]){
    // return a character repr of Morse bitstring
    // a dot is 0 and a dash is a 1
    if (strcmp(bitstring, "01") == 0) {
        sprintf(String,"A\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "1000") == 0) {
        sprintf(String,"B\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "1010") == 0) {
        sprintf(String,"C\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "100") == 0) {
        sprintf(String,"D\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "0") == 0) {
        sprintf(String,"E\n");
        UART_putstring(String);
    }
    else  if (strcmp(bitstring, "0010") == 0) {
        sprintf(String,"F\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "110") == 0) {
        sprintf(String,"G\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "0000") == 0) {
        sprintf(String,"H\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "00") == 0) {
        sprintf(String,"I\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "0111") == 0) {
        sprintf(String,"J\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "101") == 0) {
        sprintf(String,"K\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "0100") == 0) {
        sprintf(String,"L\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "11") == 0) {
        sprintf(String,"M\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "10") == 0) {
        sprintf(String,"N\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "111") == 0) {
        sprintf(String,"O\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "0110") == 0) {
        sprintf(String,"P\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "1101") == 0) {
        sprintf(String,"Q\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "010") == 0) {
        sprintf(String,"R\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "000") == 0) {
        sprintf(String,"S\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "1") == 0) {
        sprintf(String,"T\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "001") == 0) {
        sprintf(String,"U\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "0001") == 0) {
        sprintf(String,"V\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "011") == 0) {
        sprintf(String,"W\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "1001") == 0) {
        sprintf(String,"X\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "1011") == 0) {
        sprintf(String,"Y\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "1100") == 0) {
        sprintf(String,"Z\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "01111") == 0) {
        sprintf(String,"1\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "00111") == 0) {
        sprintf(String,"2\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "00011") == 0) {
        sprintf(String,"3\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "00001") == 0) {
        sprintf(String,"4\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "00000") == 0) {
        sprintf(String,"5\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "10000") == 0) {
        sprintf(String,"6\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "11000") == 0) {
        sprintf(String,"7\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "11100") == 0) {
        sprintf(String,"8\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "11110") == 0) {
        sprintf(String,"9\n");
        UART_putstring(String);
    }
    else if (strcmp(bitstring, "11111") == 0) {
        sprintf(String,"0\n");
        UART_putstring(String);
    }

}

ISR(TIMER1_CAPT_vect) {
    // if button is pressed down turn the LED on
  if (PINB & (1 << PINB0)) {
        // button pressed down
          sprintf(String,"Button pressed down\n");
          UART_putstring(String);
          _delay_ms(50);


        // start counting overflows
        count = 0;
        // button is pressed turn LED on
        PORTB |= (1 << PORTB5);
        cli();
        // now look for a falling edge
        TCCR1B &= ~(1<<ICES1);
        sei();

      // record the button as pressed
      buttonNotPressed = 0;

      bitstringTerminated = 0;
    } else {
          // button released
          sprintf(String,"Button released\n");
          UART_putstring(String);
          _delay_ms(50);

          sprintf(String,"count: %d\n", count);
          UART_putstring(String);
          _delay_ms(50);

        // determine the type of press it was
        // if dot: record the 0, print that it was a dot, blink blue LED
        if (count <= two_hundred_ms_ovfs && count >= thirty_ms_ovfs) {
            // record the 0
            morseBinary[morseBitCount] = '0';
            morseBitCount += 1;

            // print that it was a dot
            sprintf(String,"dot\n");
            UART_putstring(String);
            _delay_ms(50);

            // blink the blue LED
            PORTB |= (1 << PORTB3);
            _delay_ms(50);
            PORTB &= ~(1 << PORTB3);

            bitstringTerminated = 0;

        }
        // dash: record the 1, print that it was a dot, blink red LED
        else if (count <= four_hundred_ms_ovfs && count >= two_hundred_ms_ovfs) {
            // record the 1
            morseBinary[morseBitCount] = '1';
            morseBitCount += 1;

            // print that it was a dash
            sprintf(String,"dash\n");
            UART_putstring(String);
            _delay_ms(50);

            // blink red LED
            PORTB |= (1 << PORTB2);
            _delay_ms(50);
            PORTB &= ~(1 << PORTB2);

            bitstringTerminated = 0;
        }


        cli();
        // now look for a rising edge
        TCCR1B |= (1<<ICES1);
        sei();

        // record the button as not pressed anymore
        buttonNotPressed = 1;
        count = 0;
    }
}

ISR(TIMER1_OVF_vect) {
    count ++;

    // check if the button has not been pressed for more than 400ms
    // space: print the character that was decoded, print that it was a space
    if (count > four_hundred_ms_ovfs && buttonNotPressed && !bitstringTerminated) {
        morseBinary[morseBitCount] = '\0';

        // translate the Morse bitstring to a character and print to serial monitor
        printChar(morseBinary);

        // reset the morse bit tracking
        morseBitCount = 0;



        sprintf(String,"space\n\n");
        UART_putstring(String);
        _delay_ms(50);

        bitstringTerminated = 1;
    }


}



int main () {
    UART_init(BAUD_PRESCALER);
    // turn PB5 off initially
    PORTB &= ~(1 << PORTB5);
    Initialize();
    while (1);


//   PART A
//    // configure LED pins as outputs
//



//
//    // configure button pin D7 as input
//    DDRD &= !(1 << DDD7);
//    int counter = 0;
//
//    // turn PB1 on initially
//    PORTB |= (1 << PORTB1);
//
//    while (1) {
//        // check if value at port is HIGH
//        if (PIND & (1 << PIND7)) {
//            // turn off all LEDs
//            PORTB &= ~(1 << PORTB1);
//
//            PORTB &= ~(1 << PORTB4);
//            counter += 1;
//            if (counter % 4 == 1) {
//                // turn on PB1
//                PORTB |= (1 << PORTB1);
//                _delay_ms(500);
//            } else if (counter % 4 == 2) {
//                // turn on PB2
//                PORTB |= (1 << PORTB2);
//                _delay_ms(500);
//            } else if (counter % 4 == 3) {
//                // turn on PB3
//                PORTB |= (1 << PORTB3);
//                _delay_ms(500);
//            } else if (counter % 4 == 0) {
//                // turn on PB4
//                PORTB |= (1 << PORTB4);
//                _delay_ms(500);
//            }
//        }
//    }

}