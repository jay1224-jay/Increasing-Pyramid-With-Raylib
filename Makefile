CC = gcc
LIBS = -lraylib -lm

a.out: disk_stack.c
	$(CC) disk_stack.c $(LIBS)
	@echo "To run the program, execute the file \"a.out\"(or a.exe if Windows)"


