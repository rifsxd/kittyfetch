#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include <sys/utsname.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>

#define VERSION "1.0.0"

// Function declarations
void kittyfetch(int verbose);
char* titleinf();
char* osinf();
char* kernelinf();
char* shellinf();
char* wminf();
char* getRandomGreeting();


int main(int argc, char *argv[]) {
    int verbose = 0;

    // Check for the -v flag
    if (argc > 1 && strcmp(argv[1], "-v") == 0) {
        verbose = 1;
    }

    srand(time(NULL));

    kittyfetch(verbose);
    return 0;
}

void kittyfetch(int verbose) {
    if (verbose) {
        printf("\n");
        printf("\033[92m >-< Meow! This is kittyfetch %s, your friendly system information display made with love by RifsxD! <3\033[0m\n\n", VERSION);
    }

    printf(
        "            \n"
        " \033[3m%s\n"
        "            \n"
        "            %s\n"
        "   \033[92m/\\_/\\\033[0m    %s\n"
        "  \033[93m( >.< )\033[0m   %s\n"
        "   \033[94m= ^ =\033[0m    %s\n"
        "  \033[95m~(\033[95m♥\033[95m)(\033[95m♥\033[95m)   %s\n"
        "            \n",
        getRandomGreeting(),
        titleinf(),
        osinf(),
        kernelinf(),
        shellinf(),
        wminf()
    );

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

char* getRandomGreeting() {
    char* greetings[] = {
        "\033[92m Meow! =>.<=\033[0m",
        "\033[92m Hello there! :D\033[0m",
        "\033[92m Greetings! :)\033[0m",
        "\033[92m Hey! >-<\033[0m",
        "\033[92m Hiya! ;>\033[0m",
        "\033[92m Yo! :3\033[0m",
        "\033[92m Hi! ^_^\033[0m",
        "\033[92m Hewwo! <3\033[0m"
    };

    return greetings[rand() % (sizeof(greetings) / sizeof(greetings[0]))];
}


char* titleinf() {
    char* title = malloc(256);
    char username[256];
    char hostname[256];
    getlogin_r(username, sizeof(username));
    gethostname(hostname, sizeof(hostname));
    snprintf(title, 256, "\033[31m%s\033[0m", strcat(strcat(username, "@"), hostname));
    return title;
}

char* osinf() {
    char* osInfo = malloc(256);
    FILE* fp = fopen("/etc/os-release", "r");
    if (fp) {
        char line[256];
        while (fgets(line, sizeof(line), fp)) {
            if (strstr(line, "PRETTY_NAME")) {
                char* name = strchr(line, '=') + 2;  // Skip the '=' and space characters
                name[strlen(name) - 2] = '\0';  // Remove the trailing newline and quote characters
                snprintf(osInfo, 256, "\033[32mOS \033[0m%s", name);
                break;
            }
        }
        fclose(fp);
    } else {
        snprintf(osInfo, 256, "\033[32mOS \033[0m%s", "Unknown");
    }
    return osInfo;
}

char* kernelinf() {
    char* osInfo = malloc(256);
    
    struct utsname unameData;
    if (uname(&unameData) == 0) {
        snprintf(osInfo, 256, "\033[33mKernel \033[0m%s", unameData.release);
    } else {
        snprintf(osInfo, 256, "\033[33mKernel \033[0m%s", "Unknown");
    }

    return osInfo;
}

char* shellinf() {
    char* shell = malloc(256);
    char* shellenv = getenv("SHELL");
    char* shellname = shellenv ? strrchr(shellenv, '/') + 1 : "Unknown";
    snprintf(shell, 256, "\033[34mShell \033[0m%s", shellname);
    return shell;
}

char* wminf() {
    char* wm = malloc(256);

    char* waylandDisplay = getenv("WAYLAND_DISPLAY");
    if (waylandDisplay) {
        char* xdgDesktop = getenv("XDG_CURRENT_DESKTOP");
        snprintf(wm, 256, "\033[35mWM \033[0m%s", xdgDesktop ? xdgDesktop : "Unknown");
    } else {
        Display* display = XOpenDisplay(NULL);
        if (display) {
            Window root = DefaultRootWindow(display);

            Atom netSupportingWmCheckAtom = XInternAtom(display, "_NET_SUPPORTING_WM_CHECK", False);
            Atom netWmNameAtom = XInternAtom(display, "_NET_WM_NAME", False);
            Atom utf8StringAtom = XInternAtom(display, "UTF8_STRING", False);

            if (netSupportingWmCheckAtom != None && netWmNameAtom != None) {
                Atom actualType;
                int actualFormat;
                unsigned long nItems, bytesAfter;
                unsigned char* propValue = NULL;

                if (XGetWindowProperty(display, root, netSupportingWmCheckAtom, 0, 1, False,
                                       XA_WINDOW, &actualType, &actualFormat,
                                       &nItems, &bytesAfter, &propValue) == Success && propValue) {
                    Window supportingWmCheck = *((Window*)propValue);
                    XFree(propValue);

                    if (XGetWindowProperty(display, supportingWmCheck, netWmNameAtom, 0, 1024, False,
                                           utf8StringAtom, &actualType, &actualFormat,
                                           &nItems, &bytesAfter, &propValue) == Success && propValue) {
                        snprintf(wm, 256, "\033[35mWM \033[0m%s", (char*)propValue);
                        XFree(propValue);
                    } else {
                        snprintf(wm, 256, "\033[35mWM \033[0m%s", "Unknown");
                    }
                }
            }

            XCloseDisplay(display);
        } else {
            snprintf(wm, 256, "\033[35mWM \033[0m%s", "Unknown");
        }
    }

    return wm;
}
