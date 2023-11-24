#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "function.c"
#include "extended.c"
#include "minimal.c"

int main(int argc, char *argv[]) {
    int verbose = 0;
    int showBunny = 0;
    int minimal = 0;

    // Check for flags
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
            verbose = 1;
        } else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--bunny") == 0) {
            showBunny = 1;
        } else if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--minimal") == 0) {
            minimal = 1;
        } else (strcmp(argv[i], "--otherFlag") == 0);
    }

    srand(time(NULL));

    if (showBunny) {
        printf("\n");
        if (minimal) {
            kittyfetchminimal(verbose, 1); // Show minimal bunny
        } else {
            kittyfetch(verbose, 1); // Show bunny
        }
    } else {
        if (minimal) {
            kittyfetchminimal(verbose, 0); // Show minimal kitty
        } else {
            kittyfetch(verbose, 0); // Show default kitty
        }
    }

    return 0;
}