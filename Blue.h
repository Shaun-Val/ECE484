#include <avr/io.h>
#include <util/delay.h>

#define BAUD 9600                            // Define baud rate
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)     // Set baud rate value for UBRR
#define LED_PIN DDB4                         // Define LED pin (Pin 4 on Arduino)


void receiver() {
    UBRR0H = (BAUDRATE >> 8);
    UBRR0L = BAUDRATE;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);    // Enable receiver and transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  // Set frame: 8data, 1 stop bit
}

// Function to initialize the LED pin
void led() {
    DDRD |= (1 << LED_PIN);                 // Set LED_PIN as an output
}

// Function to send a character via USART
void transmit(char data) {
    while (!(UCSR0A & (1 << UDRE0)));        // Wait until buffer is empty
    UDR0 = data;                             // Send data
}