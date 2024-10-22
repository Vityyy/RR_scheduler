#include <inc/assert.h>
#include <inc/x86.h>
#include <kern/spinlock.h>
#include <kern/env.h>
#include <kern/pmap.h>
#include <kern/monitor.h>
#include <inc/syscall.h>
#include "syscall.h"

void sched_halt(void);

#ifdef SCHED_ROUND_ROBIN
int
get_curenv_idx()
{
    int i = 0;
    while (i < NENV) {
        if (&envs[i] == curenv)
            break;
        ++i;
    }
    return i;
}
#endif

// Choose a user environment to run and run it.
void
sched_yield(void) {
#ifdef SCHED_ROUND_ROBIN
    // Implement simple round-robin scheduling.
    //
    // Search through 'envs' for an ENV_RUNNABLE environment in
    // circular fashion starting just after the env this CPU was
    // last running. Switch to the first such environment found.
    //
    // If no envs are runnable, but the environment previously
    // running on this CPU is still ENV_RUNNING, it's okay to
    // choose that environment.
    //
    // Never choose an environment that's currently running on
    // another CPU (env_status == ENV_RUNNING). If there are
    // no runnable environments, simply drop through to the code
    // below to halt the cpu.

    // Your code here - Round robin

    int curenv_idx = -1;
    int i = 0;
    struct Env *chosen = NULL;
    bool found = false;

    if (curenv) {
        curenv_idx = get_curenv_idx();
        if (curenv_idx != NENV - 1)
            i = curenv_idx + 1;
        else
            curenv_idx = -1;  // to avoid looping twice
    }

    while (i < NENV && !found) {
        if (envs[i].env_status == ENV_RUNNABLE) {
            chosen = &envs[i];
            found = true;
        }
        ++i;
    }

    i = 0;
    while (i < curenv_idx && !found) {
        if (envs[i].env_status == ENV_RUNNABLE) {
            chosen = &envs[i];
            found = true;
        }
        ++i;
    }

    if (!found && curenv && curenv->env_status == ENV_RUNNING)
        chosen = curenv;

#endif
    
#ifdef SCHED_PRIORITIES
    // Implement simple priorities scheduling.
    //
    // Environments now have a "priority" so it must be consider
    // when the selection is performed.
    //
    // Be careful to not fall in "starvation" such that only one
    // environment is selected and run every time.

    // Your code here - Priorities

    static uint32_t cicle_count = 0;

    if (cicle_count % 250 == 0)
        for (int i = 0; i < NENV; i++)
            envs[i].env_priority = ENV_DEFAULT_PRIORITY;

    // If the interruption was a timer interruption, we decrement thve curenv's priority by 1
    // (if it is runnable and its priority is not the lowest)
    uint32_t curenv_priority = 0;
    if (curenv && curenv->env_tf.tf_trapno == IRQ_OFFSET + IRQ_TIMER) {
        if (curenv->env_status == ENV_RUNNABLE && curenv->env_priority != 1)
            curenv->env_priority = curenv->env_priority - 1;
    }

    struct Env *chosen = NULL;
    uint32_t highest_priority = 0;

    for (int i = 0; i < NENV; i++) {
        if (envs[i].env_status == ENV_RUNNABLE && envs[i].env_priority > highest_priority) {
            highest_priority = envs[i].env_priority;
            chosen = &envs[i];
        }
    }

    ++cicle_count;

#endif

    // Without scheduler, keep runing the last environment while it exists
    // if (curenv) {
    // 	env_run(curenv);
    // }

    if (chosen)
        env_run(chosen); // never returns

    // sched_halt never returns
    sched_halt();
}

// Halt this CPU when there is nothing to do. Wait until the
// timer interrupt wakes it up. This function never returns.
//
void
sched_halt(void) {
    int i;

    // For debugging and testing purposes, if there are no runnable
    // environments in the system, then drop into the kernel monitor.
    for (i = 0; i < NENV; i++) {
        if ((envs[i].env_status == ENV_RUNNABLE ||
             envs[i].env_status == ENV_RUNNING ||
             envs[i].env_status == ENV_DYING))
            break;
    }
    if (i == NENV) {
        cprintf("No runnable environments in the system!\n");
        while (1)
            monitor(NULL);
    }

    // Mark that no environment is running on this CPU
    curenv = NULL;
    lcr3(PADDR(kern_pgdir));

    // Mark that this CPU is in the HALT state, so that when
    // timer interupts come in, we know we should re-acquire the
    // big kernel lock
    xchg(&thiscpu->cpu_status, CPU_HALTED);

    // Release the big kernel lock as if we were "leaving" the kernel
    unlock_kernel();

    // Once the scheduler has finishied it's work, print statistics on
    // performance. Your code here

    // Reset stack pointer, enable interrupts and then halt.
    asm volatile("movl $0, %%ebp\n"
                 "movl %0, %%esp\n"
                 "pushl $0\n"
                 "pushl $0\n"
                 "sti\n"
                 "1:\n"
                 "hlt\n"
                 "jmp 1b\n"
            :
            : "a"(thiscpu->cpu_ts.ts_esp0));
}
