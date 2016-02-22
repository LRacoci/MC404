##########################################################
# Description: The makefile for "trab01".
#
# Author: Lucas Alves Racoci - ra156331@students.ic.unicamp.br
#
#
##########################################################

# List of object files that must be linked together to 
# build the ias-as executable
OBJ_FILES = main.o HashTable.o Builder.o iasDefs.o Word.o  Error.o MemMap.o

# Default rule
all: ias-as

# -- Rules for making each one of the .o files --

# -- main.o depends on main.c and on error.h
main.o: main.c error.h
	gcc -c -g main.c -o main.o

# -- error.o depends on error.c and on error.h
error.o: error.c error.h
	gcc -c -g error.c -o error.o

# All the .o files depends on the .c and .h with the same name
%.o: %.c %.h
	gcc -c $< -o $@ -std=c99 -pedantic -Wall -Werror -lm -g

# -- Clean rule. It removes the ias-as file and any .o file on the directory --
.PHONY : clean_all clean
clean:
	rm -f ias-as *.o

##########################################################
# Do not change this rule
##########################################################

# -- Rule to make the executable ias-as
ias-as: $(OBJ_FILES)
	gcc -g $(OBJ_FILES) -o ias-as 