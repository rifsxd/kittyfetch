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

#include "function.h"

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

char *getTitleInfo() {
    char *titleInfo = malloc(256);
    if (titleInfo) {
        char username[256];
        char hostname[256];
        if (getlogin_r(username, sizeof(username)) == 0 && gethostname(hostname, sizeof(hostname)) == 0) {
            snprintf(titleInfo, 256, "\033[31m%s \033[31m%s\033[0m", USER, strcat(strcat(username, "@"), hostname));
        } else {
            snprintf(titleInfo, 256, "\033[31m%s \033[31m%s\033[0m", USER, "Unknown");
        }
    } else {
        snprintf(titleInfo, 256, "\033[31m%s \033[31m%s\033[0m", USER, "Unknown");
    }
    return titleInfo;
}

char *getOsInfo() {
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

char *getKernelInfo() {
    char *kernelInfo = malloc(256);

    if (kernelInfo) {
        struct utsname unameData;
        if (uname(&unameData) == 0) {
            snprintf(kernelInfo, 256, "\033[33m%s \033[0m%s", KERNEL, unameData.release);
        } else {
            snprintf(kernelInfo, 256, "\033[33m%s \033[0m%s", KERNEL, "Unknown");
        }
    } else {
        snprintf(kernelInfo, 256, "\033[33m%s \033[0m%s", KERNEL, "Unknown");
    }
    
    return kernelInfo;
}

char *getShellInfo() {
    char *shellInfo = malloc(256);
    if (shellInfo) {
        char *shellenv = getenv("SHELL");
        if (shellenv) {
            char *shellname = strrchr(shellenv, '/');
            if (shellname) {
                // If there's a '/', use the string after it
                snprintf(shellInfo, 256, "\033[34m%s \033[0m%s", SHELL, shellname + 1);
            } else {
                // If no '/', consider the whole string as the shell name
                snprintf(shellInfo, 256, "\033[34m%s \033[0m%s", SHELL, shellenv);
            }
        } else {
            snprintf(shellInfo, 256, "\033[34m%s \033[0m%s", SHELL, "Unknown");
        }
    } else {
        snprintf(shellInfo, 256, "\033[34m%s \033[0m%s", SHELL, "Unknown");
    }
    
    return shellInfo;
}


char *getWmInfo() {
    char *wmInfo = malloc(256);

    if (wmInfo) {
        char *waylandDisplay = getenv("WAYLAND_DISPLAY");
        if (waylandDisplay) {
            char *xdgDesktop = getenv("XDG_CURRENT_DESKTOP");
            snprintf(wmInfo, 256, "\033[38;5;93m%s \033[0m%s", WM, xdgDesktop ? xdgDesktop : "Unknown");
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
                            snprintf(wmInfo, 256, "\033[38;5;93m%s \033[0m%s", WM, (char *)propValue);
                            XFree(propValue);
                        } else {
                            snprintf(wmInfo, 256, "\033[38;5;93m%s \033[0m%s", WM, "Unknown");
                        }
                    }
                }

                XCloseDisplay(display);
            } else {
                snprintf(wmInfo, 256, "\033[38;5;93m%s \033[0m%s", WM, "Unknown");
            }
        }
    } else {
        snprintf(wmInfo, 256, "\033[38;5;93m%s \033[0m%s", WM, "Unknown");
    }
    
    return wmInfo;
}

char *getUptimeInfo() {
    char *uptimeInfo = malloc(256);
    if (uptimeInfo) {
        FILE *uptimeFile = fopen("/proc/uptime", "r");
        if (uptimeFile) {
            double uptimeValue;
            fscanf(uptimeFile, "%lf", &uptimeValue);
            fclose(uptimeFile);

            int hours = (int)(uptimeValue / 3600);
            int minutes = (int)((uptimeValue - hours * 3600) / 60);

            snprintf(uptimeInfo, 256, "\033[36m%s \033[0m%dh %dm", UPTIME, hours, minutes);
        } else {
            snprintf(uptimeInfo, 256, "\033[36m%s \033[0m%s", UPTIME, "Unknown");
        }
    } else {
        snprintf(uptimeInfo, 256, "\033[36m%s \033[0m%s", UPTIME, "Unknown");
    }
    
    return uptimeInfo;
}

char *getRamInfo() {
    char *ramInfo = malloc(256);
    if (ramInfo) {
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
                snprintf(ramInfo, 256, "\033[38;5;198m%s \033[0m%ld MB / %ld MB", RAM, used_mem / 1024, total_mem / 1024);
            } else {
                snprintf(ramInfo, 256, "\033[38;5;198m%s \033[0m%s", RAM, "Unknown");
            }

            fclose(meminfo);
        } else {
            snprintf(ramInfo, 256, "\033[38;5;198m%s \033[0m%s", RAM, "Unknown");
        }
    } else {
        snprintf(ramInfo, 256, "\033[38;5;198m%s \033[0m%s", RAM, "Unknown");
    }
    
    return ramInfo;
}

char *getStorageInfo() {
    char *stoageInfo = malloc(256);
    if (stoageInfo) {
        struct statvfs vfs;
        if (statvfs("/", &vfs) == 0) {
            long total_space = (long)vfs.f_frsize * vfs.f_blocks;
            long used_space = (long)vfs.f_frsize * (vfs.f_blocks - vfs.f_bfree);

            snprintf(stoageInfo, 256, "\033[95m%s \033[0m%ld MB / %ld MB", DISK, used_space / (1024 * 1024), total_space / (1024 * 1024));
        } else {
            snprintf(stoageInfo, 256, "\033[95m%s \033[0m%s", DISK, "Unknown");
        }
    } else {
        snprintf(stoageInfo, 256, "\033[95m%s \033[0m%s", DISK, "Unknown");
    }
    
    return stoageInfo;
}

char *getLSBReleaseInfo() {
    char *lsbaltInfo = malloc(256);
    if (lsbaltInfo) {
        FILE *lsbReleaseFile = popen("lsb_release -si 2>/dev/null", "r");
        if (lsbReleaseFile) {
            if (fgets(lsbaltInfo, 256, lsbReleaseFile) != NULL) {
                // Remove newline character
                lsbaltInfo[strcspn(lsbaltInfo, "\n")] = 0;
            } else {
                snprintf(lsbaltInfo, 256, "%s", "Unknown");
            }
            pclose(lsbReleaseFile);
        } else {
            snprintf(lsbaltInfo, 256, "%s", "Unknown");
        }
    } else {
        snprintf(lsbaltInfo, 256, "%s", "Unknown");
    }
    
    return lsbaltInfo;
}

char *getPackageInfo() {
    char *lsbaltInfo = getLSBReleaseInfo();

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
    } else {
        snprintf(packageInfo, 256, "\033[38;5;208m%s \033[0m%s", PACKAGES, "Unknown");
    }
    
    return packageInfo;
}

char *getCpuInfo() {
    char *cpuInfo = malloc(256);
    if (cpuInfo) {
        FILE *cpuinfo = fopen("/proc/cpuinfo", "r");
        if (cpuinfo) {
            char line[256];
            int cpuCount = 0;

            while (fgets(line, sizeof(line), cpuinfo) != NULL) {
                if (strstr(line, "model name")) {
                    cpuCount++;
                    char *model = strchr(line, ':') + 2;
                    model[strlen(model) - 1] = '\0'; // Remove the trailing newline
                    snprintf(cpuInfo, 256, "\033[95m%s \033[0m%s (x%d)", CPU, model, cpuCount);
                }
            }

            fclose(cpuinfo);
        } else {
            snprintf(cpuInfo, 256, "\033[95m%s \033[0m%s", CPU, "Unknown");
        }
    } else {
        snprintf(cpuInfo, 256, "\033[95m%s \033[0m%s", CPU, "Unknown");
    }
    
    return cpuInfo;
    
}

char *getGpuInfo() {
    char *gpuInfo = malloc(256);
    if (gpuInfo) {
        FILE *lspci = popen("lspci | grep -i vga", "r");
        if (lspci) {
            char line[256];

            if (fgets(line, sizeof(line), lspci) != NULL) {
                // Remove unwanted prefix
                char *gpuName = strstr(line, ": ");
                if (gpuName) {
                    gpuName += 2;  // Move past the ": "
                    // Remove newline character
                    gpuName[strcspn(gpuName, "\n")] = 0;

                    snprintf(gpuInfo, 256, "\033[96m%s \033[0m%s", GPU, gpuName);
                } else {
                    snprintf(gpuInfo, 256, "\033[96m%s \033[0m%s", GPU, "Unknown");
                }
            } else {
                snprintf(gpuInfo, 256, "\033[96m%s \033[0m%s", GPU, "Unknown");
            }

            pclose(lspci);
        } else {
            snprintf(gpuInfo, 256, "\033[96m%s \033[0m%s", GPU, "Unknown");
        }
    } else {
        snprintf(gpuInfo, 256, "\033[96m%s \033[0m%s", GPU, "Unknown");
    }
    
    return gpuInfo;
}