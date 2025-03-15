#include <bcbasic/bcbasic_static.h>

#include <stdio.h>

int main(int argc, char** argv) {
    printf("argv[0]: %s\n", argv[0]);
    for (int i = 1; i < argc; ++i) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    return 0;
}
