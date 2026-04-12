#include "mywc.h"

int main(int argc, char *argv[]) {
    (void)argc;
    const char *filepath = "./text.txt";

    if (argv[1] != NULL) {
        filepath = argv[1];
    }

    process_file(filepath);
    return 0;
}
