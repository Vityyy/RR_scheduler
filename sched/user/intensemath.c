#include <inc/lib.h>

void
umain(int argc, char** argv) {
    uint32_t sum = 0;

    for (uint32_t i = 0; i < 10; i++) {
        for (uint32_t j = 0; j < 1000000; j++)
            sum += i;

        cprintf("Priority: %d\n", sys_env_get_prior());
    }
}
