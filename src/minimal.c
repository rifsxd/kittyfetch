#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "version.h"

void kittyfetchminimal(int verbose, int isBunny) {
    if (verbose) {
        printf("\n");
        if (isBunny) {
            printf("\033[92m ^-^ Purr! This is bunnyfetch %s, your friendly system information display made with love by RifsxD! <3\033[0m\n\n", VERSION);
        } else {
            printf("\033[92m >-< Meow! This is kittyfetch %s, your friendly system information display made with love by RifsxD! <3\033[0m\n\n", VERSION);
        }
    }

    if (isBunny) {
        // Bunny printf
        printf(
            "            \n"
            " \033[3m%s\n"
            "            \n"
            "            %s\n"
            "            %s\n"
            "   \033[38;5;15m(\\ /)\033[0m    %s\n"
            "   \033[38;5;15m( . .)\033[0m   %s\n"
            "   \033[38;5;15mc(\033[38;5;211m%c\033[\033[38;5;15m)(\033[38;5;211m%c\033[\033[38;5;15m)\033[0m  %s\n\n",
            getRandomGreetingBunny(),
            titleinf(),
            osinf(),
            kernelinf(),
            shellinf(),
            '"', '"',
            wminf()
        );
    } else {
        // Default kitty printf
        printf(
            "            \n"
            " \033[3m%s\n"
            "            \n"
            "            %s\n"
            "   \033[38;5;94m/\\_/\\\033[0m    %s\n"
            "  \033[38;5;15m( >.< )\033[0m   %s\n"
            "   \033[38;5;94m= ^ =\033[0m    %s\n"
            "  \033[38;5;15m~(\033[38;5;211m♥\033[\033[38;5;15m)(\033[38;5;211m♥\033[38;5;15m)   %s\n\n",
            getRandomGreeting(),
            titleinf(),
            osinf(),
            kernelinf(),
            shellinf(),
            wminf()
        );
    }

    printf("         ");
    for (int i = 0; i < 8; i++) {
        printf("\033[4%dm   ", i);
    }
    printf("\033[0m\n         ");
    for (int i = 0; i < 8; i++) {
        printf("\033[10%dm   ", i);
    }
    printf("\033[0m\n\n");
}