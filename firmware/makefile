all: clock.elf

clean:
	rm *.o
	rm *.hex
	rm *.elf

clock.elf: main.o
	avr-gcc -Wall -Os -DF_CPU=8000000 -mmcu=atmega328p -o clock.elf main.o
	avr-objcopy -j .text -j .data -O ihex clock.elf clock.hex

flash:
	avrdude -c usbasp -p atmega328p -U flash:w:clock.hex:i

.c.o:
	avr-gcc -Wall -Os -DF_CPU=8000000 -mmcu=atmega328p -c $< -o $@ 
.cpp.o:
	avr-g++ -Wall -Os -DF_CPU=8000000 -mmcu=atmega328p -c $< -o $@ 
