#ifndef FUNCTION_H
#define FUNCTION_H

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

#endif