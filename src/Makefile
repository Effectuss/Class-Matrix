#################################################
##              Makefile template              ##
#################################################

#     These special targets are called phony     #
# .PHONY: all dist clean test style leaks lcov

#################### Exec file ###################
EXEC := matrix_oop_test

############# Name of static library #############
SLIB := matrix_oop.a

#################### Test name ###################
TEST := test_matrix.cc

# Choosing a compiler and setting the main flags #
CC := g++
STANDART :=-std=c++17
CFLAGS := -Wall -Werror -Wextra $(STANDART)
LKFLAGS := -g -fprofile-arcs -ftest-coverage
CPPCHECKFLAG := --enable=all --language=c++ -$(STANDART) --suppress=missingIncludeSystem
LDFLAGS := -lgtest
VFLAG := --leak-check=full --show-leak-kinds=all -s
TEST_FLAGS = -fprofile-arcs -ftest-coverage

OS := $(shell uname)
ifeq ($(OS), Darwin)
LEAKS := leaks --atExit -- ./$(EXEC)
endif
ifeq ($(OS), Linux)
LEAKS := valgrind $(VFLAG) ./$(EXEC)
LDFLAGS += -lpthread -lgtest_main -L/usr/lib
endif

##################      Path     #################
P_LINT := ../linters

################# Resource files #################
CSOURCES :=$(wildcard *.cc)
CHEADERS :=$(wildcard *.h)
COBJ :=$(CSOURCES:.cc=.o)
HOBJ :=$(CHEADERS:.h=.gch)

################### Main target ##################
all: $(SLIB)

################## Style check ###################
style:
	-cp $(P_LINT)/.clang-format .
	@clang-format -i *.cc
	@clang-format -i *.h
	clang-format -n *.cc
	clang-format -n *.h
	-cppcheck $(CPPCHECKFLAG) *.h *.cc

################## Leaks check ###################
leaks: $(EXEC)
	$(LEAKS)

############ Cleaning up unused files ############
clean:
	-@rm -rf $(EXEC)
	-@rm -rf *.o
	-@rm -rf *.gch
	-@rm -rf *.a
	-@rm -rf *.gcno
	-@rm -rf *.gcda
	-@rm -rf report
	-@rm -rf *.info
	-@rm -rf .clang-format
	-@rm -rf *.tgz
	-@rm -rf matrix_oop_test.dSYM

####### Template for creating object files #######
%.o : %.cc
	$(CC) $(CFLAGS) -c $< -o $@

### Template for creating header object files ###
%.gch : %.h
	$(CC) $(CFLAGS) -c $< -o $@

##############  Project archiving   ##############
dist:
	tar -czf $(EXEC).tgz ./*

##############   Create exit file   ##############
$(EXEC): $(CSOURCES)
	$(CC) $(CFLAGS) --coverage -o $(EXEC) $< $(TEST) $(LDFLAGS)

##############         Tests        ##############
test: clean $(EXEC)
	./$(EXEC)

##############     gcov report      ##############
lcov: test
	lcov -t "$(EXEC)" -o $(EXEC).info -c -d .
	genhtml -o report $(EXEC).info

##############   matrix_oop.a   ##############
$(SLIB): $(COBJ) $(HOBJ)
	ar -rvs $(SLIB) $<