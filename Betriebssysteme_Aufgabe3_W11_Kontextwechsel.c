#include <windows.h>
#include <stdio.h>

#define ITERATIONS 1000000

DWORD WINAPI thread_function(LPVOID lpParam) {
    return 0;
}

int main() {
    HANDLE thread;
    LARGE_INTEGER start, end, frequency;
    long long total_time = 0;

    // Abfrage der Taktfrequenz des Hochauflösenden Zeitgebers
    QueryPerformanceFrequency(&frequency);

    for (int i = 0; i < ITERATIONS; ++i) {
        // Startzeit messen
        QueryPerformanceCounter(&start);
        // Thread erstellen und warten, bis er beendet ist
        thread = CreateThread(NULL, 0, thread_function, NULL, 0, NULL);
        WaitForSingleObject(thread, INFINITE);
        CloseHandle(thread);
        // Endzeit messen
        QueryPerformanceCounter(&end);

        // Berechne die Latenz in Nanosekunden
        long long diff = (end.QuadPart - start.QuadPart) * 1000000000LL / frequency.QuadPart;
        total_time += diff;
    }

    // Berechne die durchschnittliche Kontextwechseldauer
    double avg_latency = (double)total_time / ITERATIONS;

    printf("Durchschnittliche Kontextwechseldauer unter Windows 11: %.2f ns\n", avg_latency);

    return 0;
}
