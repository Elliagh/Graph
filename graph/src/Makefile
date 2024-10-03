CC=gcc
FLAGS=--std=c11 -Werror -Wall -Wextra
DIR=../build
DIR_TEST=../build/test_

all: test_validate_string test_precedence test_infix2postfix graph

test_validate_string: test.c
	$(CC) $(FLAGS) -o $(DIR_TEST)1 -DTEST_VALIDATE parsing.c stack.c test.c utils.c

test_precedence: test.c
	$(CC) $(FLAGS) -o $(DIR_TEST)2 -DTEST_PRECEDENCE parsing.c stack.c test.c utils.c

test_infix2postfix: test.c
	$(CC) $(FLAGS) -o $(DIR_TEST)3 -g -DTEST_INFIX2POSTFIX parsing.c stack.c test.c utils.c

graph: graph.c geometry.c utils.c
	$(CC) $(FLAGS) -o $(DIR)/graph -lm graph.c geometry.c utils.c calc.c stack.c parsing.c 

check:
	clang-format -i *.c *.h
	cppcheck --std=c11 --enable=all --suppress=missingIncludeSystem *.c *.h
	leaks --atExit -- ../build/graph

clean:
	rm -rf *.o a.out ../build/*

rebuild:
	make clean all
