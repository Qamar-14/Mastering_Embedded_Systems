ENTRY(reset)
MEMORY
{
   Mem (rwx) : ORIGIN = 0x00000000, LENGTH = 64M
}

SECTIONS
{
	. = 0x10000;
	.startup . :
	{
	  startup.o(.text)
	}>Mem
	.text : 	/* constants  and other code stored in Mem*/
	{
	  *(.text) *(.rodata) /* Merge all the remaining .txt & rodata (input sections) to the output .txt section */
	}>Mem
	.data :		/* data, initialized variables, to be copied to RAM upon <RESET> by startup.c */
	{
	  *(.data) 	/* uninitialized data which is initialized to 0 upon <RESET> by startup.c */
	}>Mem
	.bss :
	{
	  *(.bss) *(COMMON) 
	}>Mem
	. = . + 0x1000;	/* 4KB of Stack Memory */
	stack_top = .;
}