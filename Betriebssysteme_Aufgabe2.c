#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>

#define ITERATIONS 1000000

int main() {
    struct timespec start, end;
    long long min_time = LLONG_MAX;

    for (int i = 0; i < ITERATIONS; ++i) {
        clock_gettime(CLOCK_MONOTONIC, &start); // Startzeit messen
        getpid(); // System-Call
        clock_gettime(CLOCK_MONOTONIC, &end); // Endzeit messen

        // Berechne die Latenz in Nanosekunden
        long long diff = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
        if (diff < min_time) {
            min_time = diff;
        }
    }

    printf("Minimale Latenz für getpid(): %lld ns\n", min_time);

    return 0;
}
