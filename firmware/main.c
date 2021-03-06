#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <string.h>
#include <stdarg.h>

unsigned char _matrix[8];

void matrix_init() {
  memset(_matrix, 0, 8);
  PORTB = 0b11111111;
  PORTD = 0b00000000;
}

void matrix_set(int c, int r, int v) {
  if( v ) {
    _matrix[r] |= 1 << c;
  } else {
    _matrix[r] &= ~(1 << c);
  }
}

void matrix_display() {
  int c;
  for( c = 0; c < 8; c++ ) {
    PORTB = _matrix[c];
    PORTD = 1 << c;
    //_delay_ms(2);    
  }
}
  

void TWIInit(void)
{
    //set SCL to 400kHz
    TWSR = 0x00;
    TWBR = 0x0C;
    //enable TWI
    TWCR = (1<<TWEN);
}

void TWIStart(void)
{
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while ((TWCR & (1<<TWINT)) == 0);
}

void TWIStop(void)
{
    TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void TWIWrite(uint8_t u8data)
{
    TWDR = u8data;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while ((TWCR & (1<<TWINT)) == 0);
}

uint8_t TWIReadACK(void)
{
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    while ((TWCR & (1<<TWINT)) == 0);
    return TWDR;
}

uint8_t TWIReadNACK(void)
{
    TWCR = (1<<TWINT)|(1<<TWEN);
    while ((TWCR & (1<<TWINT)) == 0);
    return TWDR;
}

uint8_t TWIGetStatus(void)
{
    uint8_t status;
    //mask status
    status = TWSR & 0xF8;
    return status;
}

int main( void )
{
  DDRB = 0b11111111;
  DDRD = 0b11111111;

  matrix_init();

  matrix_set(0, 0, 1);
  matrix_set(1, 1, 1);
  matrix_set(2, 2, 1);
  matrix_set(3, 3, 1);
  matrix_set(4, 4, 1);
  matrix_set(5, 5, 1);
  matrix_set(6, 6, 1);
  matrix_set(7, 7, 1);

  TWIInit();

  for(;;) {
    matrix_display();
    //_delay_ms(10);
  }
}

