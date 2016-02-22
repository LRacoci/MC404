ARQS = phybo.ldo dobra.ldo
disk.img: $(ARQS)
	mksd.sh --so /home/specg12-1/mc404/simulador/dummyos.elf --user $<

%.ldo: %.o
	arm-eabi-ld $< -g -o $@ -Ttext=0x77802000 -Tdata=0x77802150

%.o: %.s
	arm-eabi-as $< -g -o $@

source:
	source /home/specg12-1/mc404/simulador/set_path.sh

all: disk.img
	make source
	make disk.img

clean:
	rm -f *.ldo *.o prog.x
