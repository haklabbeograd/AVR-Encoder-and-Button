#ifndef KEYPAD_H_INCLUDED
#define KEYPAD_H_INCLUDED

#define ROWS_DIR    DDRC
#define COLS_DIR    DDRB

#define ROWS_PULLUP PORTC
#define COLS_PULLUP PORTB

#define ROWS_PULLUP_SET (PORTC | 0b00000111)
#define COLS_PULLUP_SET (PORTB | 0b00011111)

#define ROWS_MASK   0b00000111
#define COLS_MASK   0b00011111

#define ROWS_INPUT  (DDRC & 0b11111000)
#define COLS_INPUT  (DDRB & 0b11100000)

#define ROWS_OUTPUT (DDRC | 0b00000111)
#define COLS_OUTPUT (DDRB | 0b00011111)

#define ROWS_READ   PINC
#define COLS_READ   PINB

#define ROWS_WRITE  PORTC
#define COLS_WRITE  PORTB

#define COLS_PCINT PCINT0_vect

void setupKeypad();
char* getButtonName();

#endif // KEYPAD_H_INCLUDED
