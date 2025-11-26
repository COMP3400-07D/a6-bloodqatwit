#include "parta.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("ERROR: Missing arguments\n");
        return 1;
    }

    if (strcmp(argv[1], "fcfs") == 0) {
        int plen = argc - 2;
        if (plen <= 0) {
            printf("ERROR: Missing arguments\n");
            return 1;
        }

        int bursts[plen];
        for (int i = 0; i < plen; i++) bursts[i] = atoi(argv[i+2]);

        printf("Using FCFS\n\n");

        struct pcb* procs = init_procs(bursts, plen);
        fcfs_run(procs, plen);

        for (int i = 0; i < plen; i++)
            printf("Accepted P%d: Burst %d\n", i, bursts[i]);

        double avg = 0;
        for (int i = 0; i < plen; i++)
            avg += procs[i].wait;
        avg /= plen;

        printf("Average wait time: %.2f\n", avg);
        free(procs);
        return 0;
    }

    if (strcmp(argv[1], "rr") == 0) {
        if (argc < 4) {
            printf("ERROR: Missing arguments\n");
            return 1;
        }

        int quantum = atoi(argv[2]);
        int plen = argc - 3;

        if (plen <= 0) {
            printf("ERROR: Missing arguments\n");
            return 1;
        }

        int bursts[plen];
        for (int i = 0; i < plen; i++) bursts[i] = atoi(argv[i+3]);

        printf("Using RR(%d).\n\n", quantum);

        struct pcb* procs = init_procs(bursts, plen);
        rr_run(procs, plen, quantum);

        for (int i = 0; i < plen; i++)
            printf("Accepted P%d: Burst %d\n", i, bursts[i]);

        double avg = 0;
        for (int i = 0; i < plen; i++)
            avg += procs[i].wait;
        avg /= plen;

        printf("Average wait time: %.2f\n", avg);
        free(procs);
        return 0;
    }

    printf("ERROR: Missing arguments\n");
    return 1;
}
