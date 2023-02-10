//
// Created by Keith Mathe on 2/10/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>


int main() {
    // set as outputs
    DDRB |= (1 << DDB1);
    DDRB |= (1 << DDB2);
    DDRB |= (1 << DDB3);
    DDRB |= (1 << DDB4);

    while (1) {
        // set output as high
        PORTB |= (1 << PORTB1);
        PORTB |= (1 << PORTB2);
        PORTB |= (1 << PORTB3);
        PORTB |= (1 << PORTB4);
    }
}


