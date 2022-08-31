ENTRY(reset)

MEMORY
{
	Mem (rwx):ORIGIN = 0x00000000 , LENGTH = 64M
}

SECTIONS
{
	.qamar :
	{
		*(.text)
	}
}