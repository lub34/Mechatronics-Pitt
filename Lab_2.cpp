/*
 * Lab 2 Code Luke Blascovich.cpp
 *
 * Created: 2/1/2021 11:19:01 AM
 * Author : Luke Blascovich
 */ 

//** GLOBAL VARIABLES **/
char position = 0;		 // Determines which LED was last on. 0-3 represent pins PC0-3 respectively
char direction = 0;		 // Determines whether circuit is cycling through LEDs one way or the other. 0 for one way, 1 for the other

// Function prototypes
void wait(volatile int multiple);

#include <avr/io.h>

int main(void)
{
	DDRC = 0b00001111;  // Set PC4-7 to input; set PC0-3 to output
	PORTC = 0b11111111; // Set all port C pins declared in DDRC as outputs to HIGH (5V) (those that aren't outputs are merely placeholders here)
	
	DDRD = 0b00000000;	// Set all port D pins to inputs (only really need PC2 to be input for this code though)
		 
    // ============================================
    // P R O G R A M L O O P
    // ============================================
	while(1)
    {
		//Check if switch 1 is open () / closed ()
	   	if (PIND & 0b00000100) // Switch 1 is open. "Read" the contents of PortD2 using bit-wise operation (AND PIND with binary 8 so that only PD2 is read)
		{   // When read as 1 (open switch) start cycling through the LEDs by alternating which of pins PC0-3 is on.
			if (position == 0)
			{
				PORTC = 0b11111110;
				// Clear PC0, setting it to 0V; essentially unblocking the dam holding back current from flowing through its LED and turning said LED on.
				// Set PC1, setting it to 5V; essentially blocking the current from flowing through its pin's LED and turning said LED off.
				// Set PC2, setting it to 5V; essentially blocking the current from flowing through its pin's LED and turning said LED off.
				// Set PC3, setting it to 5V; essentially blocking the current from flowing through its pin's LED and turning said LED off.
				
				// Increment position to next LED that needs to be turned on
				direction = 0; // Flip cycling direction
				position++;
				wait(1000); // 1000ms = 1sec delay
			}
			else if (position == 1)
			{
				PORTC = 0b11111101;
				// Set PC0, setting it to 5V; essentially blocking the current from flowing through its pin's LED and turning said LED off.
				// Clear PC1, setting it to 0V; essentially unblocking the dam holding back current from flowing through its LED and turning said LED on.
				// Set PC2, setting it to 5V; essentially blocking the current from flowing through its pin's LED and turning said LED off.
				// Set PC3, setting it to 5V; essentially blocking the current from flowing through its pin's LED and turning said LED off.
				
				// Increment position to next LED that needs to be turned on
				if (direction == 0)
				{
					position++; // Cycle forward by 1 LED
				}
				else
				{
					position--; // Cycle backward by 1 LED
				}
				wait(1000); // 1000ms = 1sec delay
			}
			else if (position == 2)
			{
				PORTC = 0b11111011;
				// Set PC0, setting it to 5V; essentially blocking the current from flowing through its pin's LED and turning said LED off.
				// Set PC1, setting it to 5V; essentially blocking the current from flowing through its pin's LED and turning said LED off.
				// Clear PC2, setting it to 0V; essentially unblocking the dam holding back current from flowing through its LED and turning said LED on.
				// Set PC3, setting it to 5V; essentially blocking the current from flowing through its pin's LED and turning said LED off.
				
				// Increment position to next LED that needs to be turned on
				if (direction == 0)
				{
					position++; // Cycle forward by 1 LED
				}
				else
				{
					position--; // Cycle backward by 1 LED
				}
				wait(1000); // 1000ms = 1sec delay
			}
			else // when position == 3
			{
				PORTC = 0b11110111;
				// Set PC0, setting it to 5V; essentially blocking the current from flowing through its pin's LED and turning said LED off.
				// Set PC1, setting it to 5V; essentially blocking the current from flowing through its pin's LED and turning said LED off.
				// Set PC2, setting it to 5V; essentially blocking the current from flowing through its pin's LED and turning said LED off.
				// Clear PC3, setting it to 0V; essentially unblocking the dam holding back current from flowing through its LED and turning said LED on.
				
				// Increment position to next LED that needs to be turned on
				direction = 1; // Flip cycling direction
				position--;
				wait(1000); // 1000ms = 1sec delay
			}
		}
		// This effect seems to lag by one LED... weird
		else // Switch is closed; 
		{
			PORTC = 0b11111111;
		}
	}
	
return 0;	
} // end main

/*
============================================
  FUNCTIONS
============================================
*/

void wait(volatile int multiple) {
	// This subroutine creates a delay equal to multiple*T, where T is 1 msec
	while (multiple > 0) {
		TCCR0A = 0x00; // clears WGM00 and WGM01 (bits 0 and 1) to ensure Timer/Counter is in normal mode.
		TCNT0 = 0; // preload value for testing on count = 250
		TCCR0B = 0b00000011; //1<<CS01 | 1<<CS00; TCCR0B = 0x03; // Start TIMER0, Normal mode, crystal clock, prescaler = 64
		while (TCNT0 < 0xFA); // exits when count = 250 (requires preload of 0 to make count = 250)
		TCCR0B = 0x00; // Stop TIMER0
		multiple--;
	}
} // end wait()


