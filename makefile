# My First Makefile
CC=gcc # Compiler to use
INCLUDES=-I ./ # Directory for header file
OBJS=main.o gamefunc.o # List of objects to be build
EXEC=hangman

all: ${OBJS}
	@echo "Building executable..."
	${CC} ${INCLUDES} ${OBJS} -o ${EXEC}
 
%.o: %.c
	@echo "Building object $*.o..."
	${CC} -c $*.c ${INCLUDES}

list:
	@echo $(shell ls)            
 
clean:
	@echo "Cleaning..."
	rm -rf *.o

mrproper: clean
	rm -rf ${EXEC}