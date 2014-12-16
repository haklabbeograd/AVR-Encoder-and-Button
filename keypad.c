#include <avr/io.h>
#include "keypad.h"
#include <util/delay.h>

//#define __DEBUG__

#ifdef __DEBUG__
#include "usart.h"
#endif // __DEBUG__
//Strings button matrix
char buttons[3][5][10] =
        {
            {"NA","NA","NA","SW204","SW207"},
            {"SW200","SW205","ENCBUTT","SW202","SW208"},
            {"SW201","SW203","NA","SW206","SW209"}
        };

//Sets columns as input, pushes them up, and sets an interrupt on them
//Sets rows as output and sets them to drive LOW.
inline void setupKeypad()
{
    COLS_DIR = COLS_INPUT;
    COLS_PULLUP = COLS_PULLUP_SET;
    ROWS_DIR = ROWS_OUTPUT;
    ROWS_WRITE &= ~ROWS_MASK;

    PCICR |= (1 << PCIE0);    // set PCIE0 to enable PCMSK0 scan
    PCMSK0 |= COLS_MASK; //set pins 43210 to one
}

//Sets rows as input, pulls them high, drives columns LOW..
inline void setupKeypadforRows()
{
    ROWS_DIR = ROWS_INPUT;
    ROWS_PULLUP = ROWS_PULLUP_SET;
    COLS_DIR = COLS_OUTPUT;
    COLS_WRITE&= ~COLS_MASK;

}
//retrieves the button name from the buttons string matrix
char* getButtonName()
{
    int i=0,j=0;
    char * returnStr = 0;
    uint8_t read = COLS_READ | ~COLS_MASK;
#ifdef __DEBUG__
    uint8_t debug_cols = read;
    uint8_t debug_rows = 0;
#endif // __DEBUG__
    i = 0;
    while((read & 1) && i<5)
    {
        read>>=1;
        i++;
    }
    if(i < 5)
    {
        setupKeypadforRows();
        _delay_ms(25);
        read = ROWS_READ | ~ROWS_MASK;

#ifdef __DEBUG__
        debug_rows = read;
#endif // __DEBUG__

        j =0;
        while((read & 0b1)&& j<3 )
        {
            read>>=1;
            j++;
        }

        if(j<3)
            returnStr = buttons[j][i];
    }
    setupKeypad();
#ifdef __DEBUG__
    char debug_str[50];
    sprintf(debug_str,"COLS: 0x%X\nROWS: 0x%X\nJ: %d\nI: %d\n\n",debug_cols,debug_rows,j,i);
    USART_putstring(debug_str);
#endif // __DEBUG__
    return returnStr;
}
