// Lab 2 template file
.data
.global lowercase_string
lowercase_string:
    // Specify a string ending with '\0'
    .asciz "ece 362 is awesome!"

.global login_name
login_name:
    .asciz "rmsundar"

.global puid
puid:
    .asciz "0032402630"

// Align to 4bytes boundary as we have a string above
.balign 4

.text
.global asm_strlen
asm_strlen:
    /* uint64_t asm_strlen(char *str)
     * Take in a pointer to a string and return
     * its length up to the null terminating
     * character `\0`
     **/

    /* Enter your code after this comment */
	mov x2, #0 // counter for string length

	cbz x0, while1_end

	while1:
		ldrb w1, [x0, x2] // load in a character from array at x0 + x2 * 1-byte
		cbz x1, while1_end // if char = 0 (null), then end loop
		add x2, x2, #1
		b while1
	while1_end:
		mov x0, x2 // put counter value x2 in return argument x0
    /* Enter your code above this comment */
    ret

.global asm_fib
asm_fib:
    /* void asm_fib(int *arr, uint64_t length)
     * Accept a pointer to an array of integer and
     * the length of the array, then generate fibonacci
     * series starting at `0` and store the result
     * back to the array `arr` at corresponding indices.
     **/

    /* Enter your code after this comment */
    // INPUT ARGUMENTS
    // x0 = pointer to array
    // x1 = length of array

	cbz x0, for1_end // return if pointer = null
	cbz x1, for1_end // return if length = 0

	// Initial terms for the fib series
	mov x2, #0 // prev: Fn-2 term
	mov x3, #1 // curr: Fn-1 term
	mov x4, #0 // i of for-loop

	for1:
		// CONDITION
		cmp x4, x1
		b.HS for1_end // if i >= length, end loop. in other words, run loop while i < length

		// BODY
		if1:
			cmp x4, #0
			b.NE elif1
			// if i = 0, then...
			str w2, [x0, x4, lsl#2] // store 0 in arr[0]. str at byte x0 + i*4, since each element i is 4 bytes
			b for1_incr
		elif1:
			cmp x4, #1
			b.NE else1
			// if i = 1, then...
			str w3, [x0, x4, lsl#2] // store 1 in arr[1]. str at byte x0 + i*4, since each element i is 4 bytes
			b for1_incr
		else1:
			mov x5, x3 // temp = Fn-1
			add x3, x3, x2 // Fn = Fn-1 + Fn-2
			mov x2, x5 // Fn-2 = temp
			str w3, [x0, x4, lsl#2] // store Fn in arr[i]. str at byte x0 + i*4, since each element i is 4 bytes
			b for1_incr
		// INCREMENT
		for1_incr:
			add x4, x4, #1 // increment i
			b for1
	for1_end:
    /* Enter your code above this comment */
    ret

.global asm_toUppercase
asm_toUppercase:
    /* void asm_toUppercase(char *str)
     * loop through an entire string and only convert
     * the lowercase letter to uppercase, leaving the
     * rest of the string intact
     **/

    /* Enter your code after this comment */
	// INPUT ARGUMENTS
    // x0 = pointer to array

	cbz x0, while2_end // return if pointer = null

	mov x2, #0 // character pointer
    while2:
		ldrb w1, [x0, x2] // load in a character from array at x0 + x2 * 1byte
		cbz x1, while2_end // if char = 0 (null), then end loop

		if2_check1:
			// if char >= a, check second condition
			cmp x1, #97
			b.HS if2_check2
			// else, move on to next character
			b while2_incr
		if2_check2:
			// if char <= z, go to if body
			cmp x1, #122
			b.LS if2_then
			// else, move on to next character
			b while2_incr
		if2_then:
			sub x1, x1, #32 // convert char to uppercase
			strb w1, [x0, x2] // store in a character from array at x0 + x2 * 1byte
			b while2_incr
		while2_incr:
			add x2, x2, #1 // incrment
			b while2
    while2_end:
    /* Enter your code above this comment */
    ret
