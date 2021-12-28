TARGET = hw14
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose --track-origins=yes
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

all: 
	$(GCC)  *.c -o $(TARGET) -I.