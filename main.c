#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
//#include <avr/iom328p.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include "keypad.h"
#include "usart.h"
#include "bit_magic.h"

//globals
volatile uint8_t change = 0; /*<< flag set in columns interrupt cleared in main */
uint8_t oldPIND2 =0;
uint8_t newPIND2 = 0;

//sets up encoder pins as input, pulled up, and interrupt on change..
void setupEncoder()
{
    DDRD &= ~(1 << DDD2) & ~(1 << DDD3);        //set pins as input
    PORTD |= (1 << PORTD2) | (1 << PORTD3);     //pulls up pins
    PCICR |= (1 << PCIE2);                      // set PCIE02 to enable PCMSK0 scan
    PCMSK2 |= (1 << PCINT18) | (1 << PCINT19);  // set PCINT0 to trigger an interrupt on state change
}
int main(void)
{
    USART_init();       //Call the USART initialization code
    setupKeypad();      //Call the keypad initialization code
    setupEncoder();     //Call the Encoder initialization code
    char * buttonToSend = 0;
    while(1)
    {   //Infinite loop
        sei();//enables the interrupts
        set_sleep_mode(SLEEP_MODE_IDLE);
        sleep_mode();   //sleeps
        cli();          //upon wake up disable interrupts

        if(change)
        {//Button in matrix pressed
            _delay_ms(25);
            change = 0;
            buttonToSend = getButtonName();
        }
        if(buttonToSend != 0)
        {//Button identified
            USART_putstring("Button: ");
            USART_putstring(buttonToSend);
            USART_putstring("\n");
        }

    }

    return 0;
}

//Button matrix Column interrupt
ISR(COLS_PCINT)
{
    change = 1;//set flag
}


#define phaseA REGISTER_BIT(PIND,2)
#define phaseB REGISTER_BIT(PIND,3)
//Encoder interrupt routine
//Sends "Encoder: ++\n" if encoder moved forward
//Sends "Encoder: --\n" if encoder moved reverse
ISR(PCINT2_vect)
{
    newPIND2 = phaseA;
    if((oldPIND2 == 0) && (newPIND2 != 0))
    {
        if( phaseB == 0 )
        {
            USART_putstring("Encoder: --\n");
        }
        else
        {
            USART_putstring("Encoder: ++\n");
        }
        _delay_ms(125);
    }
    oldPIND2 = newPIND2;
}

