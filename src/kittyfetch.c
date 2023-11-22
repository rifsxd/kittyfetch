#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include <sys/utsname.h>
#include <sys/statvfs.h>

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>

#define VERSION "1.0.0"

#ifdef LEGACY
#define USER "User"
#define OS "OS"
#define PACKAGES "Packages"
#define KERNEL "Kernel"
#define UPTIME "Uptime"
#define SHELL "Shell"
#define CPU "CPU"
#define GPU "GPU"
#define DISK "Disk"
#define RAM "RAM"
#define WM "WM"
#else
#define USER ""
#define OS "󰍹"
#define PACKAGES "󰏓"
#define KERNEL "󰌽"
#define UPTIME "󱑁"
#define SHELL ""
#define CPU ""
#define GPU "󰿵"
#define DISK "󰋊"
#define RAM "󰇻"
#define WM "󰖲"
#endif

// Function declarations
void kittyfetch(int verbose, int isBunny);
void kittyfetchminimal(int verbose, int isBunny);
char *titleinf();
char *uptimeinf();
char *osinf();
char *raminf();
char *kernelinf();
char *shellinf();
char *wminf();
char *getRandomGreeting();
char *getRandomGreetingBunny();
char *packageinf();
char *storageinf();
char *cpuinf();
char *gpuinf();

int main(int argc, char *argv[]) {
    int verbose = 0;
    int showBunny = 0;
    int minimal = 0;

    // Check for flags
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0) {
            verbose = 1;
        } else if (strcmp(argv[i], "--bunny") == 0) {
            showBunny = 1;
        } else if (strcmp(argv[i], "--minimal") == 0) {
            minimal = 1;
        } else if (strcmp(argv[i], "--otherFlag") == 0) {
            // Handle other flag logic
            // You can add more flags as needed
        }
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

void kittyfetch(int verbose, int isBunny) {
    if (verbose) {
        printf("\n");
        if (isBunny) {
            printf("\033[92m (^-^) Purr! This is bunnyfetch %s, your friendly system information display made with love by RifsxD! <3\033[0m\n\n", VERSION);
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
            "            %s\n"
            "            %s\n"
            "   \033[38;5;15m(\\ /)\033[0m    %s\n"
            "   \033[38;5;15m( . .)\033[0m   %s\n"
            "   \033[38;5;15mc(\033[38;5;211m%c\033[\033[38;5;15m)(\033[38;5;211m%c\033[\033[38;5;15m)\033[0m  %s\n"
            "            %s\n"
            "            %s\n"
            "            %s\n"
            "            %s\n\n",
            getRandomGreetingBunny(),
            titleinf(),
            osinf(),
            packageinf(),
            kernelinf(),
            uptimeinf(),
            shellinf(),
            '"', '"',
            cpuinf(),
            gpuinf(),
            storageinf(),
            raminf(),
            wminf()
        );
    } else {
        // Default kitty printf
        printf(
            "            \n"
            " \033[3m%s\n"
            "            \n"
            "            %s\n"
            "            %s\n"
            "            %s\n"
            "            %s\n"
            "   \033[38;5;94m/\\_/\\\033[0m    %s\n"
            "  \033[38;5;15m( >.< )\033[0m   %s\n"
            "   \033[38;5;94m= ^ =\033[0m    %s\n"
            "  \033[38;5;15m~(\033[38;5;211m♥\033[\033[38;5;15m)(\033[38;5;211m♥\033[38;5;15m)   %s\n"
            "            %s\n"
            "            %s\n"
            "            %s\n\n",
            getRandomGreeting(),
            titleinf(),
            osinf(),
            packageinf(),
            kernelinf(),
            uptimeinf(),
            shellinf(),
            cpuinf(),
            gpuinf(),
            storageinf(),
            raminf(),
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
            "   \033[38;5;15m(\\ /)\033[0m    %s\n"
            "   \033[38;5;15m( . .)\033[0m   %s\n"
            "   \033[38;5;15mc(\033[38;5;211m%c\033[\033[38;5;15m)(\033[38;5;211m%c\033[\033[38;5;15m)\033[0m  %s\n"
            "            %s\n\n",
            getRandomGreetingBunny(),
            titleinf(),
            osinf(),
            kernelinf(),
            '"', '"',
            shellinf(),
            
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

char *getRandomGreeting() {
    char *greetings[] = {
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

char *getRandomGreetingBunny() {
    char *greetings[] = {
        "\033[92m Purr! ( . .)\033[0m",
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

char *titleinf() {
    char *title = malloc(256);
    if (title) {
        char username[256];
        char hostname[256];
        if (getlogin_r(username, sizeof(username)) == 0 && gethostname(hostname, sizeof(hostname)) == 0) {
            snprintf(title, 256, "\033[31m%s \033[31m%s\033[0m", USER, strcat(strcat(username, "@"), hostname));
        } else {
            snprintf(title, 256, "\033[31m%s \033[31m%s\033[0m", USER, "Unknown");
        }
    } else {
        snprintf(title, 256, "\033[31m%s \033[31m%s\033[0m", USER, "Unknown");
    }

    return title;
}

char *osinf() {
    char *osInfo = malloc(256);
    if (osInfo) {
        FILE *fp = fopen("/etc/os-release", "r");
        if (fp) {
            char line[256];
            while (fgets(line, sizeof(line), fp)) {
                if (strstr(line, "NAME")) {
                    char *name = strchr(line, '=') + 2; // Skip the '=' and space characters
                    name[strlen(name) - 2] = '\0';    // Remove the trailing newline and quote characters
                    snprintf(osInfo, 256, "\033[32m%s \033[0m%s", OS, name);
                    break;
                }
            }
            fclose(fp);
        } else {
            snprintf(osInfo, 256, "\033[32m%s \033[0m%s", OS, "Unknown");
        }
    } else {
        snprintf(osInfo, 256, "\033[32m%s \033[0m%s", OS, "Unknown");
    }

    return osInfo;
}

char *kernelinf() {
    char *osInfo = malloc(256);

    if (osInfo) {
        struct utsname unameData;
        if (uname(&unameData) == 0) {
            snprintf(osInfo, 256, "\033[33m%s \033[0m%s", KERNEL, unameData.release);
        } else {
            snprintf(osInfo, 256, "\033[33m%s \033[0m%s", KERNEL, "Unknown");
        }
    } else {
        snprintf(osInfo, 256, "\033[33m%s \033[0m%s", KERNEL, "Unknown");
    }

    return osInfo;
}

char *shellinf() {
    char *shell = malloc(256);
    if (shell) {
        char *shellenv = getenv("SHELL");
        if (shellenv) {
            char *shellname = strrchr(shellenv, '/');
            if (shellname) {
                // If there's a '/', use the string after it
                snprintf(shell, 256, "\033[34m%s \033[0m%s", SHELL, shellname + 1);
            } else {
                // If no '/', consider the whole string as the shell name
                snprintf(shell, 256, "\033[34m%s \033[0m%s", SHELL, shellenv);
            }
        } else {
            snprintf(shell, 256, "\033[34m%s \033[0m%s", SHELL, "Unknown");
        }
    } else {
        snprintf(shell, 256, "\033[34m%s \033[0m%s", SHELL, "Unknown");
    }

    return shell;
}


char *wminf() {
    char *wm = malloc(256);

    if (wm) {
        char *waylandDisplay = getenv("WAYLAND_DISPLAY");
        if (waylandDisplay) {
            char *xdgDesktop = getenv("XDG_CURRENT_DESKTOP");
            snprintf(wm, 256, "\033[38;5;93m%s \033[0m%s", WM, xdgDesktop ? xdgDesktop : "Unknown");
        } else {
            Display *display = XOpenDisplay(NULL);
            if (display) {
                Window root = DefaultRootWindow(display);

                Atom netSupportingWmCheckAtom = XInternAtom(display, "_NET_SUPPORTING_WM_CHECK", False);
                Atom netWmNameAtom = XInternAtom(display, "_NET_WM_NAME", False);
                Atom utf8StringAtom = XInternAtom(display, "UTF8_STRING", False);

                if (netSupportingWmCheckAtom != None && netWmNameAtom != None) {
                    Atom actualType;
                    int actualFormat;
                    unsigned long nItems, bytesAfter;
                    unsigned char *propValue = NULL;

                    if (XGetWindowProperty(display, root, netSupportingWmCheckAtom, 0, 1, False,
                                           XA_WINDOW, &actualType, &actualFormat,
                                           &nItems, &bytesAfter, &propValue) == Success && propValue) {
                        Window supportingWmCheck = *((Window *)propValue);
                        XFree(propValue);

                        if (XGetWindowProperty(display, supportingWmCheck, netWmNameAtom, 0, 1024, False,
                                               utf8StringAtom, &actualType, &actualFormat,
                                               &nItems, &bytesAfter, &propValue) == Success && propValue) {
                            snprintf(wm, 256, "\033[38;5;93m%s \033[0m%s", WM, (char *)propValue);
                            XFree(propValue);
                        } else {
                            snprintf(wm, 256, "\033[38;5;93m%s \033[0m%s", WM, "Unknown");
                        }
                    }
                }

                XCloseDisplay(display);
            } else {
                snprintf(wm, 256, "\033[38;5;93m%s \033[0m%s", WM, "Unknown");
            }
        }
    } else {
        snprintf(wm, 256, "\033[38;5;93m%s \033[0m%s", WM, "Unknown");
    }

    return wm;
}

char *uptimeinf() {
    char *uptime = malloc(256);
    if (uptime) {
        FILE *uptimeFile = fopen("/proc/uptime", "r");
        if (uptimeFile) {
            double uptimeValue;
            fscanf(uptimeFile, "%lf", &uptimeValue);
            fclose(uptimeFile);

            int hours = (int)(uptimeValue / 3600);
            int minutes = (int)((uptimeValue - hours * 3600) / 60);

            snprintf(uptime, 256, "\033[36m%s \033[0m%dh %dm", UPTIME, hours, minutes);
        } else {
            snprintf(uptime, 256, "\033[36m%s \033[0m%s", UPTIME, "Unknown");
        }
    } else {
        snprintf(uptime, 256, "\033[36m%s \033[0m%s", UPTIME, "Unknown");
    }

    return uptime;
}

char *raminf() {
    char *ram = malloc(256);
    if (ram) {
        FILE *meminfo = fopen("/proc/meminfo", "r");
        if (meminfo) {
            long total_mem = 0, free_mem = 0, buffers = 0, cached = 0;
            char line[256];

            while (fgets(line, sizeof(line), meminfo) != NULL) {
                if (sscanf(line, "MemTotal: %ld kB", &total_mem) == 1) {
                    continue;
                }
                if (sscanf(line, "MemFree: %ld kB", &free_mem) == 1) {
                    continue;
                }
                if (sscanf(line, "Buffers: %ld kB", &buffers) == 1) {
                    continue;
                }
                if (sscanf(line, "Cached: %ld kB", &cached) == 1) {
                    continue;
                }
            }

            if (total_mem > 0 && free_mem > 0) {
                // Adjust based on your preference
                long used_mem = total_mem - free_mem - buffers - cached;
                snprintf(ram, 256, "\033[38;5;198m%s \033[0m%ld MB / %ld MB", RAM, used_mem / 1024, total_mem / 1024);
            } else {
                snprintf(ram, 256, "\033[38;5;198m%s \033[0m%s", RAM, "Unknown");
            }

            fclose(meminfo);
        } else {
            snprintf(ram, 256, "\033[38;5;198m%s \033[0m%s", RAM, "Unknown");
        }
    } else {
        snprintf(ram, 256, "\033[38;5;198m%s \033[0m%s", RAM, "Unknown");
    }

    return ram;
}

char *storageinf() {
    char *storage = malloc(256);
    if (storage) {
        struct statvfs vfs;
        if (statvfs("/", &vfs) == 0) {
            long total_space = (long)vfs.f_frsize * vfs.f_blocks;
            long used_space = (long)vfs.f_frsize * (vfs.f_blocks - vfs.f_bfree);

            snprintf(storage, 256, "\033[95m%s \033[0m%ld MB / %ld MB", DISK, used_space / (1024 * 1024), total_space / (1024 * 1024));
        } else {
            snprintf(storage, 256, "\033[95m%s \033[0m%s", DISK, "Unknown");
        }
    } else {
        snprintf(storage, 256, "\033[95m%s \033[0m%s", DISK, "Unknown");
    }

    return storage;
}

char *getLSBReleaseInfo() {
    char *lsbInfo = malloc(256);
    if (lsbInfo) {
        FILE *lsbReleaseFile = popen("lsb_release -si 2>/dev/null", "r");
        if (lsbReleaseFile) {
            if (fgets(lsbInfo, 256, lsbReleaseFile) != NULL) {
                // Remove newline character
                lsbInfo[strcspn(lsbInfo, "\n")] = 0;
            } else {
                snprintf(lsbInfo, 256, "%s", "Unknown");
            }
            pclose(lsbReleaseFile);
        } else {
            snprintf(lsbInfo, 256, "%s", "Unknown");
        }
    } else {
        snprintf(lsbInfo, 256, "%s", "Unknown");
    }
    return lsbInfo;
}

char *packageinf() {
    char *lsbInfo = getLSBReleaseInfo();

    char *packageInfo = malloc(256);
    if (packageInfo) {
        int pkgCount = 0;

        // Check the Linux distribution using os-release
        FILE *osReleaseFile = popen("cat /etc/os-release | grep '^ID_LIKE=' | cut -d'=' -f2 && cat /etc/os-release | grep '^ID=' | cut -d'=' -f2", "r");
        if (osReleaseFile) {
            char distro[64];
            if (fgets(distro, sizeof(distro), osReleaseFile) != NULL) {
                // Remove newline character
                distro[strcspn(distro, "\n")] = 0;

                // Get package info based on the distribution
                if (strstr(distro, "arch") != NULL) {
                    // Count Arch Linux packages
                    FILE *archFile = popen("pacman -Qq", "r");
                    if (archFile) {
                        while (fgets(packageInfo, 256, archFile) != NULL) {
                            pkgCount++;
                        }
                        pclose(archFile);

                        snprintf(packageInfo, 256, "\033[38;5;208m%s \033[0m%d (pacman)", PACKAGES, pkgCount);
                    } else {
                        snprintf(packageInfo, 256, "\033[38;5;208m%s \033[0m%s", PACKAGES, "Unknown");
                    }
                } else if (strstr(distro, "fedora") != NULL || strstr(distro, "opensuse") != NULL || strstr(distro, "suse") != NULL || strstr(distro, "rhel") != NULL) {
                    // Count RPM packages
                    FILE *rpmFile = popen("rpm -qa", "r");
                    if (rpmFile) {
                        while (fgets(packageInfo, 256, rpmFile) != NULL) {
                            pkgCount++;
                        }
                        pclose(rpmFile);

                        snprintf(packageInfo, 256, "\033[38;5;208m%s \033[0m%d (rpm)", PACKAGES, pkgCount);
                    } else {
                        snprintf(packageInfo, 256, "\033[38;5;208m%s \033[0m%s", PACKAGES, "Unknown");
                    }
                } else if (strstr(distro, "nixos") != NULL) {
                    // Count NixOS packages
                    FILE *nixFile = popen("echo $(( $(nix-store -qR /run/current-system/sw | wc -l) + $(nix-store -qR /etc/profiles/per-user/$USER | wc -l) ))", "r");
                    if (nixFile) {
                        if (fgets(packageInfo, 256, nixFile) != NULL) {
                            pkgCount = atoi(packageInfo);
                            snprintf(packageInfo, 256, "\033[38;5;208m%s \033[0m%d (nix)", PACKAGES, pkgCount);
                        } else {
                            snprintf(packageInfo, 256, "\033[38;5;208m%s \033[0m%s", PACKAGES, "Unknown");
                        }
                        pclose(nixFile);
                    } else {
                        snprintf(packageInfo, 256, "\033[38;5;208m%s \033[0m%s", PACKAGES, "Unknown");
                    }
                } else if (strstr(distro, "debian") != NULL || strstr(distro, "ubuntu") != NULL || strstr(distro, "linuxmint") != NULL || strstr(distro, "popos") != NULL) {
                    // Count Debian/Ubuntu packages
                    FILE *debFile = popen("dpkg -l | grep ^ii | wc -l", "r");
                    if (debFile) {
                        if (fgets(packageInfo, 256, debFile) != NULL) {
                            pkgCount = atoi(packageInfo);
                            snprintf(packageInfo, 256, "\033[38;5;208m%s \033[0m%d (deb)", PACKAGES, pkgCount);
                        } else {
                            snprintf(packageInfo, 256, "\033[38;5;208m%s \033[0m%s", PACKAGES, "Unknown");
                        }
                        pclose(debFile);
                    } else {
                        snprintf(packageInfo, 256, "\033[38;5;208mm%s \033[0m%s", PACKAGES, "Unknown");
                    }
                } else {
                    snprintf(packageInfo, 256, "\033[38;5;208m%s \033[0m%s", PACKAGES, "Unknown");
                }
            } else {
                snprintf(packageInfo, 256, "\033[38;5;208m%s \033[0m%s", PACKAGES, "Unknown");
            }
            pclose(osReleaseFile);
        } else {
            snprintf(packageInfo, 256, "\033[38;5;208m%s \033[0m%s", PACKAGES, "Unknown");
        }
        free(lsbInfo);
    } else {
        snprintf(packageInfo, 256, "\033[38;5;208m%s \033[0m%s", PACKAGES, "Unknown");
    }

    return packageInfo;
}

char *cpuinf() {
    char *cpu = malloc(256);
    if (cpu) {
        FILE *cpuinfo = fopen("/proc/cpuinfo", "r");
        if (cpuinfo) {
            char line[256];
            int cpuCount = 0;

            while (fgets(line, sizeof(line), cpuinfo) != NULL) {
                if (strstr(line, "model name")) {
                    cpuCount++;
                    char *model = strchr(line, ':') + 2;
                    model[strlen(model) - 1] = '\0'; // Remove the trailing newline
                    snprintf(cpu, 256, "\033[95m%s \033[0m%s (x%d)", CPU, model, cpuCount);
                }
            }

            fclose(cpuinfo);
        } else {
            snprintf(cpu, 256, "\033[95m%s \033[0m%s", CPU, "Unknown");
        }
    } else {
        snprintf(cpu, 256, "\033[95m%s \033[0m%s", CPU, "Unknown");
    }

    return cpu;
}

char *gpuinf() {
    char *gpu = malloc(256);
    if (gpu) {
        FILE *lspci = popen("lspci | grep -i vga", "r");
        if (lspci) {
            char line[256];

            if (fgets(line, sizeof(line), lspci) != NULL) {
                // Remove unwanted prefix
                char *gpuInfo = strstr(line, ": ");
                if (gpuInfo) {
                    gpuInfo += 2;  // Move past the ": "
                    // Remove newline character
                    gpuInfo[strcspn(gpuInfo, "\n")] = 0;

                    snprintf(gpu, 256, "\033[96m%s \033[0m%s", GPU, gpuInfo);
                } else {
                    snprintf(gpu, 256, "\033[96m%s \033[0m%s", GPU, "Unknown");
                }
            } else {
                snprintf(gpu, 256, "\033[96m%s \033[0m%s", GPU, "Unknown");
            }

            pclose(lspci);
        } else {
            snprintf(gpu, 256, "\033[96m%s \033[0m%s", GPU, "Unknown");
        }
    } else {
        snprintf(gpu, 256, "\033[96m%s \033[0m%s", GPU, "Unknown");
    }

    return gpu;
}