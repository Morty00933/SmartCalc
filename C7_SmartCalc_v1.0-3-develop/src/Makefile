.PHONY: all re calc clean check test
#.PHONY если есть файлы с именем как цель, они игнорируются

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
TST_LIBS :=  -lcheck -lm -lpthread
OS := $(shell uname -s)

ifeq ($(OS),Linux)
	CFLAGS+=-D LINUX
else
	ifeq ($(OS),Darwin)
		CFLAGS+=-D MAC
	endif
endif

all: test calc.a gcov_report

re: clean test gcov_report

test: calc.a test.o
	$(CC) $(CFLAGS) test.o calc.a $(TST_LIBS) -o test
	@./test

test.o: test.c
	$(CC) $(CFLAGS) -c test.c -o test.o

calc.a: calc.o
	@ar rcs calc.a calc.o
	ranlib calc.a

calc.o: SmartCalc.c
	$(CC) $(CFLAGS) -c SmartCalc.c -o calc.o

gcov_report: gcov_test.info
	@genhtml -o report/ gcov_test.info
	@open report/index.html

gcov_test.info: gcov_test gcov_test.gcda
	@lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .

gcov_test: test.c SmartCalc.c
	$(CC) $(CFLAGS) --coverage test.c SmartCalc.c $(TST_LIBS) -o gcov_test

gcov_test.gcda:
	@chmod +x *
	@./gcov_test

install:
	make clean
	mkdir build
	cd SmartCalc && qmake && make && make clean && rm Makefile && cd ../ && mv SmartCalc/SmartCalc.app build
	open build/SmartCalc.app
uninstall:
	rm -rf build*

dvi:
	open read.md

dist:
	rm -rf Archive_calc_v1.0/
	mkdir Archive_calc_v1.0/
	mkdir Archive_calc_v1.0/src
	cp -r build/SmartCalc.app Archive_calc_v1.0/src/
	tar cvzf Archive_calc_v1.0.tgz Archive_calc_v1.0/
	rm -rf Archive_calc_v1.0/

clean:
	@rm -rf test gcov_test *.gcno *.gcda *.info report *.{a,o,dSYM,out} $(EXECUTABLE) build

check-linters:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h *.cpp
	rm -f .clang-format
	
valgrind:
	valgrind --leak-check=full --track-origins=yes --trace-children=yes -s ./test
