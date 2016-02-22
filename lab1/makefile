OBJ = main.o math.o log.o
prog.x: $(OBJ)
	ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 /usr/lib64/crt1.o /usr/lib64/crti.o -L/usr/lib64 $^ -lc /usr/lib64/crtn.o -o prog.x

%.o: %.s
	as -o $@ $<

%.s: %.c
	gcc -S -o $@ -c $<

clean:
	rm -f *.s *.o prog.x