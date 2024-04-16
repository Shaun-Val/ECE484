#include <avr/io.h>
#include <util/delay.h>
#include "Blue.h"

int main(void) {
    receiver();                        // Initialize USART
    led();                              // Initialize the LED pin

    while (1) {
        if (UCSR0A & (1 << RXC0)) {          // Check if data received
            char received_char = UDR0;       // Fetch the received character

            // Check the received character to control the LED
            if (received_char == '1') {
                PORTD |= (1 << LED_PIN);     // Turn on the LED
            } else if (received_char == '0') {
                PORTD &= ~(1 << LED_PIN);    // Turn off the LED
            }
        }
        _delay_ms(100);       
    }
}
