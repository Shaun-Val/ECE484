#include <avr/io.h>
#include <util/delay.h>

#define BAUD 9600                            // Define baud rate
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)     // Set baud rate value for UBRR
#define LED_PIN DDB4                          // Define LED pin (Pin 10 on Arduino)

// Function to initialize the USART
void uart_init() {
    UBRR0H = (BAUDRATE >> 8);
    UBRR0L = BAUDRATE;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);    // Enable receiver and transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  // Set frame: 8data, 1 stop bit
}

// Function to initialize the LED pin
void led_init() {
    DDRD |= (1 << LED_PIN);                 // Set LED_PIN as an output
}

// Function to send a character via USART
void uart_transmit(char data) {
    while (!(UCSR0A & (1 << UDRE0)));        // Wait until buffer is empty
    UDR0 = data;                             // Send data
}

int main(void) {
    uart_init();                             // Initialize USART
    led_init();                              // Initialize the LED pin

    while (1) {
        if (UCSR0A & (1 << RXC0)) {          // Check if data received
            char received_char = UDR0;       // Fetch the received character

            // Check the received character to control the LED
            if (received_char == '1') {
                PORTD |= (1 << LED_PIN);     // Turn on the LED
            } else if (received_char == '0') {
                PORTD &= ~(1 << LED_PIN);    // Turn off the LED
            }

            // Echo the received character back to the terminal
            uart_transmit(received_char); 
        }
        _delay_ms(100);                     // Delay for stability
    }
}
