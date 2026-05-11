#include <execinfo.h>
#include <stdio.h>

#ifdef DEBUG_LEVEL
#if DEBUG_LEVEL >= 3
#define DEBUG_PRINT(fmt, ...)                                                            \
    do {                                                                                 \
        printf("DEBUG: func=%s, line=%d, " fmt "\n", __func__, __LINE__, ##__VA_ARGS__); \
        void *trace[16];                                                                 \
        int trace_size = backtrace(trace, 16);                                           \
        backtrace_symbols_fd(trace, trace_size, fileno(stdout));                         \
    } while (0)
#elif DEBUG_LEVEL >= 2
#define DEBUG_PRINT(fmt, ...)                                                            \
    do {                                                                                 \
        printf("DEBUG: func=%s, line=%d, " fmt "\n", __func__, __LINE__, ##__VA_ARGS__); \
    } while (0)
#else
#define DEBUG_PRINT(fmt, ...)                                    \
    do {                                                         \
        printf("DEBUG: func=%s, line=%d\n", __func__, __LINE__); \
    } while (0)
#endif
#else
#define DEBUG_PRINT(fmt, ...) \
    do {                      \
    } while (0)
#endif

//! MUST BE ENSURE THE DEBUG_PRINT("x=%d", x) AT THE 48 LINE















void test() {
    int x = 42;
    DEBUG_PRINT("x=%d", x);
}

int main() {
    test();
    return 0;
}