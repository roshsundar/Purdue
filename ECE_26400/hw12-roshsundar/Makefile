TARGET = hw12
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose --track-origins=yes
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

all:
	$(GCC) *.c -o $(TARGET) -I.

test:
	./$(TARGET) inputs/test1

memory:
	$(VALGRIND) ./$(TARGET) inputs/test1

clean:
	rm -f *.o
	rm -f *.txt