OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(start)

SECTIONS
{
	. = 0x30000000;

	__code_start = .;

	. = ALIGN(4);
	.text : {
		*(.vectors)
		*(.text)
	}

	. = ALIGN(4);
	.rodata : { 
		*(.rodata) 
	}

	. = ALIGN(4);
	.data : { 
		*(.data) 
	}

	. = ALIGN(4);
	__bss_start = .;
	.bss : { 
		*(.bss) 
		*(.COMMON) 
	}
	__end = .;
}
