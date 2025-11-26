#include "parta.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * TODO: Describe what the function does
 */
struct pcb* init_procs(int* bursts, int blen) {
    if (blen <= 0) return NULL;

    struct pcb* procs = malloc(sizeof(struct pcb) * blen);

    for (int i = 0; i < blen; i++) {
        procs[i].pid = i;
        procs[i].burst_left = bursts[i];
        procs[i].wait = 0;
    }

    return procs;
}

/**
 * TODO: Describe what the function does
 */
void printall(struct pcb* procs, int plen) {
    for (int i = 0; i < plen; i++) {
        printf("P%d: burst_left=%d wait=%d\n",
               procs[i].pid, procs[i].burst_left, procs[i].wait);
    }
}

/**
 * TODO: Describe what the function does
 */
void run_proc(struct pcb* procs, int plen, int current, int amount) {
    if (current < 0 || current >= plen) return;

    if (procs[current].burst_left > 0) {
        procs[current].burst_left -= amount;
        if (procs[current].burst_left < 0) procs[current].burst_left = 0;
    }

    for (int i = 0; i < plen; i++) {
        if (i != current && procs[i].burst_left > 0) {
            procs[i].wait += amount;
        }
    }
}

/**
 * TODO: Describe what the function does
 */
int fcfs_run(struct pcb* procs, int plen) {
    int time = 0;

    for (int i = 0; i < plen; i++) {
        int burst = procs[i].burst_left;

        if (burst > 0) {
            run_proc(procs, plen, i, burst);
            time += burst;
        }
    }

    return time;
}

/**
 * TODO: Describe what the function does
 */
int rr_next(int current, struct pcb* procs, int plen) {
    int all_done = 1;
    for (int i = 0; i < plen; i++) {
        if (procs[i].burst_left > 0) {
            all_done = 0;
            break;
        }
    }
    if (all_done) return -1;

    int next = (current + 1) % plen;

    while (procs[next].burst_left == 0) {
        next = (next + 1) % plen;
    }

    return next;
}
/**
 * TODO: Describe what the function does
 */
int rr_run(struct pcb* procs, int plen, int quantum) {
    int time = 0;

    int current = 0;
    while (procs[current].burst_left == 0)
        current = rr_next(current, procs, plen);

    while (current != -1) {
        int burst = procs[current].burst_left;
        int run_amount = burst > quantum ? quantum : burst;

        run_proc(procs, plen, current, run_amount);
        time += run_amount;

        current = rr_next(current, procs, plen);
    }

    return time;
}

