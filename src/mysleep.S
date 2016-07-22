.syntax unified
.cpu cortex-m3
.thumb

.global mysleep
.type  mysleep, %function

/*
	subs	r0, r0, #12
	bls		mysleep_end
	lsrs	r0, r0, #2
*/

mysleep:
	subs	r0, r0, #29
	bls		mysleep_end
	lsrs	r0, r0, #3
	beq.n mysleep_end
    movw r1, #:lower16:mysleep_ram
    movt r1, #:upper16:mysleep_ram
	bx r1
	mysleep_end:
	bx lr

.section .ramcode.mysleep,"ax",%progbits
.type  mysleep_ram, %function
mysleep_ram:
	mysleep_loop:
		subs	r0, #1
		nop
		bne.n	mysleep_loop
	bx	lr


	/* 16  für 1 Durchlauf
	 20 für 2
	 24 für 3 */
