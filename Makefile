CC=msp430-gcc
# no optimization
CFLAGS= -Wall -fomit-frame-pointer -mmcu=msp430g2553

OBJS=IR-transmit.o


all: $(OBJS)
	$(CC) $(CFLAGS) -o IR-transmit.elf $(OBJS)

#this is an implicit rule that says how to compile a .c to get a .o
#$< is the name of the first prereq (the .c file)
%.o: %.c
	$(CC) $(CFLAGS) -g -c $<
	$(CC) $(CFLAGS) -S $<

clean:
	rm -fr IR-transmit.elf $(OBJS)
