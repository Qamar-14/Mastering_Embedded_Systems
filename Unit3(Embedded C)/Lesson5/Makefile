#prepared by Qamora

CC=arm-none-eabi-
CFLAGS=-mcpu=cortex-m3 -gdwarf-2
INCS=-I .
LIBS=
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o) 
As = $(wildcard *.s)
AsOBJ = $(As:.s=.o) 
all: learn-in-depth_cortexM4_led.hex
	@echo "----------BUILD IS DONE----------"

%.o: %.s
	$(CC)as.exe $(CFLAGS) $< -o $@ 

%.o: %.c
	$(CC)gcc.exe -c $(INCS) $(CFLAGS) $< -o $@

learn-in-depth_cortexM4_led.elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_Script.ld $(LIBS) $(OBJ) $(AsOBJ)  -o $@ -Map=Map_file.map
	
learn-in-depth_cortexM4_led.hex: learn-in-depth_cortexM4_led.elf
	$(CC)objcopy.exe -O binary $< $@

clean:
	rm -rf *.o *~ *.elf *.hex
	@echo "Everything clean"
