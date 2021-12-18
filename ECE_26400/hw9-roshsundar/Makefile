TARGET = hw9
CFLAGS = -std=c99 -g  -Wall -Wshadow --pedantic -Wvla -Werror
GCC = gcc $(CFLAGS)

OBJS = hw9.o maze.o mazehelper.o path.o solver.o

VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose --track-origins=yes

$(TARGET): $(OBJS) maze.h mazehelper.h path.h solver.h
	$(GCC) $(OBJS) -o $(TARGET)

%.o : %.c
	$(GCC) -c $<

testall: test1 test2 test3 test4 test5

testmemory: $(TARGET)
	$(VALGRIND) ./$(TARGET) inputs/maze1 path1.txt
	
test1: $(TARGET)
	./$(TARGET) inputs/maze1 path1.txt

test2: $(TARGET)
	./$(TARGET) inputs/maze2 path2.txt

test3: $(TARGET)
	./$(TARGET) inputs/maze3 path3.txt

test4: $(TARGET)
	./$(TARGET) inputs/maze4 path4.txt

test5: $(TARGET)
	./$(TARGET) inputs/maze5 path5.txt

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f *.txt
	rm -f *.o
