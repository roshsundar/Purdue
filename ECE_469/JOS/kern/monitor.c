// Simple command-line kernel monitor useful for
// controlling the kernel and exploring the system interactively.

#include <inc/stdio.h>
#include <inc/string.h>
#include <inc/memlayout.h>
#include <inc/assert.h>
#include <inc/x86.h>

#include <kern/console.h>
#include <kern/monitor.h>
#include <kern/kdebug.h>
#include <kern/trap.h>
#include <kern/pmap.h>
#include <kern/env.h>
#define CMDBUF_SIZE	80	// enough for one VGA text line
// ANSI color codes
#define ANSI_RESET   "\x1b[0m"
#define ANSI_RED     "\x1b[31m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_BLUE    "\x1b[34m"
#define ANSI_MAGENTA "\x1b[35m"

struct Command {
	const char *name;
	const char *desc;
	// return -1 to force monitor to exit
	int (*func)(int argc, char** argv, struct Trapframe* tf);
};

// LAB 1: add your command to here...
static struct Command commands[] = {
	{ "help", "Display this list of commands", mon_help },
	{ "kerninfo", "Display information about the kernel", mon_kerninfo },
	{ "show", "Display the ASCII art", mon_show },
	{ "showmappings", "Display the mappings in a readable format", mon_showmappings },
	{ "setperms", "set the permissions for an address", mon_setperms },
	{ "si", "Step in and execute one instruction", mon_si}
};

/***** Implementations of basic kernel monitor commands *****/

int
mon_help(int argc, char **argv, struct Trapframe *tf)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(commands); i++)
		cprintf("%s - %s\n", commands[i].name, commands[i].desc);
	return 0;
}

int
mon_kerninfo(int argc, char **argv, struct Trapframe *tf)
{
	extern char _start[], entry[], etext[], edata[], end[];

	cprintf("Special kernel symbols:\n");
	cprintf("  _start                  %08x (phys)\n", _start);
	cprintf("  entry  %08x (virt)  %08x (phys)\n", entry, entry - KERNBASE);
	cprintf("  etext  %08x (virt)  %08x (phys)\n", etext, etext - KERNBASE);
	cprintf("  edata  %08x (virt)  %08x (phys)\n", edata, edata - KERNBASE);
	cprintf("  end    %08x (virt)  %08x (phys)\n", end, end - KERNBASE);
	cprintf("Kernel executable memory footprint: %dKB\n",
		ROUNDUP(end - entry, 1024) / 1024);
	return 0;
}

void 
printColorfulText(const char* text, const char* color) {
	cprintf("%s%s%s\n", color, text, ANSI_RESET);
}

int
mon_show(int argc, char **argv, struct Trapframe *tf)
{
	// Print colorful ASCII art
	printColorfulText("PPPPPPP   UU   UU   RRRRRR    DDDDDD    UU   UU   EEEEEEE", ANSI_RED);
    printColorfulText("PP   PP   UU   UU   RR   RR   DD   DD   UU   UU   EE     ", ANSI_GREEN);
    printColorfulText("PPPPPPP   UU   UU   RRRRRR    DD   DD   UU   UU   EEEEEE ", ANSI_YELLOW);
    printColorfulText("PP        UU   UU   RR  RR    DD   DD   UU   UU   EE     ", ANSI_BLUE);
    printColorfulText("PP         UUUUU    RR   RR   DDDDDD     UUUUU    EEEEEEE", ANSI_MAGENTA);
	return 0;
}

int
mon_showmappings(int argc, char **argv, struct Trapframe *tf)
{
	//no input to function
	if(argc != 3)
	{
		cprintf("  FORMAT:\n");
		cprintf("    showmappings beginaddr endaddr\n");
		return -1;
	}
	//get the inputs as strings
	char* begin_str = argv[1];
	char* end_str = argv[2];
	//these two to check if they have bad addresses
	char* beg_has_failed = NULL;
	char* end_has_failed = NULL;
	//get the addresses of the beginning and the ending in the form of uintptr via strtol
	uintptr_t beg = strtol(begin_str, &beg_has_failed, 16);
	if(*beg_has_failed != '\0' || (beg_has_failed == NULL))
	{
		cprintf("  Hex address format for input %s invalid\n", begin_str);
		return -1;
	}
	uintptr_t end = strtol(end_str, &end_has_failed, 16);
	if(*end_has_failed != '\0' || (end_has_failed == NULL))
	{
		cprintf("  Hex address format for input %s invalid\n", end_str);
		return -1;
	}

	//check if end is above the highest possible
	uintptr_t curr = beg;

	while(curr <= end)
	{
		//we want to make sure that it doesnt overflow over the maximum limit of curr (aka 2^32)
		if((2^32) - curr < PGSIZE)
		{
			break;
		}
		// we use the same function as in bootmapregion to walk through each page size via a page table entry
		//we are only reading through so we dont want to create a new page
		pte_t *pte = pgdir_walk(kern_pgdir,(void*) curr, 0);
		//checks if the walk failed
		if(!pte || !(*pte & PTE_P))
		{
			cprintf("No mapped value at %x", curr);
		}
		else
		{
			cprintf("ADDR: %x; ", curr);
			//we want to get all the perms of curr
			int read = ((*pte & PTE_P) == 1);
			int write = ((*pte & PTE_W) == 2);
			int user = ((*pte & PTE_U) == 4);
			cprintf("PERMS: R:%d; W:%d; U:%d", read, write, user);
		}
		cprintf("\n");
		// Increment in PGSIZE chunks
		curr += PGSIZE;
	}
	return 0;
}

int
mon_setperms(int argc, char **argv, struct Trapframe *tf)
{
	if (argc < 2)
	{
		cprintf("  FORMAT (to change perms):\n");
		cprintf("    setperms addr [P|W|U] in bit pattern format\n");
		return -1;
	}
	char* has_failed = NULL;
	uintptr_t init_addr = strtol(argv[1], &has_failed, 16);
	if(*has_failed != '\0' || (has_failed == NULL))
	{
		cprintf("  Hex address format for input %s invalid\n", init_addr);
		return -1;
	}
	// get the page table entry at init_addr
	pte_t *pte = pgdir_walk(kern_pgdir,(void*) init_addr, 0);
	if (argc < 3) 
	{
		cprintf("ADDR: %x; ", init_addr);
		//we want to get all the perms of curr before the change
		int read = ((*pte & PTE_P) == 1);
		int write = ((*pte & PTE_W) == 2);
		int user = ((*pte & PTE_U) == 4);
		cprintf("PERMS: R:%d; W:%d; U:%d\n", read, write, user);
		return 0;
	}
	else if(argc == 3)
	{
		//change the perms based on the bit pattern given by the input
		bool incorrect_inp = true;
		int curr_perm = 0;
		if((argv[2][0] == '0' || argv[2][0] == '1') && (argv[2][1] == '0' || argv[2][1] == '1') && (argv[2][2] == '0' || argv[2][2] == '1'))
		{
			incorrect_inp = false;
		}
		if(strlen(argv[2]) != 3)
		{
			incorrect_inp = true;
		}
		if(incorrect_inp)
		{
			cprintf("  FORMAT (to change perms):\n");
			cprintf("    setperms addr [P|W|U] in bit pattern format\n");
			return -1;
		}
		if(argv[2][0] == '0' || argv[2][0] == '1')
		{
			*pte = (argv[2][0] == '1') ? (*pte | PTE_P): (*pte & ~PTE_P);
		}
		if(argv[2][1] == '0' || argv[2][1] == '1')
		{
			*pte = (argv[2][1] == '1') ? (*pte | PTE_W): (*pte & ~PTE_W);
		}
		if(argv[2][2] == '0' || argv[2][2] == '1')
		{
			*pte = (argv[2][2] == '1') ? (*pte | PTE_U): (*pte & ~PTE_U);
		}
		cprintf("ADDR: %x; ", init_addr);
		//we want to get all the perms of curr after the change
		int read = ((*pte & PTE_P) == 1);
		int write = ((*pte & PTE_W) == 2);
		int user = ((*pte & PTE_U) == 4);
		cprintf("PERMS: R:%d; W:%d; U:%d\n", read, write, user);
		return 0;
	}
	else
	{
		cprintf("too many inputs\n");
		return -1;
	}
}

const char* remove_after_colon(const char* inputString, char* fin_string)
{
	int i = 0;
	while(inputString[i] != '\0')
	{
		if(inputString[i] == ':')
		{
			fin_string[i] = '\0';
			return fin_string;
		}
		else
		{
			fin_string[i] = inputString[i];
		}
		i++;
	}
	return fin_string;
}

int
mon_backtrace(int argc, char **argv, struct Trapframe *tf)
{
	// LAB 1: Your code here.
    // HINT 1: use read_ebp().
    // HINT 2: print the current ebp on the first line (not current_ebp[0])
	
	//get the top of the stack
	uint32_t init_ebp = read_ebp();
	uint32_t* curr_ebp = (uint32_t*) init_ebp;
	int num_backtraces = 0;
	cprintf("Stack backtrace:\n");
	// while the previous ebp exists
	while(curr_ebp != 0)
	{
		uint32_t eip = curr_ebp[1];
		cprintf("  ebp %08x  eip %08x  args", curr_ebp, (curr_ebp[1]));
		//5 arguments
		for(uint32_t i = 2; i < 7; i++)
		{
			cprintf(" %08x", curr_ebp[i]);
		}
		cprintf("\n");
		num_backtraces++;
		
		//Call EIP debug info:
		struct Eipdebuginfo debug;
		debuginfo_eip(eip, &debug);
		char fin_string[100];
		const char* fn_name = remove_after_colon(debug.eip_fn_name, fin_string);
		cprintf("          %s:%d: %s+%d\n", debug.eip_file, debug.eip_line, fn_name, eip - debug.eip_fn_addr);
		curr_ebp = (uint32_t*) *curr_ebp;
	}
	return 0;
}

int
mon_si(int argc, char **argv, struct Trapframe *tf)
{
	//check if trapframe is available
	if(!tf)
	{
		panic("nothing to step into!\n");
	}
	//check if breakpoint or debug is enabled to step in
	if(tf->tf_trapno == T_BRKPT || tf->tf_trapno == T_DEBUG)
	{
		//enable the tf eflag for executing one instruction
		tf->tf_eflags |= 0x100;
		//run environment
		env_run(curenv);
	}
	else
	{
		panic("no breakpoints and debug mode is disabled!\n");
	}
	return 0;
}

/***** Kernel monitor command interpreter *****/

#define WHITESPACE "\t\r\n "
#define MAXARGS 16

static int
runcmd(char *buf, struct Trapframe *tf)
{
	int argc;
	char *argv[MAXARGS];
	int i;

	// Parse the command buffer into whitespace-separated arguments
	argc = 0;
	argv[argc] = 0;
	while (1) {
		// gobble whitespace
		while (*buf && strchr(WHITESPACE, *buf))
			*buf++ = 0;
		if (*buf == 0)
			break;

		// save and scan past next arg
		if (argc == MAXARGS-1) {
			cprintf("Too many arguments (max %d)\n", MAXARGS);
			return 0;
		}
		argv[argc++] = buf;
		while (*buf && !strchr(WHITESPACE, *buf))
			buf++;
	}
	argv[argc] = 0;

	// Lookup and invoke the command
	if (argc == 0)
		return 0;
	for (i = 0; i < ARRAY_SIZE(commands); i++) {
		if (strcmp(argv[0], commands[i].name) == 0)
			return commands[i].func(argc, argv, tf);
	}
	cprintf("Unknown command '%s'\n", argv[0]);
	return 0;
}

void
monitor(struct Trapframe *tf)
{
	char *buf;

	cprintf("Welcome to the JOS kernel monitor!\n");
	cprintf("Type 'help' for a list of commands.\n");

	if (tf != NULL)
		print_trapframe(tf);

	while (1) {
		buf = readline("K> ");
		if (buf != NULL)
			if (runcmd(buf, tf) < 0)
				break;
	}
}
