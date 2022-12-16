// Lab 3 template file
.data

.global login_name
login_name:
    .asciz "rmsundar"

.global puid
puid:
    .asciz "0032402630"

.balign 4

.equ TEST_SORT,         0x1
.equ TEST_STRCONCAT,    0x2
.equ TEST_FIB,          0x4
.equ TEST_BSEARCH,      0x8
.equ TEST_ALL,          (TEST_SORT | TEST_STRCONCAT | TEST_FIB | TEST_BSEARCH)

// Replace the TEST_ALL with the tests you want to run
// OR expression also support like the TEST_ALL above
// i.e. replace the TEST_ALL below with TEST_SORT | TEST_STRCONCAT
//      will test on the sort and strconcat
.global test
test:
    .word TEST_ALL


// Align to 4bytes boundary as we have a string above
.balign 4

.text
.global asm_sort_int
asm_sort_int:
    /* void asm_sort_int(int64_t* arr, uint64_t n)
     * relies on `qsort` in C standard library to 
     * sort in ascending order
     **/

    /* Enter your code after this comment */
	sub sp, sp, #16
	str lr, [sp]
	str x0, [sp, #8]

	mov x2, #8
    ldr x3, =asm_cmp

	bl qsort

	ldr x0, [sp, #8]
	ldr lr, [sp]
   	add sp, sp, #16
    /* Enter your code above this comment */
    ret

.global asm_cmp
asm_cmp:
    // int asm_cmp(const void * a, const void * b)
    // Compare function to int64_t
    // used for qsort
    /* Enter your code after this comment */
	ldr x0, [x0]
	ldr x1, [x1]

	sub x0, x0, x1

	cmp x0, #0
	b.GE asm_cmp_else
		mov x0, #-1
		ret
	asm_cmp_else:
		mov x0, #1

    /* Enter your code above this comment */
    ret

.global asm_strconcat
asm_strconcat:
    /* char* asm_strconcat(char * str1, char * str2)
     * First assign memory space with `malloc`, 
     * concatenating `str1` and `str2`, 
     * and return the resulted string.
     **/
    /* Enter your code after this comment */
	sub sp, sp, #16
	str lr, [sp]
	mov x19, x0 // char *str1
	mov x20, x1 // char *str2

	mov x0, x19
	bl strlen
	mov x21, x0 // int n1

	mov x0, x20
	bl strlen
	mov x22, x0 // int n2

	add x23, x21, x22
	add x23, x23, #1 // int size = n1 + n2 + 1

	mov x0, x23
	bl malloc
	mov x24, x0 // char * buf

	mov x0, x24
	mov x1, x19
	mov x2, x21
	bl memcpy

	add x0, x0, x21
	mov x1, x20
	mov x2, x22
	bl memcpy

	//buf[size - 1] = '\0' ??
	sub x0, x0, x21
	sub x23, x23, #1
	mov x5, #0
	strb w5, [x0, x23]

	ldr lr, [sp]
	add sp, sp, #16
    /* Enter your code above this comment */
    ret

.global asm_fib
asm_fib:
    /* uint64_t asm_fib(uint64_t n)
     * accept an index term `n` and return 
     * the Fn fibonacci term (F0 = 0, F1 = 1)
     **/

    /* Enter your code after this comment */
	sub sp, sp, #32
	str lr, [sp, #8]
	mov x2, x0 // use x2 to store n since x0 used for function return/pass


	cmp x0, #2
	b.GE asm_fib_else
		add sp, sp, #32
		b asm_fib_return
	asm_fib_else:
		// asm_fib(n-1)
		sub x2, x2, #1 // n-1
		mov x0, x2
		str x2, [sp] // store x2 since it may be modified in call
		bl asm_fib
		mov x1, x0 // store asm_fib(n-1) in x1
		ldr x2, [sp] // restore x2 = n-1

		// asm_fib(n-2)
		sub x0, x2, #1 // x2 = n-2
		str x1, [sp, #16] // store x1 since it may be modified in call
		str x2, [sp] // store x2 since it may be modified in call
		bl asm_fib
		ldr x1, [sp, #16] // restore asm_fib(n-1)
		add x1, x1, x0 // x1 = asm_fib(n - 1) + asm_fib(n - 2)
		ldr lr, [sp, #8] // restore lr to know where to return to
		add sp, sp, #32 // done with x0, x1, x2. pop from stack
		mov x0, x1


	asm_fib_return:
    /* Enter your code above this comment */
    ret

.global asm_bsearch
asm_bsearch:
    /* int64_t asm_bsearch(int *arr, int key, 
                    int64_t start,
                    int64_t end)
     * Return the index of the element in the array
     * if the element does not exist, return -1 instead
     * arr: integer array to be searched
     * key: the element we want to search on
     * start: start index of subarray, inclusive
     * end: end index of subarray, inclusiveloop through an entire string and only convert
     **/

    /* Enter your code after this comment */
    sub sp, sp, #64
	str lr, [sp]

	// move arguments since x0-x3 are re-used for function calls
	mov x21, x0
	mov x22, x1
	mov x23, x2
	mov x24, x3

	cmp x2, x3
	b.LE asm_bsearch_else1
		// start > end
		mov x0, #-1
		b asm_bsearch_ret
	asm_bsearch_else1:
		add x19, x2, x3
		lsr x19, x19, #1 // mid = (end + start) / 2

		ldr w20, [x0, x19, lsl#2] // x20 = arr[mid]

		// store since function call will change values
		str x21, [sp, #8]
		str x22, [sp, #16]
		str x23, [sp, #24]
		str x24, [sp, #32]
		str x19, [sp, #40]
		str x20, [sp, #48]

		cmp x20, x1
		b.GE asm_bsearch_cond2
			// arr[mid] < key
			add x2, x19, #1
			bl asm_bsearch
			b asm_bsearch_ret
		asm_bsearch_cond2:
			b.EQ asm_bsearch_cond3
			// arr[mid] > key
			sub x3, x19, #1
			bl asm_bsearch
			b asm_bsearch_ret
		asm_bsearch_cond3:
			// arr[mid] = key
			mov x0, x19
	asm_bsearch_ret:
		// restore values
		ldr lr, [sp]
		//ldr x0, [sp, #8]
		ldr x1, [sp, #16]
		ldr x2, [sp, #24]
		ldr x3, [sp, #32]
		ldr x19, [sp, #40]
		ldr x20, [sp, #48]
		add sp, sp, #64
    /* Enter your code above this comment */
    ret
