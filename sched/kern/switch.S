/*
 * Your code here for context_switch
 *
 * It should restore the register values in the Trapframe with the 'iret' instruction.
 * This exits the kernel and starts executing some environment's code.
 *
 * This function does not return.
 */

.globl context_switch;
context_switch:


    add $4, %esp        # skip the return address (to env_run() in env.c)

    pop %esp            # now the stack = B's trapframe, and we can pop things out of it
                        # B = the soon-to-be-executed process

    popa                # restore values of general purpose registers
    pop %es             # restore value of es
    pop %ds             # restore value of ds

    add $8, %esp        # skip trapno and err fields of the trapframe

    iret                # return-from-trap instruction
                        # restore values of eip, cs, eflags, esp, and ss
                        # among other things:
                        #   - by restoring value of eip we jump to user space, to where we left execution
                        #   - by restoring value of cs we change the privilege level from 0 to 3
                        #   - by restoring value of esp we now point to the user stack

spin:
	jmp spin
