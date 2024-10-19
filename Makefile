FLAGS = -I -DDEBUG
OFLAG = -o

compile: main.o disassemble.o
	gcc $(OFLAG) disassembler main.o disassemble.o $(FLAGS)


main.o: main.c
	gcc -c main.c

disassemble.o: disassemble.c disassemble.h
	gcc -c disassemble.c

clean:
	@echo "delete object file(s) from program"
	rm -f *.o program.exe
