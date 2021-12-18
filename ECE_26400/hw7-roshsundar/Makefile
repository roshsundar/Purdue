TARGET = hw7
CFLAGS = -std=c99 -g  -Wall -Wshadow --pedantic -Wvla -Werror
TESTS = -DTEST_DIVIDE -DTEST_INTERLEAVE -DTEST_SHUFFLE  
GCC = gcc $(CFLAGS) $(TESTS) 

OBJS = main.o shuffle.o 

VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose --track-origins=yes

$(TARGET): $(OBJS) shuffle.h
	$(GCC)  $(OBJS) -o $(TARGET)

%.o : %.c
	$(GCC) -c $<

testall: test1 test2 test3

testmemory: $(TARGET)
	$(VALGRIND) ./$(TARGET) 4 | sort > out4.txt
	$(VALGRIND) ./$(TARGET) 8 | sort > out8.txt
	$(VALGRIND) ./$(TARGET) 11 | sort > out11.txt
	$(VALGRIND) ./$(TARGET) 13 | sort > out13.txt

test1: $(TARGET)
	./$(TARGET) 4 | sort > out4.txt
	diff -i -w out4.txt expected/expected4

test2: $(TARGET)
	./$(TARGET) 8 | sort > out8.txt
	diff -i -w out8.txt expected/expected8

test3: $(TARGET)
	./$(TARGET) 11 | sort > out11.txt
	diff -i -w out11.txt expected/expected11

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f *.txt
