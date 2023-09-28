#prepared by Qamora

CC=arm-none-eabi-
CFLAGS=-mcpu=cortex-m4 -gdwarf-2 -g
INCS=-I .
LIBS=
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o) 
As = $(wildcard *.s)
AsOBJ = $(As:.s=.o) 
Project_Name= unit3_lab4_cortexM4

all: $(Project_Name).hex
	@echo "----------BUILD IS DONE----------"

%.o: %.s
	$(CC)as.exe $(CFLAGS) $< -o $@ 

%.o: %.c
	$(CC)gcc.exe -c $(INCS) $(CFLAGS) $< -o $@

$(Project_Name).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_Script.ld $(LIBS) $(OBJ) $(AsOBJ)  -o $@ -Map=Map_file.map
	cp $(Project_Name).elf $(Project_Name).axf	

$(Project_Name).hex: $(Project_Name).elf
	$(CC)objcopy.exe -O binary $< $@

clean:
	rm -rf *.o *~ *.elf *.hex
	@echo "Everything clean"
