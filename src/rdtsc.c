#include <unistd.h>
#include <sys/time.h>

extern unsigned long long get_cycles()
{
    long long out;
    asm volatile(
            "RDTSCP;"  /* outputs to EDX:EAX and the (unused) cpuid to ECX*/
            "SHLQ $32,%%rdx;"
            "ORQ %%rdx,%%rax;"
            "MOVQ %%rax,%0;"
            :"=r"(out)
            : /*no input*/
            :"rdx","rax", "rcx"
            );
    return out;
}

/**
 * Get time delta in microseconds.
 */
static long get_us_interval(struct timeval *start, struct timeval *end) {
    return (((end->tv_sec - start->tv_sec) * 1000000)
            + (end->tv_usec - start->tv_usec));
}

/**
 * This is a microbenchmark to get cpu frequency the process is running on. The
 * returned value is used to convert TSC counter values to microseconds.
 *
 * @return double.
 * @author cjiang
 *
 * see https://github.com/FriendsOfPHP/uprofiler
 */
extern double get_cpu_frequency() {
    struct timeval start;
    struct timeval end;
    long long tsc_start;
    long long tsc_end;

    if (gettimeofday(&start, 0)) {
        return 0.0;
    }

    tsc_start = get_cycles();

    /* Sleep for 5 miliseconds. Comparaing with gettimeofday's few microseconds
     * execution time, this should be enough. */
    usleep(5000);
    if (gettimeofday(&end, 0)) {
        return 0.0;
    }

    tsc_end = get_cycles();

    return (tsc_end - tsc_start) * 1.0 / (get_us_interval(&start, &end));
}
