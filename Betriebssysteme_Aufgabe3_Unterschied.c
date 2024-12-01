#include <windows.h>
#include <stdio.h>

#define ITERATIONS 1000000

DWORD WINAPI thread_function(LPVOID lpParam) {
    return 0;
}

void dummy_function() {
    // Leere Funktion, um die Zeit ohne Kontextwechsel zu messen
}

int main() {
    HANDLE thread;
    LARGE_INTEGER start, end, frequency;
    long long total_time_with_context_switch = 0;
    long long total_time_without_context_switch = 0;

    // Abfrage der Taktfrequenz des Hochauflösenden Zeitgebers
    QueryPerformanceFrequency(&frequency);

    // Messen der Zeit mit Kontextwechsel
    for (int i = 0; i < ITERATIONS; ++i) {
        QueryPerformanceCounter(&start);
        thread = CreateThread(NULL, 0, thread_function, NULL, 0, NULL);
        WaitForSingleObject(thread, INFINITE);
        CloseHandle(thread);
        QueryPerformanceCounter(&end);

        long long diff = (end.QuadPart - start.QuadPart) * 1000000000LL / frequency.QuadPart;
        total_time_with_context_switch += diff;
    }

    // Messen der Zeit ohne Kontextwechsel
    for (int i = 0; i < ITERATIONS; ++i) {
        QueryPerformanceCounter(&start);
        dummy_function();
        QueryPerformanceCounter(&end);

        long long diff = (end.QuadPart - start.QuadPart) * 1000000000LL / frequency.QuadPart;
        total_time_without_context_switch += diff;
    }

    // Berechne die durchschnittliche Dauer mit und ohne Kontextwechsel
    double avg_latency_with_context_switch = (double)total_time_with_context_switch / ITERATIONS;
    double avg_latency_without_context_switch = (double)total_time_without_context_switch / ITERATIONS;
    double context_switch_time = avg_latency_with_context_switch - avg_latency_without_context_switch;

    printf("Durchschnittliche Kontextwechseldauer unter Windows 11: %.2f ns\n", avg_latency_with_context_switch);
    printf("Durchschnittliche Zeit ohne Kontextwechsel: %.2f ns\n", avg_latency_without_context_switch);
    printf("Isolierte Kontextwechseldauer: %.2f ns\n", context_switch_time);

    return 0;
}
