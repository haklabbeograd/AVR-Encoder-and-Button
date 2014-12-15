#ifndef USART_H_INCLUDED
#define USART_H_INCLUDED

void USART_init(void);
unsigned char USART_receive(void);
void USART_send( unsigned char data);
void USART_putstring(char* StringPtr);

#endif // USART_H_INCLUDED
