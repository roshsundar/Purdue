// implement fork from user space

#include <inc/string.h>
#include <inc/lib.h>

// PTE_COW marks copy-on-write page table entries.
// It is one of the bits explicitly allocated to user processes (PTE_AVAIL).
#define PTE_COW		0x800

//
// Custom page fault handler - if faulting page is copy-on-write,
// map in our own private writable copy.
//
static void
pgfault(struct UTrapframe *utf)
{
	void *addr = (void *) utf->utf_fault_va;
	uint32_t err = utf->utf_err;
	int r;

	// Check that the faulting access was (1) a write, and (2) to a
	// copy-on-write page.  If not, panic.
	// Hint:
	//   Use the read-only page table mappings at uvpt
	//   (see <inc/memlayout.h>).

	// LAB 4: Your code here.
	if(!(err & FEC_WR))
    {
        panic("pgfault: not a write!");
    }
    else if(!(uvpt[(uintptr_t)addr >> PGSHIFT] & PTE_COW))
    {
        panic("pgfault: not a copy-on-write!");
    }

	// Allocate a new page, map it at a temporary location (PFTEMP),
	// copy the data from the old page to the new page, then move the new
	// page to the old page's address.
	// Hint:
	//   You should make three system calls.

	// LAB 4: Your code here.
	r = sys_page_alloc(0, PFTEMP, PTE_P|PTE_U|PTE_W);
	if(r < 0)
    {
        panic("sys_page_alloc: %e", r);
    }
    
    memmove(PFTEMP, ROUNDDOWN(addr, PGSIZE), PGSIZE);

	r = sys_page_map(0, PFTEMP, 0, ROUNDDOWN(addr, PGSIZE), PTE_P|PTE_U|PTE_W);
    if(r < 0)
    {
        panic("sys_page_map: %e", r);
    }
	r = sys_page_unmap(0, PFTEMP);
    if(r < 0)
    {
        panic("sys_page_unmap: %e", r);
    }
}

//
// Map our virtual page pn (address pn*PGSIZE) into the target envid
// at the same virtual address.  If the page is writable or copy-on-write,
// the new mapping must be created copy-on-write, and then our mapping must be
// marked copy-on-write as well.  (Exercise: Why do we need to mark ours
// copy-on-write again if it was already copy-on-write at the beginning of
// this function?)
//
// Returns: 0 on success, < 0 on error.
// It is also OK to panic on error.
//
static int
duppage(envid_t envid, unsigned pn)
{
	int r;

	// LAB 4: Your code here.
	pte_t pte = uvpt[pn];
	if(((pte & PTE_W) || (pte & PTE_COW)) && !(pte & PTE_SHARE))
	{
		r = sys_page_map(thisenv->env_id, (void*)(pn*PGSIZE), envid, (void*)(pn*PGSIZE), PTE_COW|PTE_P|PTE_U);
		if(r < 0)
		{
			panic("dup page failed!");
		}
		r = sys_page_map(thisenv->env_id, (void*)(pn*PGSIZE), thisenv->env_id, (void*)(pn*PGSIZE), PTE_COW|PTE_P|PTE_U);
		if(r < 0)
		{
			panic("dup page failed!");
		}
	}
	else
	{
		r = sys_page_map(thisenv->env_id, (void*)(pn*PGSIZE), envid, (void*)(pn*PGSIZE), (PTE_SYSCALL & pte));
		if(r < 0)
		{
			panic("dup page failed!");
		}
	}
	// panic("duppage not implemented");
	return 0;
}

//
// User-level fork with copy-on-write.
// Set up our page fault handler appropriately.
// Create a child.
// Copy our address space and page fault handler setup to the child.
// Then mark the child as runnable and return.
//
// Returns: child's envid to the parent, 0 to the child, < 0 on error.
// It is also OK to panic on error.
//
// Hint:
//   Use uvpd, uvpt, and duppage.
//   Remember to fix "thisenv" in the child process.
//   Neither user exception stack should ever be marked copy-on-write,
//   so you must allocate a new page for the child's user exception stack.
//
envid_t
fork(void)
{
	// LAB 4: Your code here.
	set_pgfault_handler(pgfault);
	if(!(thisenv->env_pgfault_upcall))
	{
		set_pgfault_handler(pgfault);
	}

	envid_t childid = sys_exofork();
	if(childid < 0)
	{
		panic("sys exofork failed");
	}
	if(childid == 0)
	{
		thisenv = &envs[ENVX(sys_getenvid())];
		return 0;
	}

	for(int i = 0; i < NPDENTRIES; i++)
	{
		pde_t pde = uvpd[i];
		if(pde & PTE_P)
		{
			for(int j = 0; j < NPTENTRIES; j++)
			{
				uintptr_t pn = i * NPDENTRIES + j;
				pte_t pte = uvpt[pn];
				if(!(pte & PTE_P) || (pn*PGSIZE >= UTOP) || (pn * PGSIZE == UXSTACKTOP - PGSIZE))
				{
					continue;
				}
				duppage(childid, pn);
			}
		}
	}
	int r = sys_page_alloc(childid, (void*)(UXSTACKTOP - PGSIZE), PTE_P|PTE_U|PTE_W);
	if(r < 0)
	{
		panic("sys_page_alloc failed");
	}
	r = sys_page_map(childid, (void*)(UXSTACKTOP - PGSIZE), 0, PFTEMP, PTE_P|PTE_U|PTE_W);
	if(r < 0)
	{
		panic("sys_page_map failed");
	}
	// r = sys_page_map(childid, (void*)(UXSTACKTOP - PGSIZE), PTE_P|PTE_U|PTE_W);
	// if(r < 0)
	// {
	// 	panic("sys_page_map failed");
	// }
	r = sys_env_set_pgfault_upcall(childid, thisenv->env_pgfault_upcall);
    if(r == -1) 
	{
        panic("child process env_set_pgfault failed\n");
    }
	r = sys_env_set_status(childid, ENV_RUNNABLE);
    if(r < 0) {
        return -1;
    }
	return childid;
	// panic("fork not implemented");
}

// Challenge!
int
sfork(void)
{
	panic("sfork not implemented");
	return -E_INVAL;
}
