TARGET = hw8
CFLAGS = -std=c99 -g  -Wall -Wshadow --pedantic -Wvla -Werror
TESTS = -DTEST_DIVIDE -DTEST_INTERLEAVE -DTEST_SHUFFLE  
GCC = gcc $(CFLAGS) $(TESTS) 

OBJS = main.o shuffle.o 

VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose --track-origins=yes

$(TARGET): $(OBJS) shuffle.h
	$(GCC)  $(OBJS) -o $(TARGET)

%.o : %.c
	$(GCC) -c $<

testall: test1 test2 test3 test4

testmemory: $(TARGET)
	$(VALGRIND) ./$(TARGET) 3 1 | sort > out_3_1.txt
	$(VALGRIND) ./$(TARGET) 3 2 | sort > out_3_2.txt
	$(VALGRIND) ./$(TARGET) 4 2 | sort > out_4_2.txt
	$(VALGRIND) ./$(TARGET) 6 2 | sort > out_6_2.txt
	
test1: $(TARGET)
	./$(TARGET) 3 1 | sort > out_3_1.txt
	diff -i -w out_3_1.txt expected/expected_3_1

test2: $(TARGET)
	./$(TARGET) 3 2 | sort > out_3_2.txt
	diff -i -w out_3_2.txt expected/expected_3_2

test3: $(TARGET)
	./$(TARGET) 4 2 | sort > out_4_2.txt
	diff -i -w out_4_2.txt expected/expected_4_2

test4: $(TARGET)
	./$(TARGET) 6 2 | sort > out_6_2.txt
	diff -i -w out_6_2.txt expected/expected_6_2

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f *.txt
