CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
LIBS = -lm
EXEC = hw3
GCC = gcc $(CFLAGS)
FUNCS = func1.c func2.c func3.c func4.c func5.c

# Test the TEST_INTEGRATE flag, or the integrate() function in answer3.c
# parameters are [output file name], [lower limit], [upper limit], [interval number]
testgen: hw3.h
	$(GCC) testgen.c answer3.c $(FUNCS) -o $@ -DTEST_INTEGRATE $(LIBS)
	./testgen TEST_INTEGRATE.out 1.0 2.0 10000

# Test the RUN_INTEGRATE flag, or runIntegrate() function in answer3.c
# Parameters are [input file], [output file]
# testcases folder contains inputs, testdir contains outputs
# the $@ takes the target name, i.e. testall in this case
testall: hw3.h
	$(GCC) hw3.c answer3.c $(FUNCS) -o $@ -DRUN_INTEGRATE -DTEST_INTEGRATE $(LIBS)
	mkdir testdir
	./$@ testcases/test1 testdir/test1.out
	./$@ testcases/test2 testdir/test2.out
	./$@ testcases/test3 testdir/test3.out
	./$@ testcases/test4 testdir/test4.out
	./$@ testcases/test5 testdir/test5.out

clean:
	/bin/rm -f input*
	/bin/rm -f *.o
	/bin/rm -f testgen 
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
	/bin/rm -f hw3 hw3.prof
	/bin/rm -f -r testdir
	/bin/rm -f testall
