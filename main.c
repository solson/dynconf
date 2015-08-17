#include "config.h"

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

void* load_config(const char* filename, struct config* conf) {
    // Re-build user config.
    system("make libconfig.so");

    // Reload user config.
    void* libconfig = dlopen(filename, RTLD_NOW);
    if (libconfig == NULL) {
        fprintf(stderr, "Error opening user config shared library.\n");
        exit(1);
    }

    // Call user config initialization function.
    typedef void (*init_func)(struct config*);
    init_func dynconf_init = (init_func) dlsym(libconfig, "dynconf_init");

    if (dynconf_init == NULL) {
        fprintf(stderr, "Error loading user config shared library 'dynconf_init' function.\n");
        exit(1);
    }

    (*dynconf_init)(conf);

    return libconfig;
}

int main(int argc, char** argv) {
    struct config conf;
    conf.number = 1;

    void* libconfig = load_config("./libconfig.so", &conf);

    while (1) {
        // Wait on user input.
        int c = getc(stdin);
        if (c == EOF) { break; }

        if (dlclose(libconfig) != 0) {
            fprintf(stderr, "Error closing user config shared library.\n");
            exit(1);
        }

        // Rebuild, reload and re-run user config.
        libconfig = load_config("./libconfig.so", &conf);

        printf("conf.number = %d\n", conf.number);
    }

    return 0;
}
