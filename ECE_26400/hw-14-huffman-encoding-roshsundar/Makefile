TARGET = hw14
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose --track-origins=yes
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

a := basic
b := gophers
c := para
d := prideandprejudice
e := woods

all: 
	$(GCC)  *.c -o $(TARGET) -I.

test: all
	./$(TARGET) inputs/$(a) $(addsuffix _sorted,$(a)) $(addsuffix _huffman,$(a)) $(addsuffix _header,$(a)) 
	diff $(addsuffix _sorted,$(a)) expected/$(addsuffix _sorted,$(a))
	diff $(addsuffix _huffman,$(a)) expected/$(addsuffix _huffman,$(a))
	diff $(addsuffix _header,$(a)) expected/$(addsuffix _header,$(a))

	./$(TARGET) inputs/$(b) $(addsuffix _sorted,$(b)) $(addsuffix _huffman,$(b)) $(addsuffix _header,$(b)) 
	diff $(addsuffix _sorted,$(b)) expected/$(addsuffix _sorted,$(b))
	diff $(addsuffix _huffman,$(b)) expected/$(addsuffix _huffman,$(b))
	diff $(addsuffix _header,$(b)) expected/$(addsuffix _header,$(b))
	
	./$(TARGET) inputs/$(c) $(addsuffix _sorted,$(c)) $(addsuffix _huffman,$(c)) $(addsuffix _header,$(c)) 
	diff $(addsuffix _sorted,$(c)) expected/$(addsuffix _sorted,$(c))
	diff $(addsuffix _huffman,$(c)) expected/$(addsuffix _huffman,$(c))
	diff $(addsuffix _header,$(c)) expected/$(addsuffix _header,$(c))

	./$(TARGET) inputs/$(d) $(addsuffix _sorted,$(d)) $(addsuffix _huffman,$(d)) $(addsuffix _header,$(d))
	diff $(addsuffix _sorted,$(d)) expected/$(addsuffix _sorted,$(d))
	diff $(addsuffix _huffman,$(d)) expected/$(addsuffix _huffman,$(d))
	diff $(addsuffix _header,$(d)) expected/$(addsuffix _header,$(d))

	./$(TARGET) inputs/$(e) $(addsuffix _sorted,$(e)) $(addsuffix _huffman,$(e)) $(addsuffix _header,$(e)) 
	diff $(addsuffix _sorted,$(e)) expected/$(addsuffix _sorted,$(e))
	diff $(addsuffix _huffman,$(e)) expected/$(addsuffix _huffman,$(e))
	diff $(addsuffix _header,$(e)) expected/$(addsuffix _header,$(e))
	
.PHONY: $(a)
.PHONY: $(b)
.PHONY: $(c)
.PHONY: $(d)
.PHONY: $(e)
.PHONY: clean

$(a): all
	$(VALGRIND) ./$(TARGET) inputs/$(a) $(addsuffix _sorted,$(a)) $(addsuffix _huffman,$(a)) $(addsuffix _header,$(a))

$(b): all
	$(VALGRIND) ./$(TARGET) inputs/$(b) $(addsuffix _sorted,$(b)) $(addsuffix _huffman,$(b)) $(addsuffix _header,$(b))

$(c): all
	$(VALGRIND) ./$(TARGET) inputs/$(c) $(addsuffix _sorted,$(c)) $(addsuffix _huffman,$(c)) $(addsuffix _header,$(c))

$(d): all
	$(VALGRIND) ./$(TARGET) inputs/$(d) $(addsuffix _sorted,$(d)) $(addsuffix _huffman,$(d)) $(addsuffix _header,$(d))

$(e): all
	$(VALGRIND) ./$(TARGET) inputs/$(e) $(addsuffix _sorted,$(e)) $(addsuffix _huffman,$(e)) $(addsuffix _header,$(e))

clean:
	rm $(TARGET) 
	rm $(addsuffix _sorted,$(a)) $(addsuffix _huffman,$(a)) $(addsuffix _header,$(a))
	rm $(addsuffix _sorted,$(b)) $(addsuffix _huffman,$(b)) $(addsuffix _header,$(b))
	rm $(addsuffix _sorted,$(c)) $(addsuffix _huffman,$(c)) $(addsuffix _header,$(c))
	rm $(addsuffix _sorted,$(d)) $(addsuffix _huffman,$(d)) $(addsuffix _header,$(d))
	rm $(addsuffix _sorted,$(e)) $(addsuffix _huffman,$(e)) $(addsuffix _header,$(e))

